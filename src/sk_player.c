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
#include <sk_player.h>
#include <sk_config.h>
#include <sk_gametypes.h>

#define FILEPATH_BUFFER_MAX_SIZE 64
#define PLAYER_HEIGHT            2
#define GRAVITY                  19
#define JUMP_INIT_VELOCITY       9
#define PEEK_ACCELERATION        1.5
#define WALK_VELOCITY            0.1

void sk_player_create(State *s, sk_player_kind kind) {
  s->player.camera = (Camera3D) {
    .position = (Vector3) { 0, PLAYER_HEIGHT, 4 },
    .target = (Vector3) { 0, 2, 0 },
    .up = (Vector3) { 0, 1, 0 },
    .fovy = SK_CONFIG_CLIENT_FOV,
    .projection = CAMERA_PERSPECTIVE
  };
  s->player.kind = kind;
}

void sk_player_destroy(sk_player *p) {
  sk_weapon_destroy(&p->weapon);
  UnloadModel(p->model);
  p = 0;
}

void sk_player_load(sk_player *p, sk_weapon_kind initial_weapon_kind) {
  char filepath[FILEPATH_BUFFER_MAX_SIZE] = {0};
  sprintf(filepath, "assets/models/%s.glb", sk_player_kinds[p->kind]);
  p->model = LoadModel(filepath);
  sk_weapon_create(p, initial_weapon_kind);
}

void sk_player_jump(sk_player *p) {
  float dt = GetFrameTime();
  if (IsKeyPressed(SK_CONFIG_CLIENT_JUMP) &&
      p->camera.position.y <= PLAYER_HEIGHT) p->v_y = JUMP_INIT_VELOCITY;
  p->v_y -= GRAVITY * dt;
  p->camera.position.y += p->v_y * dt;
  if (p->camera.position.y < PLAYER_HEIGHT) {
    p->camera.position.y = PLAYER_HEIGHT;
    p->v_y = 0;
  }
  else p->camera.target.y += p->v_y * dt;
}

float sk_player_peek(sk_player *p) {
  float cam_roll = 0;
  if (p->camera.up.y >= 0.98f) {
    if (IsKeyDown(SK_CONFIG_CLIENT_PEEK_LEFT))       cam_roll -= PEEK_ACCELERATION;
    else if (IsKeyDown(SK_CONFIG_CLIENT_PEEK_RIGHT)) cam_roll += PEEK_ACCELERATION;
  }
  if (!IsKeyDown(SK_CONFIG_CLIENT_PEEK_LEFT) &&
      !IsKeyDown(SK_CONFIG_CLIENT_PEEK_RIGHT)) {
    p->camera.up.z = 0;
    if (p->camera.up.x) p->camera.up.x *= 0.9f;
    if (p->camera.up.y < 1) p->camera.up.y = 1;
  }
  return cam_roll;
}

void sk_player_move(sk_player *p, float roll) {
  Vector2 dm = GetMouseDelta();
  UpdateCameraPro(&p->camera,
                  (Vector3) {
                    IsKeyDown(SK_CONFIG_CLIENT_MOVE_FORWARD)   * WALK_VELOCITY -
                    IsKeyDown(SK_CONFIG_CLIENT_MOVE_BACKWARDS) * WALK_VELOCITY,
                    IsKeyDown(SK_CONFIG_CLIENT_MOVE_RIGHT)     * WALK_VELOCITY -
                    IsKeyDown(SK_CONFIG_CLIENT_MOVE_LEFT)      * WALK_VELOCITY,
                    0
                  },
                  (Vector3) {
                    dm.x * SK_CONFIG_CLIENT_MOUSE_SENSITIVITY,
                    dm.y * SK_CONFIG_CLIENT_MOUSE_SENSITIVITY,
                    roll
                  },
                  0);
}

void sk_player_draw(sk_player *p) {
  DrawModel(p->model,
            (Vector3) {
              p->camera.position.x - 4,
              p->camera.position.y - PLAYER_HEIGHT,
              p->camera.position.z
            },
            1,
            WHITE);
}
