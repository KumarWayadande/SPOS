#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MaxItems 5      // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5    // Size of the buffer

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void *producer(void *pno) {
    int item;
    for (int i = 0; i < MaxItems; i++) {
        item = rand() % 100;  // Produce a random item (scaled down to a number between 0 and 99)

        sem_wait(&empty);  // Wait if buffer is full
        pthread_mutex_lock(&mutex);  // Lock the buffer

        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);
        in = (in + 1) % BufferSize;  // Increment the index in a circular fashion

        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&full);  // Signal that buffer is not empty
    }
    return NULL;
}

void *consumer(void *cno) {
    for (int i = 0; i < MaxItems; i++) {
        sem_wait(&full);  // Wait if buffer is empty
        pthread_mutex_lock(&mutex);  // Lock the buffer

        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n", *((int *)cno), item, out);
        out = (out + 1) % BufferSize;  // Increment the index in a circular fashion

        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&empty);  // Signal that buffer is not full
    }
    return NULL;
}

int main() {
    pthread_t pro[5], con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize);  // Initialize the empty semaphore
    sem_init(&full, 0, 0);  // Initialize the full semaphore

    int a[5] = {1, 2, 3, 4, 5};  // Used to number the producers and consumers
    srand(time(NULL));  // Seed the random number generator

    // Create 5 producer threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, producer, (void *)&a[i]);
    }

    // Create 5 consumer threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, consumer, (void *)&a[i]);
    }

    // Join the producer threads
    for (int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }

    // Join the consumer threads
    for (int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    // Cleanup
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
