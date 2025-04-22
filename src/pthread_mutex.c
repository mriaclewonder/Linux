#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

pthread_mutex_t mutex;

void* func1(void *arg)
{
  int i = 0;
  pthread_mutex_lock(&mutex);
  for (i = 'A'; i <= 'Z';++i){
    putchar(i);
    fflush(stdout);
    usleep(100000);
  }
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void* func2(void* arg)
{
  int  i = 0;
  pthread_mutex_lock(&mutex);
  for (i = 'a'; i <= 'z'; ++i)
  {
    putchar(i);
    fflush(stdout);
    usleep(100000);
  }
  pthread_mutex_unlock(&mutex);
  return NULL;
}


int main() {
  pthread_t pit1;
  pthread_t pit2;
  pthread_mutex_init(&mutex, NULL);

  pthread_create(&pit1, NULL, func1, NULL);
  pthread_create(&pit2, NULL, func2, NULL);

  pthread_join(pit1, NULL);
  pthread_join(pit2, NULL);

  pthread_mutex_destroy(&mutex);

  printf("\n");
  return 0;
}