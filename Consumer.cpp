#include <iostream>
#include <unistd.h>
#include "Consumer.h"
#include <semaphore.h>

using namespace std;

void* consumeItem(void *buf){
    ConsumerArgs * consumer_args = (ConsumerArgs*) buf;
    int item;
    while(true){
        // wait for designated wait time
        usleep(consumer_args->wait_time *1000); // converting to milliseconds

        // decrement semaphore keeping count of available slots in buffer
        sem_wait(&consumer_args->buf->Unconsumed);
        // access buffer exclusively 
        sem_wait(&consumer_args->buf->Mutex);
        // remove item from buffer
        item = consumer_args->buf->RequestQueue[0];
        consumer_args->buf->RequestQueue.erase(consumer_args->buf->RequestQueue.begin());
        if(item == HumanDriver){
            sem_post(&consumer_args->buf->HumanRequests);
        }
        // relinquish buffer to other threads
        sem_post(&consumer_args->buf->Mutex);
        sem_post(&consumer_args->buf->AvailableSlots);

        cout << "Consume: "<< item << endl;
        consumer_args->buf->requests_in_queue[item]--;
        consumer_args->buf->request_type_count[item]++;
    }
    sem_post(&consumer_args->buf->Exit);
    return NULL;
}