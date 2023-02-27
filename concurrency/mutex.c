#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int counter = 0;
// pthread_mutex_t lck = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lck;

void * count(void * args) {
  for (int i = 0; i < 500; i++) {
    pthread_mutex_lock(&lck);
    counter++;
    pthread_mutex_unlock(&lck);
  }

  return NULL;
}

int main() {
  pthread_t threads[2];
  pthread_mutex_init(&lck, NULL);
  for (int i = 0; i < 2; i++) {
    pthread_create(&threads[i], NULL, count, NULL);
  }

  for (int i = 0; i < 2; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("%d\n", counter);
  pthread_mutex_destroy(&lck);
}