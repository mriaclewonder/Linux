#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

pthread_mutex_t _mutex;
pthread_cond_t _cond;

int flag = 0;

void* func1(void *arg) {
    while (1) {
        pthread_mutex_lock(&_mutex);

        // 等待 flag 为 0
        while (flag != 0) {
            pthread_cond_wait(&_cond, &_mutex);
        }

        // 修改 flag 为 1
        flag = 1;
        printf("Thread 1: Changed flag to 1\n");

        // 通知线程 2
        pthread_cond_signal(&_cond);

        pthread_mutex_unlock(&_mutex);
        sleep(2);
    }

    return NULL;
}

void* func2(void* arg) {
    while (1) {
        pthread_mutex_lock(&_mutex);

        // 等待 flag 为 1
        while (flag != 1) {
            pthread_cond_wait(&_cond, &_mutex);
        }

        // 修改 flag 为 0
        flag = 0;
        printf("Thread 2: Changed flag to 0\n");

        // 通知线程 1
        pthread_cond_signal(&_cond);

        pthread_mutex_unlock(&_mutex);
        sleep(2);
    }

    return NULL;
}

int main() {
    pthread_t pit1;
    pthread_t pit2;

    pthread_mutex_init(&_mutex, NULL);
    pthread_cond_init(&_cond, NULL);

    pthread_create(&pit1, NULL, func1, NULL);
    pthread_create(&pit2, NULL, func2, NULL);

    pthread_join(pit1, NULL);
    pthread_join(pit2, NULL);

    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_cond);

    return 0;
}