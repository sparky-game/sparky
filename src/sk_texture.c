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


#include <sk_texture.h>

#define TEXTURE_PATH_PLACEHOLDER "assets/textures/%s/%s.png"

void sk_texture_set(sk_texture_kind kind, Material *m) {
  const char * const name = sk_texture_kind2name[kind];
  m->maps[MATERIAL_MAP_ALBEDO].texture = LoadTexture(TextFormat(TEXTURE_PATH_PLACEHOLDER, name, "albedo"));
  m->maps[MATERIAL_MAP_NORMAL].texture = LoadTexture(TextFormat(TEXTURE_PATH_PLACEHOLDER, name, "normal"));
  m->maps[MATERIAL_MAP_ROUGHNESS].texture = LoadTexture(TextFormat(TEXTURE_PATH_PLACEHOLDER, name, "roughness"));
  m->maps[MATERIAL_MAP_HEIGHT].texture = LoadTexture(TextFormat(TEXTURE_PATH_PLACEHOLDER, name, "height"));
  m->maps[MATERIAL_MAP_OCCLUSION].texture = LoadTexture(TextFormat(TEXTURE_PATH_PLACEHOLDER, name, "ao"));
}
