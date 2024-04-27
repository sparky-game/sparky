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


#include <assert.h>
#include <sk_log.h>
#include <sk_map_element.h>

sk_map_element sk_map_element_create(sk_map_element_kind kind,
                                     char *name,
                                     sk_texture_kind texture_kind,
                                     f32 w, f32 l, f32 h) {
  sk_map_element e = {
    .id = sk_uuid_gen(),
    .kind = kind,
    .name = name,
    .position = (Vector3) { 0, 0, 0 },
    .scale = 1
  };
  switch (kind) {
  case SK_MAP_ELEMENT_FLOOR:
    e.model = LoadModelFromMesh(GenMeshPlane(w, l, 1, 1));
    break;
  case SK_MAP_ELEMENT_WALL:
    e.model = LoadModelFromMesh(GenMeshCube(w, h, l));
    break;
  }
  assert(e.model.meshCount == 1);
  assert(e.model.materialCount == 1);
  sk_texture_set(texture_kind, &e.model.materials[0]);
  SK_LOG_INFO("sk_map_element_create :: created new element (%s)", e.id.value);
  return e;
}

void sk_map_element_destroy(sk_map_element *e) {
  UnloadModel(e->model);
  SK_LOG_INFO("sk_map_element_destroy :: destroyed element (%s)", e->id.value);
  *e = (sk_map_element) {0};
  e = 0;
}

void sk_map_element_draw(sk_map_element *e) {
  DrawModel(e->model, e->position, e->scale, WHITE);
}

void sk_map_element_rename(sk_map_element *e, char *name) {
  e->name = name;
}

void sk_map_element_move(sk_map_element *e, Vector3 new_position) {
  e->position = new_position;
}

void sk_map_element_scale(sk_map_element *e, f32 scale) {
  e->scale = scale;
}
