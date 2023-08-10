#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>
#define HASHMAP_SIZE 1024

// hold 64 bits of arbitrary data in each hashmap element for now.
typedef void *WHashMapValue;

typedef struct WHashMap {
  WHashMapValue *array[HASHMAP_SIZE];
} WHashMap;

/* either call this which zero-allocs it for you, or statically zero-alloc it
 yourself. we rely on pointers being NULL when they're not in use. */
WHashMap *w_create_hm();
void w_free_hm(WHashMap *map);

/* stick a bunch of bytes in the pointer, have the hashmap store a copy. */
void w_hm_put(WHashMap *map, char *key, void *value, int value_sz);

/* just stick the actual pointer in there, with no clone. significantly less
 safe. */
void w_hm_put_no_clone(WHashMap *map, char *key, void *value);

void *w_hm_get(WHashMap *map, char *key);

/* return whether it was actually found and deleted or not. */
bool w_hm_delete(WHashMap *map, char *key);

#endif
