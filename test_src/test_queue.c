#include "whisper/queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int compare_ints(void *a, void *b) { return *((int *)a) == *((int *)b); }

void test_queue() {
  WQueue q;
  w_make_queue(&q, sizeof(int), 5);
  int values[] = {10, 20, 30, 40, 50};
  for (int i = 0; i < 5; i++) {
    printf("queue indices: head %d, rear %d\n", q.head_idx, q.rear_idx);
    assert(w_enqueue(&q, &values[i]) == 0);
  }

  // Test for full queue
  int overflow_val = 60;
  assert(w_enqueue(&q, &overflow_val) == -1);

  for (int i = 0; i < 5; i++) {
    int *dequeue_val = (int *)w_dequeue(&q);
    assert(compare_ints(dequeue_val, &values[i]));
  }

  // Test for empty queue
  assert(w_dequeue(&q) == NULL);

  w_clean_queue(&q);
}
