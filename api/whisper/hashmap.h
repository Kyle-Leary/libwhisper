#ifndef HASHMAP_H
#define HASHMAP_H

#include "whisper/value.h"
#include <stdbool.h>
#include <sys/types.h>

#define HASHMAP_SIZE 1024

typedef Value64 WHashMapValue;

typedef WHashMapValue WHashMap[HASHMAP_SIZE];

/* either call this which zero-allocs it for you, or statically zero-alloc it
 yourself. we rely on pointers being NULL when they're not in use. */
void w_create_hm(WHashMap dest);
void w_free_hm(WHashMap map);

/* stick a bunch of bytes in the pointer, have the hashmap store a copy. */
void w_hm_put_ptr_clone(WHashMap map, const char *key, WHashMapValue value,
                        int value_sz);
/* store the actual value passed in. */
void w_hm_put_direct_value(WHashMap map, const char *key, WHashMapValue value);

WHashMapValue w_hm_get(WHashMap map, const char *key);

bool w_hm_delete_ptr(WHashMap map, const char *key);
bool w_hm_delete_value(WHashMap map, const char *key);

WHashMapValue w_hm_get(WHashMap map, const char *key);

/* return whether it was actually found and deleted or not. */
bool w_hm_delete(WHashMap map, const char *key);

#endif
