#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <semaphore.h>

using namespace std;

class Buffer{
public:
    sem_t  Mutex, Uncomsumed, AvailableSlots;
    // count of human driver requests
    int human_driver_requests;
    // max human driver requests
    int max_human_requests;
    // max size of queue
    int max_queue_size;
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