#ifndef CONSUMER_H
#define CONSUMER_H
#include "Buffer.h"

/* Defines struct that is used to pass the buffer to the consumer function. This
struct is then used by the consumer to access variables and the shared buffer. 

Buff * buf: Shared buffer used to communicate between threads.

consume_type: Keeps track of what type of request is being consumed. 

wait_time: Holds (in miliseconds) how long to wait inbetween consuming requests. This is
based on the commmand line arguments input. Used to simulate the time it takes for a
consumer to consume a request. */

using namespace std;

typedef struct arg{
    //shared data
    Buffer *buf;
    //consumer type that is being consumed
    int consume_type;
    //number of miliseconds to sleep inbetween consumption of a request
    int wait_time;
}ConsumerArgs;

//defines common function used by consumers
void* consumeItem(void *buf);

#endif