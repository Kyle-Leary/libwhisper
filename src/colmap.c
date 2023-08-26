#include "whisper/colmap.h"
#include "whisper/array.h"

static unsigned int cmhash(const char *key, int map_sz) {
  unsigned int hash = 0;
  while (*key) {
    // arg is a "const char *" since *key++ is modifying the copied pointer THEN
    // dereffing.
    hash = (hash << 5) + *key++;
  }
  // bound the key in the actual hashing function.
  return hash % map_sz;
}

void w_create_cm(WColMap *dest, int elm_sz, int map_sz) {
  w_make_array(dest, elm_sz, map_sz);
}

void w_free_cm(WColMap *map) { w_clean_array(map); }

int w_cm_insert(WColMap *map, const char *key, void *value) {
  return w_array_insert_index(map, cmhash(key, map->num_elms), value);
}

void *w_cm_get(WColMap *map, const char *key) {
  return w_array_get(map, cmhash(key, map->num_elms));
}

void w_cm_delete(WColMap *map, const char *key) {
  w_array_delete_index(map, cmhash(key, map->num_elms));
}
