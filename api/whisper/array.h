#pragma once

#include <sys/types.h>

typedef struct WArray {
  uint full_elm_sz; // the elm sz passed in plus the sizeof the element header.
  uint elm_sz;
  uint num_elms;

  // the general purpose, dynamically allocated buffer for the internal array
  // data.
  void *buffer;
} WArray;

// apply a block to every element in the array.
#define W_ARRAY_ITERATE(block)

// allocate the buffer and fill the passed in WArray pointer.
void w_make_array(WArray *warray, uint elm_sz, uint num_elms);

int w_array_insert(WArray *array, void *data);
void w_array_delete_index(WArray *array, uint index);

// either return a pointer to the data in the buffer, or NULL if it doesn't
// exist.
void *w_array_get(WArray *array, uint index);

void w_clean_array(WArray *array);
