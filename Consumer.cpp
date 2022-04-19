#include <iostream>
#include <unistd.h>
#include "Consumer.h"
#include <semaphore.h>
#include "io.h"

using namespace std;

/*void consumeItem(void *buf): 
Purpose: is to provide common code for the consumer threads to use when created.
Utilizes POSIX (unnamed) semaphores in order to ensure critical regions when
writing into buffer and proper resource usage. Consumes until has consumed the last 
request based on command line input and signals it is complete to the semaphore before exiting.

Expects: 
void *buf: Is a shared data structure used to communicate between POSIX threads

Return: Does not return anything
*/

void* consumeItem(void *buf){
    ConsumerArgs * consumer_args = (ConsumerArgs*) buf;
    int item;
    while(true){
        // check if all items consumed
        // decrement semaphore keeping count of available slots in buffer
        sem_wait(&consumer_args->buf->Unconsumed);
        // access buffer exclusively 
        if(consumer_args->buf->max_number_of_consumptions == 0){
            // one thread may be stuck in unconsumed wait
            break; // exit loop
        }
        sem_wait(&consumer_args->buf->Mutex);
        // remove item from buffer
        item = consumer_args->buf->RequestQueue[0];
        consumer_args->buf->RequestQueue.erase(consumer_args->buf->RequestQueue.begin());
        if(item == HumanDriver){
            sem_post(&consumer_args->buf->HumanRequests);
        }
        // decrement count of request in queue
        consumer_args->buf->requests_in_queue[item]--;
        // increment count of requests consumed
        consumer_args->buf->requests_consumed[item]++;
        // increment
        consumer_args->buf->request_type_count[item]++;
        // cout << "Consume: "<< item << endl;
        if(consumer_args->consume_type == CostAlgoDispatch){
            consumer_args->buf->cost_algo_consumption[item]++;
        }
        else if (consumer_args->consume_type == FastAlgoDispatch){
            consumer_args->buf->fast_algo_consumption[item]++;
        }
        // decrement count of max consumptions
        consumer_args->buf->max_number_of_consumptions--;
        int *arrPointer = (consumer_args->consume_type == FastAlgoDispatch)? consumer_args->buf->fast_algo_consumption:consumer_args->buf->cost_algo_consumption;
        io_remove_type(
            (ConsumerType)consumer_args->consume_type,
            (RequestType)item,
            consumer_args->buf->requests_in_queue,
            arrPointer
        );
        // relinquish buffer to other threads
        sem_post(&consumer_args->buf->Mutex);
        sem_post(&consumer_args->buf->AvailableSlots);
        // wait for designated wait time
        usleep(consumer_args->wait_time *1000); // converting to milliseconds
        if(consumer_args->buf->max_number_of_consumptions == 0){
            // one thread may be stuck in unconsumed wait
            sem_post(&consumer_args->buf->Unconsumed);
            break; // exit loop
        }
    }
    cout << "\n\nexit thread consumer "<<consumer_args->consume_type<<"\n\n";
    sem_post(&consumer_args->buf->Exit);
    return NULL;
}