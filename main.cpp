/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Jordan Aquino & Jamison Coombs
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "buffer.h"
#include <unistd.h>
#include <pthread.h>
#include <mutex>

using namespace std;

// global buffer object
Buffer *buffer;
bool running = true;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER; /* consumer waits on this cond var */
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER; /* producer waits on this cond var */

// Producer thread function
// TODO: Add your implementation of the producer thread here
void *producer(void *id) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) id);
    while (running) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);
        // TODO: Add synchronization code here
        pthread_mutex_lock(&m);
        while (buffer->get_count() == buffer->get_size())
            pthread_cond_wait(&c_prod, &m);

        if (buffer->insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer->print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }
        pthread_mutex_unlock(&m);
		pthread_cond_signal(&c_cons);
    }
    pthread_exit(NULL);
}

// Consumer thread function
// Add your implementation of the consumer thread here
void *consumer(void* arg) {
    while (running) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);
        // TODO: Add synchronization code here
        pthread_mutex_lock (&m);
        while(buffer->get_count() == 0)
            pthread_cond_wait(&c_cons, &m);

        buffer_item item = buffer->remove_item();
        if (item != -1) {
            cout << "Consumer Removed item " << item << endl;
            buffer->print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }
        pthread_mutex_unlock(&m);
		pthread_cond_signal(&c_prod);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	if(argc < 4){
		std::cout<<"Inadequate number of arguments provided.\n";
	}


    /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */
    unsigned int sleepTime = stoi(argv[1]);
    unsigned int numProducers =  stoi(argv[2]);
    unsigned int numConsumers = stoi(argv[3]);

    /* TODO: 2. Initialize buffer and synchronization primitives */
    buffer = new Buffer();

    /* TODO: 3. Create producer thread(s).
     * You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    pthread_t thread;
    int producer_ids[numProducers];
    for(unsigned int i = 0; i < numProducers; i++)
    {
        producer_ids[i] = i+1;
        pthread_create(&thread, NULL, producer, &producer_ids[i]);
    }
    

    /* TODO: 4. Create consumer thread(s) */
    for(unsigned int i = 0; i < numConsumers; i++)
    {
        pthread_create(&thread, NULL, consumer, NULL);
    }
    
    /* TODO: 5. Main thread sleep */
    sleep(sleepTime);

    /* TODO: 6. Exit */
    running = false;
}
