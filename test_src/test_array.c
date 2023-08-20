#include "whisper/array.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stuff {
  float x;
  int y;
  char z;
} Stuff;

void test_array_with_stuff() {
  WArray array;

  // Test 5: Creating an array with 5 elements of size sizeof(Stuff)
  w_make_array(&array, sizeof(Stuff), 5);
  assert(array.elm_sz == sizeof(Stuff));
  assert(array.num_elms == 5);

  // Test 6: Inserting elements of type Stuff
  for (int i = 0; i < 5; i++) {
    Stuff value = {i * 1.0f, i * 2, 'A' + i};
    w_array_insert(&array, &value);
  }
  for (int i = 0; i < 5; i++) {
    Stuff *value = (Stuff *)w_array_get(&array, i);
    assert(value->x == i * 1.0f);
    assert(value->y == i * 2);
    assert(value->z == 'A' + i);
  }

  // Test 7: Deleting elements and verifying NULL for deleted index
  w_array_delete_index(&array, 2);
  Stuff *value_after_delete = (Stuff *)w_array_get(&array, 2);
  assert(value_after_delete == NULL);

  // Test 8: Verifying other elements after deletion
  Stuff *value_after_delete_3 = (Stuff *)w_array_get(&array, 3);
  assert(value_after_delete_3->x == 3.0f);
  assert(value_after_delete_3->y == 6);
  assert(value_after_delete_3->z == 'D');

  // Test 9: Cleaning up
  w_clean_array(&array);
  assert(array.buffer == NULL);
}

void test_array() {
  WArray array;

  // Test 1: Creating an array with 5 elements of size sizeof(int)
  w_make_array(&array, sizeof(int), 5);
  assert(array.elm_sz == sizeof(int));
  assert(array.num_elms == 5);

  // Test 2: Inserting elements
  for (int i = 0; i < 5; i++) {
    int value = i * i;
    w_array_insert(&array, &value);
    assert(array.upper_bound == (i + 1));
  }
  for (int i = 0; i < 5; i++) {
    int *value = (int *)w_array_get(&array, i);
    assert(*value == i * i);
  }

  // Test 3: Deleting elements
  w_array_delete_index(&array, 2);
  int *value_after_delete = (int *)w_array_get(&array, 2);
  assert(value_after_delete == NULL);

  assert(array.upper_bound == 5);
  w_array_delete_index(&array, 4);
  assert(array.upper_bound == 4);

  // Test 4: Cleaning up
  w_clean_array(&array);

  test_array_with_stuff();

  assert(array.buffer == NULL);
}
