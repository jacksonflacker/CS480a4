#ifndef PRODUCER_H
#define PRODUCER_H
#include "Buffer.h"

using namespace std;

typedef struct arg_struct{
    Buffer *buf;
    int request_type;
    int wait_time;
}args;

void* produceItem(void *buf);

#endif