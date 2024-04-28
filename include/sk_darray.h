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


#pragma once

#include <sk_defines.h>

typedef struct {
  u32 capacity;
  usz element_size;
  u32 curr_len;
  void *data;
} sk_darray;

sk_darray sk_darray_create(usz element_size);

void sk_darray_destroy(sk_darray *da);

u8 sk_darray_push(sk_darray *da, void *value);

u8 sk_darray_pop(sk_darray *da, void *out_value);

u8 sk_darray_resize(sk_darray *da);
