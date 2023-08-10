#include "whisper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_VALUE_SIZE 64

static void test_create_and_free() {
  WHashMap *map = w_create_hm();
  w_free_hm(map);
  printf("Test create and free passed\n");
}

static void test_put_and_get() {
  WHashMap *map = w_create_hm();

  char key[] = "my_key";
  char value[] = "value123";
  w_hm_put(map, key, value, sizeof(value));

  char *retrieved_value = (char *)w_hm_get(map, key);

  if (strcmp(retrieved_value, value) == 0) {
    printf("Test put and get passed\n");
  } else {
    printf("Test put and get failed\n");
  }

  w_free_hm(map);
}

static void test_delete() {
  WHashMap *map = w_create_hm();

  char key[] = "my_key";
  char value[] = "value123";
  w_hm_put(map, key, value, sizeof(value));

  if (w_hm_delete(map, key)) {
    printf("Test delete passed\n");
  } else {
    printf("Test delete failed\n");
  }

  if (w_hm_get(map, key) == NULL) {
    printf("Test delete verification passed\n");
  } else {
    printf("Test delete verification failed\n");
  }

  w_free_hm(map);
}

static void test_no_clone() {
  WHashMap *map = w_create_hm();

  char key[] = "my_key";
  char *value = (char *)malloc(TEST_VALUE_SIZE);
  snprintf(value, TEST_VALUE_SIZE, "no_clone_value");

  w_hm_put_no_clone(map, key, value);

  char *retrieved_value = (char *)w_hm_get(map, key);

  if (strcmp(retrieved_value, value) == 0) {
    printf("Test no clone passed\n");
  } else {
    printf("Test no clone failed\n");
  }

  w_free_hm(map);
}

void test_hm() {
  test_create_and_free();
  test_put_and_get();
  test_delete();
  test_no_clone();
}
