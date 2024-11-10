#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t wrt; // Semaphore for writer access
pthread_mutex_t mutex; // Mutex for reader count
int cnt = 1; // Shared resource
int numreader = 0; // Number of active readers

// Writer function
void *writer(void *wno) {
    sem_wait(&wrt); // Writer waits until it's allowed to write

    cnt = cnt * 2; // Modify the shared resource
    printf("Writer %d modified cnt to %d\n", *((int *)wno), cnt);

    sem_post(&wrt); // Allow other writers/readers
    return NULL;
}

// Reader function
void *reader(void *rno) {
    pthread_mutex_lock(&mutex); // Reader locks before updating reader count
    numreader++;
    if (numreader == 1) {
        sem_wait(&wrt); // If this is the first reader, block writers
    }
    pthread_mutex_unlock(&mutex);

    // Reading section
    printf("Reader %d: read cnt as %d\n", *((int *)rno), cnt);

    pthread_mutex_lock(&mutex); // Reader locks before decrementing reader count
    numreader--;
    if (numreader == 0) {
        sem_post(&wrt); // If this is the last reader, wake up writers
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t read[10], write[5]; // 10 readers and 5 writers
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1); // Initialize semaphore for writers

    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Numbers to represent readers and writers

    // Create 5 writer threads and 10 reader threads, interleaved
    for (int i = 0; i < 5; i++) {
        pthread_create(&write[i], NULL, writer, (void *)&a[i]); // Create writer threads
        pthread_create(&read[i], NULL, reader, (void *)&a[i + 5]); // Create reader threads
    }

    // Wait for all writers and readers to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(write[i], NULL); // Wait for writer threads to finish
        pthread_join(read[i], NULL);  // Wait for reader threads to finish
    }

    pthread_mutex_destroy(&mutex); // Cleanup mutex
    sem_destroy(&wrt); // Cleanup semaphore

    return 0;
}

