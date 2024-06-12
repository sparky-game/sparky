/*
 * GNU Sparky --- A 5v5 character-based libre tactical shooter
 * Copyright (C) 2024 Wasym A. Alonso
 *
 * This file is part of Sparky.
 *
 * Sparky is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Sparky is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sparky.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdlib.h>
#include <string.h>
#include <sk_log.h>
#include <sk_hashmap.h>

#define HASH_MULTIPLIER 97

static u64 hash(const char *name, u32 n) {
  u64 hash = 0;
  for (const u8 *us = (const u8 *) name; *us; ++us) hash = (hash * HASH_MULTIPLIER) + *us;
  return hash % n;
}

sk_hashmap sk_hashmap_create(u32 capacity, usz element_size) {
  return (sk_hashmap) {
    .capacity = capacity,
    .element_size = element_size,
    .data = malloc((usz) capacity * element_size)
  };
}

void sk_hashmap_destroy(sk_hashmap *hm) {
  if (!hm) {
    SK_LOG_WARN("sk_hashmap_destroy :: `hm` is not a valid pointer, skipping destruction");
    return;
  }
  free(hm->data);
  *hm = (sk_hashmap) {0};
  hm = 0;
}

u8 sk_hashmap_set(sk_hashmap *hm, const char *name, void *value) {
  if (!hm || !name || !value) {
    SK_LOG_ERROR("sk_hashmap_set :: `hm`, `name` and `value` need to be valid pointers");
    return 0;
  }
  memcpy((void *) ((u8 *) hm->data + (hash(name, hm->capacity) * hm->element_size)), value, hm->element_size);
  return 1;
}

u8 sk_hashmap_get(sk_hashmap *hm, const char *name, void *out_value) {
  if (!hm || !name || !out_value) {
    SK_LOG_ERROR("sk_hashmap_set :: `hm`, `name` and `out_value` need to be valid pointers");
    return 0;
  }
  memcpy(out_value, (void *) ((u8 *) hm->data + (hash(name, hm->capacity) * hm->element_size)), hm->element_size);
  return 1;
}
