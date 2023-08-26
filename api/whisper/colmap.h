#pragma once

/*
 * very similar interface to a hashmap, but the implementation is using a warray
 * so it has basic/fast collision detection.
 * */

#include "whisper/array.h"
#include "whisper/value.h"
#include <stdbool.h>
#include <sys/types.h>

typedef WArray WColMap;

void w_create_cm(WColMap *dest, int elm_sz, int map_sz);

void w_free_cm(WColMap *map);

int w_cm_insert(WColMap *map, const char *key, void *value);

void *w_cm_get(WColMap *map, const char *key);

void w_cm_delete(WColMap *map, const char *key);
