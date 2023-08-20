#pragma once

#include <sys/types.h>

// a simple generic queue implemented over a ring buffer.

typedef struct WQueue {
  uint elm_sz;
  uint num_elms;

  // instead of a linked list, we're just using direct indices into the ring
  // buffer.
  uint head_idx;
  uint rear_idx;

  uint active_elements; // how many slots are in active use?

  // the queue/ringbuffer data.
  void *buffer;
} WQueue;

void w_make_queue(WQueue *wqueue, uint elm_sz, uint num_elms);

// put into the back of the queue.
// return -1 if unsuccessful.
int w_enqueue(WQueue *queue, void *data);
// pop from the head of the queue, return the pointer to the element.
// return NULL if there are no elements.
void *w_dequeue(WQueue *queue);

void w_clean_queue(WQueue *queue);
