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


#include <sk_config.h>
#include <sk_client.h>
#include <sk_gametypes.h>
#include <sk_client_renderer.h>

static State state = {0};

static void __init(void) {
  if (!ChangeDirectory(GetApplicationDirectory())) {
    TraceLog(LOG_WARNING, "Could not change CWD to the game's root directory");
  }
  sk_client_renderer_init();
  state = (State) {
    .current_scene = SCENE_MAIN_MENU,
    .player = (Player) {
      .camera = (Camera3D) {
        .position = (Vector3) { 0, SK_CLIENT_PLAYER_HEIGHT, 4 },
        .target = (Vector3) { 0, 2, 0 },
        .up = (Vector3) { 0, 1, 0 },
        .fovy = SK_CONFIG_CLIENT_FOV,
        .projection = CAMERA_PERSPECTIVE
      }
    },
  };
}

static u8 __shutdown(void) {
  sk_weapon_destroy(&state.player.weapon);
  UnloadModel(state.player.model);
  CloseAudioDevice();
  CloseWindow();
  state = (State) {0};
  TraceLog(LOG_INFO, "%s closed successfully", SK_CLIENT_NAME);
  return 0;
}

u8 sk_client_run(void) {
  TraceLog(LOG_INFO, "Initializing %s", SK_CLIENT_NAME);
  __init();
  sk_client_renderer_loop {
    sk_client_renderer_update(&state);
    sk_client_renderer_draw(&state);
  }
  return __shutdown();
}
