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
  SK_TEXTURE_GRASS1,
  SK_TEXTURE_GRASS2,
  SK_TEXTURE_LAVA,
  SK_TEXTURE_METAL,
  SK_TEXTURE_ROCK,
  SK_TEXTURE_ROOF,
  SK_TEXTURE_SAND,
  SK_TEXTURE_SNOW,
  SK_TEXTURE_STONE1,
  SK_TEXTURE_STONE2,
  SK_TEXTURE_TERRAIN,
  SK_TEXTURE_TILE,
  SK_TEXTURE_WOOD
} sk_texture_kind;

typedef struct {
  sk_texture_kind kind;
} sk_texture;

static const char * const sk_texture_kind2name[] = {
  [SK_TEXTURE_GRASS1] = "grass1",
  [SK_TEXTURE_GRASS2] = "grass2",
  [SK_TEXTURE_LAVA] = "lava",
  [SK_TEXTURE_METAL] = "metal",
  [SK_TEXTURE_ROCK] = "rock",
  [SK_TEXTURE_ROOF] = "roof",
  [SK_TEXTURE_SAND] = "sand",
  [SK_TEXTURE_SNOW] = "snow",
  [SK_TEXTURE_STONE1] = "stone1",
  [SK_TEXTURE_STONE2] = "stone2",
  [SK_TEXTURE_TERRAIN] = "terrain",
  [SK_TEXTURE_TILE] = "tile",
  [SK_TEXTURE_WOOD] = "wood"
};

void sk_texture_set(sk_texture_kind kind, Material *m);
