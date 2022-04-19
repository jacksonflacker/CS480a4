#ifndef PRODUCER_H
#define PRODUCER_H
#include "Buffer.h"
#include "ridesharing.h"
#include "io.h"


using namespace std;

typedef struct arg_struct{
    Buffer *buf;
    int request_type;
    int wait_time;
}ProducerArgs;

void* produceItem(void *buf);

#endif