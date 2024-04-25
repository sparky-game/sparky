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
#include <sk_map.h>
#include <sk_defines.h>
#include <sk_texture.h>

sk_map sk_map_create(sk_map_kind kind) {
  return (sk_map) {
    .kind = kind,
    .pbr_shader = LoadShader("assets/shaders/pbr.vert.glsl", "assets/shaders/pbr.frag.glsl")
  };
}

void sk_map_destroy(sk_map *m) {
  UnloadModel(m->floor);
  UnloadModel(m->wall1);
  UnloadModel(m->wall2);
  UnloadModel(m->wall3);
  UnloadShader(m->pbr_shader);
}

void sk_map_load(sk_map *m) {
  m->pbr_shader.locs[SHADER_LOC_MAP_ALBEDO]    = GetShaderLocation(m->pbr_shader, "albedoMap");
  m->pbr_shader.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(m->pbr_shader, "mraMap");
  m->pbr_shader.locs[SHADER_LOC_MAP_NORMAL]    = GetShaderLocation(m->pbr_shader, "normalMap");
  m->pbr_shader.locs[SHADER_LOC_MAP_EMISSION]  = GetShaderLocation(m->pbr_shader, "emissiveMap");
  m->pbr_shader.locs[SHADER_LOC_COLOR_DIFFUSE] = GetShaderLocation(m->pbr_shader, "albedoColor");
  m->pbr_shader.locs[SHADER_LOC_VECTOR_VIEW]   = GetShaderLocation(m->pbr_shader, "viewPos");
  m->floor = LoadModelFromMesh(GenMeshPlane(32, 32, 1, 1));
  assert(m->floor.meshCount == 1);
  assert(m->floor.materialCount == 1);
  // m->floor.materials[0].shader = m->pbr_shader;
  sk_texture_set(SK_TEXTURE_WOOD, &m->floor.materials[0]);
  m->wall1 = LoadModelFromMesh(GenMeshCube(1, 5, 32));
  assert(m->wall1.meshCount == 1);
  assert(m->wall1.materialCount == 1);
  // m->wall1.materials[0].shader = m->pbr_shader;
  sk_texture_set(SK_TEXTURE_STONE1, &m->wall1.materials[0]);
  m->wall2 = LoadModelFromMesh(GenMeshCube(1, 5, 32));
  assert(m->wall2.meshCount == 1);
  assert(m->wall2.materialCount == 1);
  // m->wall2.materials[0].shader = m->pbr_shader;
  sk_texture_set(SK_TEXTURE_STONE1, &m->wall2.materials[0]);
  m->wall3 = LoadModelFromMesh(GenMeshCube(32, 5, 1));
  assert(m->wall3.meshCount == 1);
  assert(m->wall3.materialCount == 1);
  // m->wall3.materials[0].shader = m->pbr_shader;
  sk_texture_set(SK_TEXTURE_STONE1, &m->wall3.materials[0]);
}

void sk_map_draw(sk_map *m) {
  DrawModel(m->floor, (Vector3) { 0, 0, 0 }, 1, WHITE);
  DrawModel(m->wall1, (Vector3) { -16, 2.5f, 0 }, 1, WHITE);
  DrawModel(m->wall2, (Vector3) { 16, 2.5f, 0 }, 1, WHITE);
  DrawModel(m->wall3, (Vector3) { 0, 2.5f, 16 }, 1, WHITE);
}

sk_map_kind sk_map_get_rand(void) {
  return (sk_map_kind) GetRandomValue(0, SK_MAP_MAX_COUNT);
}
