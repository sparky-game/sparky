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
#include <sk_rngbuf.h>

sk_rngbuf sk_rngbuf_create(u32 capacity, u32 element_size, u8 overwrite) {
  return (sk_rngbuf) {
    .capacity = capacity,
    .element_size = element_size,
    .overwrite = overwrite ? 1 : 0,
    .curr_len = 0,
    .head = 0,
    .tail = -1,
    .data = malloc(capacity * element_size)
  };
}

void sk_rngbuf_destroy(sk_rngbuf *rb) {
  if (!rb) {
    SK_LOG_WARN("sk_rngbuf_destroy :: `rb` is not a valid pointer, skipping destruction");
    return;
  }
  *rb = (sk_rngbuf) {0};
  rb = 0;
}

u8 sk_rngbuf_push(sk_rngbuf *rb, void *value) {
  if (!rb || !value) {
    SK_LOG_ERROR("sk_rngbuf_push :: `rb` and `value` need to be valid pointers");
    return 0;
  }
  if (!rb->overwrite && rb->curr_len == rb->capacity) {
    SK_LOG_ERROR("sk_rngbuf_push :: ring buffer is full (%p)", rb);
    return 0;
  }
  rb->tail = (rb->tail + 1) % rb->capacity;
  memcpy((void *) ((i32 *) rb->data + (rb->tail * rb->element_size)), value, rb->element_size);
  if (rb->overwrite) rb->curr_len = (rb->curr_len + 1) % rb->capacity;
  else ++rb->curr_len;
  SK_LOG_DEBUG("sk_rngbuf_push :: pushed new value (%u/%u)", rb->curr_len, rb->capacity);
  return 1;
}

u8 sk_rngbuf_pop(sk_rngbuf *rb, void *out_value) {
  if (!rb || !out_value) {
    SK_LOG_ERROR("sk_rngbuf_pop :: `rb` and `out_value` need to be valid pointers");
    return 0;
  }
  if (rb->curr_len == 0) {
    SK_LOG_ERROR("sk_rngbuf_pop :: ring buffer is empty (%p)", rb);
    return 0;
  }
  memcpy(out_value, (void *) ((i32 *) rb->data + (rb->head * rb->element_size)), rb->element_size);
  rb->head = (rb->head + 1) % rb->capacity;
  --rb->curr_len;
  SK_LOG_DEBUG("sk_rngbuf_pop :: popped old value (%u/%u)", rb->curr_len, rb->capacity);
  return 1;
}

u8 sk_rngbuf_peek(const sk_rngbuf *rb, void *out_value) {
  if (!rb || !out_value) {
    SK_LOG_ERROR("sk_rngbuf_peek :: `rb` and `out_value` need to be valid pointers");
    return 0;
  }
  if (rb->curr_len == 0) {
    SK_LOG_ERROR("sk_rngbuf_peek :: ring buffer is empty (%p)", rb);
    return 0;
  }
  memcpy(out_value, (void *) ((i32 *) rb->data + (rb->head * rb->element_size)), rb->element_size);
  return 1;
}
