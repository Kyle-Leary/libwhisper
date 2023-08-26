#include "whisper/colmap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_cm() {
  WColMap map;

  // Test 1: Creating a ColMap with element size sizeof(int) and initial map size 10
  w_create_cm(&map, sizeof(int), 10);
  assert(map.elm_sz == sizeof(int));
  assert(map.num_elms == 10); // assuming num_elms stores the initial map size
  
  // Test 2: Inserting key-value pairs
  int test_values[3] = {1, 2, 3};
  w_cm_insert(&map, "first", &test_values[0]);
  w_cm_insert(&map, "second", &test_values[1]);
  w_cm_insert(&map, "third", &test_values[2]);

  // Test 3: Getting values by key
  int *value = (int *)w_cm_get(&map, "first");
  assert(*value == 1);
  
  value = (int *)w_cm_get(&map, "second");
  assert(*value == 2);

  value = (int *)w_cm_get(&map, "third");
  assert(*value == 3);

  // Test 4: Deleting a key-value pair
  w_cm_delete(&map, "second");
  value = (int *)w_cm_get(&map, "second");
  assert(value == NULL);

  // Test 5: Cleaning up
  w_free_cm(&map);
  // Add any cleanup validation if necessary
}

