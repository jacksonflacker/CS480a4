#ifndef PRODUCER_H
#define PRODUCER_H
#include "Buffer.h"
#include "ridesharing.h"
#include "io.h"

/* Defines struct that is used to pass the buffer to the producer function. This
struct is then used by the producer to access variables and the shared buffer. 

Buff * buf: Shared buffer used to communicate between threads.

request_type: Keeps track of what type of request is being produced. Types are:
human driver or autonomous car represented by 0 or 1.  

wait_time: Holds (in miliseconds) how long to wait inbetween producing requests. This is
based on the commmand line arguments input. Used to simulate the time it takes for a
producer to produce a request. Unlike consumer this is different depending on the request_type.
 */


using namespace std;

typedef struct arg_struct{
    //shared buffer
    Buffer *buf;
    //type of request
    int request_type;
    //number of miliseconds to sleep inbetween production of a request
    int wait_time;
}ProducerArgs;

//defines common function used by producers
void* produceItem(void *buf);

#endif