#include <pthread.h>
#include <stdio.h>

static __thread int a = 0;


void * aug(void * args) {
  a++;
  printf("%d\n", a);
  return NULL;
}


int main() {
  pthread_t thread;
  pthread_create(&thread, NULL, aug, NULL);
  pthread_t thread2;
  pthread_create(&thread2, NULL, aug, NULL);

  printf("%d\n", a);

  pthread_join(thread, NULL);
  pthread_join(thread2, NULL);
}