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

#include <raylib.h>
#include <sk_uuid.h>
#include <sk_defines.h>
#include <sk_texture.h>

typedef enum {
  SK_MAP_ELEMENT_FLOOR,
  SK_MAP_ELEMENT_WALL
} sk_map_element_kind;

typedef struct {
  sk_uuid id;
  sk_map_element_kind kind;
  char *name;
  Model model;
  Vector3 position;
  f32 scale;
} sk_map_element;

sk_map_element sk_map_element_create(sk_map_element_kind kind,
                                     char *name,
                                     sk_texture_kind texture_kind,
                                     f32 w, f32 l, f32 h);

void sk_map_element_destroy(sk_map_element *e);

void sk_map_element_draw(sk_map_element *e);

void sk_map_element_rename(sk_map_element *e, char *name);

void sk_map_element_move(sk_map_element *e, Vector3 new_position);

void sk_map_element_scale(sk_map_element *e, f32 scale);
