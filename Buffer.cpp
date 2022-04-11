#include <iostream>
#include "ridesharing.h"
#include "Buffer.h"

using namespace std;

Buffer::Buffer(){
    // count of human driver requests
    human_driver_requests = 0;
    // max number of human driver requests in buffer at 1 time
    max_human_requests = 4;
    // max size of buffer queue
    AvailableSlots = 12;
    // mutual exclusion
    Mutex = 1;
    // # of unconsumed items in buffer queue
    Uncomsumed = 0;
}
void Buffer::insertIntoBuffer(int item){
}