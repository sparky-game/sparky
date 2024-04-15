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

typedef enum {
  SK_MAP_CAMPING
} sk_map_kind;

typedef struct {
  sk_map_kind kind;
  Shader pbr_shader;
  Model floor;
  Model wall1;
  Model wall2;
  Model wall3;
} sk_map;

sk_map sk_map_create(sk_map_kind kind);

void sk_map_destroy(sk_map *m);

void sk_map_load(sk_map *m);

void sk_map_draw(sk_map *m);
