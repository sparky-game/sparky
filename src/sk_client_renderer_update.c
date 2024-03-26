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
#include <sk_config.h>
#include <sk_defines.h>
#include <sk_client_renderer.h>

#define MODEL_PLAYER_JETT "assets/models/jett/scene.gltf"

static inline void __load_player(State *s) {
  s->player.model = LoadModel(MODEL_PLAYER_JETT);
  sk_weapon_create(&s->player, SK_WEAPON_KIND_7MM);
  assert(s->player.weapon.model_anims_count == 1);
  assert(IsModelAnimationValid(s->player.weapon.model, s->player.weapon.model_anims[0]));
}

static void __update_main_menu(State *s) {
  if (IsKeyPressed(KEY_ENTER)) {
    s->current_scene = SCENE_GAMEPLAY;
    __load_player(s);
    DisableCursor();
  }
}

static void __update_gameplay_jump(State *s) {
  float dt = GetFrameTime();
  if (IsKeyPressed(SK_CONFIG_CLIENT_JUMP) &&
      s->player.camera.position.y <= SK_CLIENT_PLAYER_HEIGHT) s->player.v_y = SK_CLIENT_PLAYER_JUMP_INIT_VELOCITY;
  s->player.v_y -= SK_CLIENT_GRAVITY * dt;
  s->player.camera.position.y += s->player.v_y * dt;
  if (s->player.camera.position.y < SK_CLIENT_PLAYER_HEIGHT) {
    s->player.camera.position.y = SK_CLIENT_PLAYER_HEIGHT;
    s->player.v_y = 0;
  }
  else s->player.camera.target.y += s->player.v_y * dt;
}

static inline void __update_gameplay_shoot(State *s) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) sk_weapon_shoot(&s->player.weapon);
}

static float __update_gameplay_cam_roll(State *s) {
  float cam_roll = 0;
  if (s->player.camera.up.y >= 0.98f) {
    if (IsKeyDown(SK_CONFIG_CLIENT_PEEK_LEFT))       cam_roll -= SK_CLIENT_PLAYER_CAM_ROLL_ACCELERATION;
    else if (IsKeyDown(SK_CONFIG_CLIENT_PEEK_RIGHT)) cam_roll += SK_CLIENT_PLAYER_CAM_ROLL_ACCELERATION;
  }
  if (!IsKeyDown(SK_CONFIG_CLIENT_PEEK_LEFT) &&
      !IsKeyDown(SK_CONFIG_CLIENT_PEEK_RIGHT)) {
    s->player.camera.up.z = 0;
    if (s->player.camera.up.x) s->player.camera.up.x *= 0.9f;
    if (s->player.camera.up.y < 1) s->player.camera.up.y = 1;
  }
  return cam_roll;
}

static void __update_gameplay(State *s) {
  __update_gameplay_jump(s);
  __update_gameplay_shoot(s);
  Vector2 dm = GetMouseDelta();
  UpdateCameraPro(&s->player.camera,
                  (Vector3) {
                    IsKeyDown(SK_CONFIG_CLIENT_MOVE_FORWARD)   * SK_CLIENT_PLAYER_CAM_WALK_SENSITIVITY -
                    IsKeyDown(SK_CONFIG_CLIENT_MOVE_BACKWARDS) * SK_CLIENT_PLAYER_CAM_WALK_SENSITIVITY,
                    IsKeyDown(SK_CONFIG_CLIENT_MOVE_RIGHT)     * SK_CLIENT_PLAYER_CAM_WALK_SENSITIVITY -
                    IsKeyDown(SK_CONFIG_CLIENT_MOVE_LEFT)      * SK_CLIENT_PLAYER_CAM_WALK_SENSITIVITY,
                    0
                  },
                  (Vector3) {
                    dm.x * SK_CONFIG_CLIENT_MOUSE_SENSITIVITY,
                    dm.y * SK_CONFIG_CLIENT_MOUSE_SENSITIVITY,
                    __update_gameplay_cam_roll(s)
                  },
                  0);
}

void sk_client_renderer_update(State *s) {
  switch (s->current_scene) {
  case SCENE_MAIN_MENU:
    __update_main_menu(s);
    break;
  case SCENE_GAMEPLAY:
    __update_gameplay(s);
    break;
  default:
    assert(0 && "Unreachable");
  }
}
