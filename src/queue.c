#include "whisper/queue.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void w_make_queue(WQueue *wqueue, uint elm_sz, uint num_elms) {
  wqueue->num_elms = num_elms;
  wqueue->elm_sz = elm_sz;
  wqueue->head_idx = 0;
  wqueue->rear_idx = 0;

  wqueue->active_elements = 0;

  // setup ringbuffer.
  wqueue->buffer = calloc(elm_sz, num_elms);
}

int w_enqueue(WQueue *queue, void *data) {
  if (queue->active_elements == queue->num_elms) {
    // no room.
    return -1;
  }

  uint i_elm_offset = queue->elm_sz * queue->rear_idx;
  uint8_t *i_elm_ptr = (uint8_t *)queue->buffer + i_elm_offset;

  queue->rear_idx++;
  queue->rear_idx %= queue->num_elms;

  queue->active_elements++;

  // memcpy the pointer into the right slot.
  { memcpy(i_elm_ptr, data, queue->elm_sz); }

  return 0;
}

void *w_dequeue(WQueue *queue) {
  if (queue->active_elements != 5 && queue->rear_idx == queue->head_idx) {
    return NULL;
  }

  uint index_elm_offset = queue->elm_sz * queue->head_idx;
  uint8_t *index_elm_ptr = (uint8_t *)queue->buffer + index_elm_offset;

  queue->head_idx++;
  queue->head_idx %= queue->num_elms;

  queue->active_elements--;

  // try to use this memory as soon as you dequeue it, safety is not guaranteed
  // and it won't stay forever, it might be bumped out.
  return index_elm_ptr;
}

void w_clean_queue(WQueue *queue) {
  free(queue->buffer);
  queue->buffer = NULL;
  // don't free the queue, we haven't necessarily alloced that on the heap.
}
