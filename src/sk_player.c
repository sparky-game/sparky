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


#include <stdio.h>
#include <assert.h>
#include <sk_player.h>

#define PLAYER_HEIGHT          2
#define GRAVITY                20
#define JUMP_INIT_VELOCITY     9
#define PEEK_ACCELERATION      1.5
#define WALK_VELOCITY          14
#define MODEL_PATH_PLACEHOLDER "assets/models/%s.glb"

sk_player sk_player_create(i8 lobby_id, i8 lobby_slot_idx, sk_player_kind kind, sk_config *config) {
  assert(lobby_id != -1);
  assert(lobby_slot_idx != -1);
  return (sk_player) {
    .lobby_id = lobby_id,
    .lobby_slot_idx = lobby_slot_idx,
    .kind = kind,
    .camera = (Camera3D) {
      .position = (Vector3) { 0, PLAYER_HEIGHT, 4 },
      .target = (Vector3) { 0, 2, 0 },
      .up = (Vector3) { 0, 1, 0 },
      .fovy = config->general.fov,
      .projection = CAMERA_PERSPECTIVE
    },
    .hp = 100
  };
}

void sk_player_destroy(sk_player *p) {
  sk_weapon_destroy(&p->weapon);
  UnloadModel(p->model);
  p = 0;
}

void sk_player_load(sk_player *p, sk_weapon_kind initial_weapon_kind) {
  p->model = LoadModel(TextFormat(MODEL_PATH_PLACEHOLDER, sk_player_kinds[p->kind]));
  p->weapon = sk_weapon_create(initial_weapon_kind);
}

void sk_player_jump(sk_player *p, sk_config *config) {
  f32 dt = GetFrameTime();
  if (IsKeyPressed(config->controls.jump) &&
      p->camera.position.y <= PLAYER_HEIGHT) p->v_y = JUMP_INIT_VELOCITY;
  p->v_y -= GRAVITY * dt;
  p->camera.position.y += p->v_y * dt;
  if (p->camera.position.y < PLAYER_HEIGHT) {
    p->camera.position.y = PLAYER_HEIGHT;
    p->v_y = 0;
  }
  else p->camera.target.y += p->v_y * dt;
}

f32 sk_player_peek(sk_player *p, sk_config *config) {
  f32 cam_roll = 0;
  if (p->camera.up.y >= 0.98f) {
    if (IsKeyDown(config->controls.peek_left))       cam_roll -= PEEK_ACCELERATION;
    else if (IsKeyDown(config->controls.peek_right)) cam_roll += PEEK_ACCELERATION;
  }
  if (!IsKeyDown(config->controls.peek_left) &&
      !IsKeyDown(config->controls.peek_right)) {
    p->camera.up.z = 0;
    if (p->camera.up.x) p->camera.up.x *= 0.9f;
    if (p->camera.up.y < 1) p->camera.up.y = 1;
  }
  return cam_roll;
}

void sk_player_move(sk_player *p, sk_config *config, f32 roll) {
  f32 dt = GetFrameTime();
  Vector2 dm = GetMouseDelta();
  UpdateCameraPro(&p->camera,
                  (Vector3) {
                    (IsKeyDown(config->controls.move_forward) - IsKeyDown(config->controls.move_backwards)) * WALK_VELOCITY * dt,
                    (IsKeyDown(config->controls.move_right) - IsKeyDown(config->controls.move_left)) * WALK_VELOCITY * dt,
                    0
                  },
                  (Vector3) {
                    config->general.mouse_sensitivity * dm.x,
                    config->general.mouse_sensitivity * dm.y,
                    roll
                  },
                  0);
}

void sk_player_draw(sk_player *p) {
  DrawModelEx(p->model,
              (Vector3) {
                p->camera.position.x - 4,
                p->camera.position.y - PLAYER_HEIGHT,
                p->camera.position.z
              },
              (Vector3) { 0, 1, 0 },
              90,
              (Vector3) { 0.001f, 0.001f, 0.001f },
              WHITE);
}
