#include <iostream>
#include <unistd.h>
#include "Producer.h"
#include <semaphore.h>

using namespace std;

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
        if(!sem_val){
            break;
        }
        // decrement semaphore keeping count of available slots in buffer
        sem_wait(&producer_args->buf->AvailableSlots);
        // access buffer exclusively 
        sem_wait(&producer_args->buf->Mutex);

        cout << "Inserting Item: "<<item<<endl;
        // insert item into buffer queue
        producer_args->buf->RequestQueue.push_back(item);
        // decrement semaphore which holds total number of requests
        sem_wait(&producer_args->buf->MaxRequests);

        // relinquish buffer to other threads
        sem_post(&producer_args->buf->Mutex);
        // increment semaphore for unconsumed items
        sem_post(&producer_args->buf->Unconsumed);
        
    }
    sem_post(&producer_args->buf->Exit);
    return NULL;
}