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
#include <sk_darray.h>

#define INITIAL_CAPACITY 1
#define RESIZE_FACTOR    2

sk_darray sk_darray_create(size_t element_size) {
  return (sk_darray) {
    .capacity = INITIAL_CAPACITY,
    .element_size = element_size,
    .curr_len = 0,
    .data = malloc(INITIAL_CAPACITY * element_size)
  };
}

void sk_darray_destroy(sk_darray *da) {
  if (!da) {
    SK_LOG_WARN("sk_darray_destroy :: `da` is not a valid pointer, skipping destruction");
    return;
  }
  free(da->data);
  *da = (sk_darray) {0};
  da = 0;
}

u8 sk_darray_push(sk_darray *da, void *value) {
  if (!da || !value) {
    SK_LOG_ERROR("sk_darray_push :: `da` and `value` need to be valid pointers");
    return 0;
  }
  if (da->curr_len >= da->capacity && !sk_darray_resize(da)) {
    SK_LOG_ERROR("sk_darray_push :: unable to push value due to failure while resizing");
    return 0;
  }
  memcpy((void *) ((i32 *) da->data + (da->curr_len * da->element_size)), value, da->element_size);
  ++da->curr_len;
  SK_LOG_DEBUG("sk_darray_push :: pushed new value (%u/%u)", da->curr_len, da->capacity);
  return 1;
}

u8 sk_darray_pop(sk_darray *da, void *out_value) {
  if (!da || !out_value) {
    SK_LOG_ERROR("sk_darray_pop :: `da` and `out_value` need to be valid pointers");
    return 0;
  }
  if (!da->curr_len) {
    SK_LOG_ERROR("sk_darray_pop :: dynamic array is empty (%p)", da);
    return 0;
  }
  memcpy(out_value, (void *) ((i32 *) da->data + ((da->curr_len - 1) * da->element_size)), da->element_size);
  --da->curr_len;
  SK_LOG_DEBUG("sk_darray_pop :: popped old value (%u/%u)", da->curr_len, da->capacity);
  return 1;
}

u8 sk_darray_resize(sk_darray *da) {
  if (!da) {
    SK_LOG_ERROR("sk_darray_resize :: `da` need to be a valid pointer");
    return 0;
  }
  void *old_data = da->data;
  u32 old_capacity = da->capacity;
  da->capacity *= RESIZE_FACTOR;
  da->data = realloc(da->data, da->capacity * da->element_size);
  memset(old_data, 0, old_capacity * da->element_size);
  return 1;
}
