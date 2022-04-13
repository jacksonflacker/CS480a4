#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <semaphore.h>
#include "ridesharing.h"

using namespace std;
// max size of buffer queue
#define MAX_BUFFER_SIZE 12
// max number of human requests in buffer at a time
#define MAX_HUMAN_REQUESTS 4

class Buffer{
public:
    int requests_produced[RequestTypeN];
    int requests_consumed[RequestTypeN];
    int fast_algo_consumption[RequestTypeN];
    int cost_algo_consumption[RequestTypeN];
    // keeps track of the count of requests currently in the buffer
    int requests_in_queue[RequestTypeN];
    // keeps running count of all requests
    int request_type_count[RequestTypeN];
    sem_t  Mutex, Unconsumed, AvailableSlots, HumanRequests, Exit, MaxRequests;
    // count of human driver requests
    int human_driver_requests;
    // max human driver requests
    int max_human_requests;
    // max size of queue
    int max_queue_size;
    // total number of requests
    int max_number_of_requests;
    // queue containing driver requests
    vector<int> RequestQueue;
    // function to insert (produce) item into queue
    void insertIntoBuffer(int item);
    // function to remove (consume) item into queue
    void removeFromBuffer();
    // constructor
    Buffer();
};

#endif