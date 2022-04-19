#include <iostream>
#include <unistd.h>
#include "Producer.h"
#include <semaphore.h>

using namespace std;


/*void produceItem(void *buf): 
Purpose: is to provide common code for the producer threads to use when created.
Utilizes POSIX (unnamed) semaphores in order to ensure critical regions when
writing into buffer and proper resource usage. Produces and publish rider requests
to the broker until it reaches the limit to production based on command line input.
Signals it is complete to the semaphore before exiting.

Expects: 
void *buf: Is a shared data structure used to communicate between POSIX threads

Return: Does not return anything
*/

void* produceItem(void * buf){
    // structure containing buffer, item type, and wait time
    ProducerArgs *producer_args = (ProducerArgs*) buf;
    int item = producer_args->request_type;
    int sem_val;
    while(true){
        // wait for designated wait time
        usleep(producer_args->wait_time *1000); // converting to milliseconds
        if(item == HumanDriver){
            // decrement semaphore keeping count of human requests in buffer
            sem_wait(&producer_args->buf->HumanRequests);
        }
        sem_getvalue(&producer_args->buf->MaxRequests, &sem_val);
        // if(!sem_val){
        //     break;
        // }
        // decrement semaphore keeping count of available slots in buffer
        sem_wait(&producer_args->buf->AvailableSlots);
        // access buffer exclusively 
        sem_wait(&producer_args->buf->Mutex);
        // if all requests made, exit
        if(producer_args->buf->max_number_of_requests == 0){
            // release buffer to other threads
            sem_post(&producer_args->buf->Mutex);
            // exit thread
            break;
        }
        // insert item into buffer queue
        producer_args->buf->RequestQueue.push_back(item);
        // decrement semaphore which holds total number of requests
        producer_args->buf->requests_in_queue[item]++;
        producer_args->buf->requests_produced[item]++;
        io_add_type(
            (RequestType)item,
            producer_args->buf->requests_in_queue,
            producer_args->buf->requests_produced
        );
        producer_args->buf->max_number_of_requests--;
        // relinquish buffer to other threads        
        sem_post(&producer_args->buf->Mutex);
        //cout <<item<< " MaxRequest Sem val: "<<sem_val<<endl;
        // increment semaphore for unconsumed items
        sem_post(&producer_args->buf->Unconsumed);
        //sem_wait(&producer_args->buf->MaxRequests);
        
    }
    cout << "\n\nexit thread producer\n\n";
    sem_post(&producer_args->buf->Exit);
    return NULL;
}