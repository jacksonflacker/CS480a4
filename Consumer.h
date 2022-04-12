#ifndef CONSUMER_H
#define CONSUMER_H
#include "Buffer.h"
#include "io.h"


using namespace std;

typedef struct arg{
    Buffer *buf;
    int request_type;
    int wait_time;
}ConsumerArgs;

void* consumeItem(void *buf);

#endif