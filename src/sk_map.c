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


#include <sk_map.h>
#include <sk_log.h>
#include <sk_defines.h>
#include <sk_texture.h>

sk_map_kind sk_map_get_rand(void) {
  return (sk_map_kind) GetRandomValue(0, SK_MAP_MAX_COUNT);
}

sk_map sk_map_create(sk_map_kind kind) {
  return (sk_map) {
    .kind = kind,
    .pbr_shader = LoadShader("assets/shaders/pbr.vert.glsl", "assets/shaders/pbr.frag.glsl"),
    .elements = sk_darray_create(sizeof(sk_map_element))
  };
}

void sk_map_destroy(sk_map *m) {
  sk_map_unload(m);
  sk_darray_destroy(&m->elements);
  UnloadShader(m->pbr_shader);
}

void sk_map_add_element(sk_darray *es,
                        sk_map_element_kind kind,
                        char *name,
                        sk_texture_kind texture_kind,
                        f32 w, f32 l, f32 h,
                        Vector3 draw_pos) {
  sk_map_element e = sk_map_element_create(kind, name, texture_kind, w, l, h);
  sk_map_element_move(&e, draw_pos);
  if (!sk_darray_push(es, &e)) SK_LOG_ERROR("sk_map_add_element :: unable to add new element");
}

void sk_map_load(sk_map *m) {
  m->pbr_shader.locs[SHADER_LOC_MAP_ALBEDO]    = GetShaderLocation(m->pbr_shader, "albedoMap");
  m->pbr_shader.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(m->pbr_shader, "mraMap");
  m->pbr_shader.locs[SHADER_LOC_MAP_NORMAL]    = GetShaderLocation(m->pbr_shader, "normalMap");
  m->pbr_shader.locs[SHADER_LOC_MAP_EMISSION]  = GetShaderLocation(m->pbr_shader, "emissiveMap");
  m->pbr_shader.locs[SHADER_LOC_COLOR_DIFFUSE] = GetShaderLocation(m->pbr_shader, "albedoColor");
  m->pbr_shader.locs[SHADER_LOC_VECTOR_VIEW]   = GetShaderLocation(m->pbr_shader, "viewPos");
  sk_map_add_element(&m->elements,
                     SK_MAP_ELEMENT_FLOOR,
                     "floor",
                     SK_TEXTURE_WOOD,
                     32, 32, 0,
                     (Vector3) { 0, 0, 0 });
  sk_map_add_element(&m->elements,
                     SK_MAP_ELEMENT_WALL,
                     "wall1",
                     SK_TEXTURE_STONE1,
                     1, 32, 5,
                     (Vector3) { -16, 2.5f, 0 });
  sk_map_add_element(&m->elements,
                     SK_MAP_ELEMENT_WALL,
                     "wall2",
                     SK_TEXTURE_STONE1,
                     1, 32, 5,
                     (Vector3) { 16, 2.5f, 0 });
  sk_map_add_element(&m->elements,
                     SK_MAP_ELEMENT_WALL,
                     "wall3",
                     SK_TEXTURE_STONE1,
                     32, 1, 5,
                     (Vector3) { 0, 2.5f, 16 });
  sk_map_add_element(&m->elements,
                     SK_MAP_ELEMENT_WALL,
                     "wall4",
                     SK_TEXTURE_STONE1,
                     32, 1, 5,
                     (Vector3) { 0, 2.5f, -16 });
}

void sk_map_unload(sk_map *m) {
  sk_map_element e = {0};
  while (m->elements.curr_len) {
    if (!sk_darray_pop(&m->elements, &e)) SK_LOG_ERROR("sk_map_unload :: unable to delete element");
    sk_map_element_destroy(&e);
  }
}

void sk_map_draw(sk_map *m) {
  for (u32 i = 0; i < m->elements.curr_len; ++i) {
    sk_map_element_draw(&((sk_map_element *) m->elements.data)[i]);
  }
}
