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
#include <semaphore.h>

using namespace std;

// global buffer object
Buffer *buffer;
bool running = true;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
sem_t s_empty;
sem_t s_full; 

// Producer thread function
void *producer(void *id) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) id);
    while (running) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);
        // Synchronization code
        sem_wait(&s_empty); // Decrement the empty semaphore
        pthread_mutex_lock(&m); // Lock the mutex

        // Insert item into buffer
        if (buffer->insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl; // show item inserted
            buffer->print_buffer(); // show buffer
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }
        pthread_mutex_unlock(&m); // unlock the mutex
		sem_post(&s_full); // increment the full semaphore
    }
    pthread_exit(NULL);
}

// Consumer thread function
void *consumer(void* arg) {
    while (running) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);

        // Synchronization code
        sem_wait(&s_full); // Decrement the full semaphore
        pthread_mutex_lock(&m); // Lock the mutex

        buffer_item item = buffer->remove_item(); // consume the item from the buffer
        if (item != -1) {
            cout << "Consumer Removed item " << item << endl; // print the item consumed
            buffer->print_buffer(); // print buffer
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }
        // Unlock the mutex
        pthread_mutex_unlock(&m);
        // Increment the empty semaphore
		sem_post(&s_empty);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	if(argc < 4){
		std::cout<<"Inadequate number of arguments provided.\n";
	}

    /* 1. Get command line arguments argv[1],argv[2],argv[3] */
    unsigned int sleepTime = stoi(argv[1]);
    unsigned int numProducers =  stoi(argv[2]);
    unsigned int numConsumers = stoi(argv[3]);

    /* 2. Initialize buffer and synchronization primitives */
    buffer = new Buffer();
    pthread_t thread;
    sem_init(&s_empty, 0, buffer->get_size());
    sem_init(&s_full, 0, 0);

    /* 3. Create producer thread(s).
     * You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    int producer_ids[numProducers];
    for(unsigned int i = 0; i < numProducers; i++)
    {
        producer_ids[i] = i+1;
        pthread_create(&thread, NULL, producer, &producer_ids[i]);
    }
    

    /* 4. Create consumer thread(s) */
    for(unsigned int i = 0; i < numConsumers; i++)
    {
        pthread_create(&thread, NULL, consumer, NULL);
    }
    
    /* 5. Main thread sleep */
    sleep(sleepTime);

    /* 6. Exit */
    running = false;
    pthread_mutex_destroy(&m);
    sem_destroy(&s_empty);
    sem_destroy(&s_full);
}
