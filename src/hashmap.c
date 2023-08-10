#include "whisper/hashmap.h"
#include <stdlib.h>
#include <string.h>

static unsigned int w_hm_hash(char *key) {
  unsigned int hash = 0;
  while (*key) {
    hash = (hash << 5) + *key++;
  }
  // bound the key in the actual hashing function.
  return hash % HASHMAP_SIZE;
}

WHashMap *w_create_hm() {
  WHashMap *map = (WHashMap *)malloc(sizeof(WHashMap));
  memset(map->array, 0, sizeof(map->array));
  return map;
}

void w_free_hm(WHashMap *map) {
  for (int i = 0; i < HASHMAP_SIZE; i++) {
    void *current = map->array[i];
    if (current) {
      free(current);
      // don't need to NULL out the ptr, we're freeing the whole map?
    }
  }
  free(map);
}

void w_hm_put(WHashMap *map, char *key, void *value, int value_sz) {
  unsigned int index = w_hm_hash(key);
  void *new_value = malloc(value_sz);
  memcpy(new_value, value, value_sz);
  map->array[index] = new_value;
}

void w_hm_put_no_clone(WHashMap *map, char *key, void *value) {
  unsigned int index = w_hm_hash(key);
  map->array[index] = value;
}

void *w_hm_get(WHashMap *map, char *key) {
  unsigned int index = w_hm_hash(key);
  void *current = map->array[index];
  return current;
}

bool w_hm_delete(WHashMap *map, char *key) {
  unsigned int index = w_hm_hash(key);
  void *current = map->array[index];
  if (current) {
    free(current);
    map->array[index] = NULL;
    return true;
  }
  return false;
}
