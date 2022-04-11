#include <iostream>
#include <unistd.h>
#include "Producer.h"

using namespace std;

void* produceItem(void * buf){
    args *producer_args = (args*) buf;
    while(producer_args->buf->RequestQueue.size() < producer_args->buf->max_queue_size){
        // wait for designated wait time
        usleep(producer_args->wait_time *1000); // converting to milliseconds
        // insert request into queue
        producer_args->buf->RequestQueue.push_back(producer_args->request_type);
    }
    return NULL;
}