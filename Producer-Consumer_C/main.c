#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

sem_t sem;
sem_t sem1;

char gBuf[100];

void* producer_func(void*) {
    
    while(1) {
        sem_wait(&sem1); // wait
        strcpy(gBuf, "Test");
        printf("Producer Thread: prodece data: %s...\n", gBuf);
        sleep(1);
        sem_post(&sem);  // post    
    }
    return NULL;
}

void* consumer_func(void*) {

    while(1) {
        sem_wait(&sem);  // Wait
        printf("Consumer thread consume data: %s\n", gBuf);
        gBuf[0] = '\0';
        sleep(1);
        sem_post(&sem1); // post
    }
    return NULL;
}

int main() {
    sem_init(&sem, 0, 0);  // Init with 0 => locked
    sem_init(&sem1, 5, 1);  // Init with 1 => unlocked

    pthread_t producer;
    pthread_create(&producer, NULL, producer_func, NULL);

    pthread_t consumer;
    pthread_create(&consumer, NULL, consumer_func, NULL);

    pthread_join(producer, nullptr);
    pthread_join(consumer, nullptr);

    sem_destroy(&sem);
    sem_destroy(&sem1);
    return 0;
}
