#include <iostream>
#include "ridesharing.h"
#include "Buffer.h"

using namespace std;

/*Buffer:
Shared data structure used to communicate between threads
Includes:

human_driver_requests: counts the current number of human drive requests to ensure 
max number of human requests is not hit.

max_human_requests: maximum number of human driver requests that area llowed in a buffer
at a single time.

semaphore &HumanRequests: semaphore used to ensure proper number of humans requests allowed in
the buffer at a single time. 

semaphore &AvailableSlots: semaphore used to place a limit on the maximum size of the buffer.

semaphore &Mutex: semaphore used in order to ensure mutal exclusions for critical section of
the buffer.

semaphore &Unconsumed: semaphore that keeps track of the number of unconsumed items in
the current buffer queue to be used by the consumer threads.

semaphore &Exit: semaphore that used to ensure precedence constraint and that the main
thread does not exit before all producer and consumer threads have exited.

max_number_of_requests: stores that number of max requests before producers stop producing.

max_number_of_consumptions: stores that number of max consumptions before consumers stop consuming.

 */

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
    // # of consumed requests
    max_number_of_consumptions = 0;
}
void Buffer::insertIntoBuffer(int item){
}