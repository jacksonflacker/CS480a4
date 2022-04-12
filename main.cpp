/**
 * @file main.cpp
 * @author Omar Martinez (REDID: 818749029)
 * @brief 
 * 
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "ridesharing.h"
#include "Buffer.h"
#include "Producer.h"
#include "Consumer.h"
#include <semaphore.h>
#include <errno.h>


using namespace std;

int main(int argc, char **argv){
    // create buffer object
    Buffer *buffer = new Buffer();
    // initialize command line arguments to default value
    int number_of_requests = 120;
    int request_dispatching_time = 0; // time in milliseconds
    int fast_match_dispatch_time = 0; // time in milliseconds
    int human_ride_request_time = 0; // time in milliseconds
    int autonomous_ride_request_time = 0; // time in milliseconds

    // read in command line arguments
    int Option;
    while((Option = getopt(argc,argv, "n:c:f:h:a:")) != -1){
        switch(Option){
            case 'n':
                if(stoi(optarg) >= 0)
                    number_of_requests = stoi(optarg);
                break;
            case 'c':
                if(stoi(optarg) >= 0)
                    request_dispatching_time = stoi(optarg);
                break;
            case 'f':
                if(stoi(optarg) >= 0)
                    fast_match_dispatch_time = stoi(optarg);
                break;
            case 'h':
                if(stoi(optarg) >= 0)
                    human_ride_request_time = stoi(optarg);
                break;
            case 'a':
                if(stoi(optarg) >= 0)
                    autonomous_ride_request_time = stoi(optarg);
                break;
            default:
                break;
        }
    }
    /**
     * @brief: Arguments passed to producer function.
     * Contains: Pointer to shared buffer, request type, and wait time for human
     *           and robo driver producers.
     * 
     */
    // store number of requests specified in command line arguments
    buffer->max_number_of_requests = number_of_requests;
    sem_init(&buffer->MaxRequests, 0, number_of_requests);
    ProducerArgs human_args = {buffer, HumanDriver, human_ride_request_time};
    ProducerArgs robo_args = {buffer, RoboDriver, autonomous_ride_request_time};

    ConsumerArgs cost_algo = {buffer, CostAlgoDispatch, request_dispatching_time};
    ConsumerArgs fast_algo = {buffer, FastAlgoDispatch, fast_match_dispatch_time};
    // spawn producer and consumer threads
    pthread_t Human_Driver, Robo_Driver, Consumer1, Consumer2;
    pthread_create(&Human_Driver, NULL, &produceItem, (void*) &human_args);
    pthread_create(&Robo_Driver, NULL, &produceItem, (void*) &robo_args);
    pthread_create(&Consumer1, NULL, &consumeItem, (void*) &cost_algo);
    pthread_create(&Consumer2, NULL, &consumeItem, (void*) &fast_algo);
    // wait for producer and consumer threads to finish before resuming main
    sem_wait(&buffer->Exit);
    sem_wait(&buffer->Exit);
    sem_wait(&buffer->Exit);
    sem_wait(&buffer->Exit);
    // pthread_join(Human_Driver, NULL);
    // pthread_join(Robo_Driver, NULL);
    // delete buffer pointer
    delete (buffer);
    return 0;
}