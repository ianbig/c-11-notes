#include <pthread.h>
#include <stdio.h>
#include <errno.h>

pthread_t thread[2];

typedef struct args {
  int thread_id;
} args_t;


void * deadlock_thread(void * arg) {
  args_t *thread_to_wait = (args_t *)arg;
  int wait_thread = thread_to_wait->thread_id;
  int res = pthread_join(thread[wait_thread], NULL);
  if (res == EDEADLK) {
    printf("detecting deadlock\n");
  }

  return NULL;
}

int main() {

    args_t thread_arg;
    thread_arg.thread_id = 0;
    pthread_create(&thread[0], NULL, deadlock_thread, &thread_arg);

    args_t thread_arg_2;
    thread_arg_2.thread_id = 1;
    pthread_create(&thread[0], NULL, deadlock_thread, &thread_arg_2);

  for (int i = 0; i < 2; i++) {
    pthread_join(thread[i], NULL);
  }
}