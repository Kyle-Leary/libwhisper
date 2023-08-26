#pragma once

#include <sys/types.h>

typedef struct WArray {
  uint full_elm_sz; // the elm sz passed in plus the sizeof the element header.
  uint elm_sz;
  uint num_elms;

  uint upper_bound; // so that we don't have to loop over the whole array and
                    // check for NULLs in each blank spot, we keep an upper
                    // bound. use this in for loop iterators.

  // the general purpose, dynamically allocated buffer for the internal array
  // data.
  void *buffer;
} WArray;

// allocate the buffer and fill the passed in WArray pointer.
void w_make_array(WArray *warray, uint elm_sz, uint num_elms);

int w_array_insert(WArray *array, void *data);
void w_array_delete_index(WArray *array, uint index);

// this method will return a nonzero value when something is found in the slot.
int w_array_insert_index(WArray *array, uint index, void *data);

// either return a pointer to the data in the buffer, or NULL if it doesn't
// exist.
void *w_array_get(WArray *array, uint index);

void w_clean_array(WArray *array);
