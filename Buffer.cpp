#include <iostream>
#include "ridesharing.h"
#include "Buffer.h"

using namespace std;

Buffer::Buffer(){
    // count of human driver requests
    human_driver_requests = 0;
    // max number of human driver requests in buffer at 1 time
    max_human_requests = 4;
    // semaphore for max human requests in buffer at a time
    sem_init(&HumanRequests, 0, MAX_HUMAN_REQUESTS);
    // max size of buffer queue
    sem_init(&AvailableSlots, 0, MAX_BUFFER_SIZE);
    // mutual exclusion
    sem_init(&Mutex,0, 1);
    // # of unconsumed items in buffer queue
    sem_init(&Unconsumed, 0, 0);
    // semaphore used to return to main after threads finished 
    sem_init(&Exit, 0, 0);
    // # of requests
    max_number_of_requests = 0;
}
void Buffer::insertIntoBuffer(int item){
}