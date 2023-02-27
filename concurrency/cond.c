#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define MAXSIZE 1

typedef struct Queue {
  pthread_mutex_t lck;
  pthread_cond_t cond;
  int data[MAXSIZE];
  int sz;
} Queue;

void initQueue(Queue * qu) {
  pthread_mutex_init(&qu->lck, NULL);
  pthread_cond_init(&qu->cond, NULL);
  qu->sz = 0;
}

void pushData(Queue *qu) {
  while (qu->sz >= MAXSIZE)
  {
    printf("queue currently full, wait for a second\n");
    pthread_cond_wait(&qu->cond, &qu->lck);
  }

  qu->data[qu->sz] = 1;
  qu->sz++;
  printf("push a data\n");
  pthread_cond_signal(&qu->cond);
}

int popData(Queue * qu) {
  while (qu->sz <= 0)
  {
    printf("queue currently empty, wait for a second\n");
    pthread_cond_wait(&qu->cond, &qu->lck);
  }

  qu->data[--qu->sz] = 0;
  printf("pop a data\n");
  pthread_cond_signal(&qu->cond);
  return 1;
}

void destroyQueue(Queue *qu) {
  pthread_mutex_destroy(&qu->lck);
  pthread_cond_destroy(&qu->cond);
}

void * pushDataHandler(void * arg) {
  pushData((Queue*) arg);
  pushData((Queue*) arg);
  return NULL;
}

void * popDataHandler(void * arg) {
  sleep(3);
  popData((Queue*) arg);
  return NULL;
}

int main() {
  Queue qu;
  initQueue(&qu);
  pthread_t pid1, pid2;
  pthread_create(&pid1, NULL, pushDataHandler, &qu);
  pthread_create(&pid2, NULL, popDataHandler, &qu);

  pthread_join(pid1, NULL);
  pthread_join(pid2, NULL);
  destroyQueue(&qu);
}