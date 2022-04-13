#ifndef CONSUMER_H
#define CONSUMER_H
#include "Buffer.h"



using namespace std;

typedef struct arg{
    Buffer *buf;
    int consume_type;
    int wait_time;
}ConsumerArgs;

void* consumeItem(void *buf);

#endif