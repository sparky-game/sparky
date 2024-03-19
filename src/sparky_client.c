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


#include <sparky_config.h>
#include <sparky_defines.h>
#include <sparky_gametypes.h>
#include <sparky_client_renderer.h>

static State state = {0};

static void sparky_client_init(void) {
  sparky_client_renderer_open_window();
  state = (State) {
    .current_scene = SCENE_MAIN_MENU,
    .player = (Player) {
      .camera = (Camera3D) {
        .position = (Vector3) { 0, SPARKY_CLIENT_PLAYER_HEIGHT, 4 },
        .target = (Vector3) { 0, 2, 0 },
        .up = (Vector3) { 0, 1, 0 },
        .fovy = SPARKY_CONFIG_CLIENT_FOV,
        .projection = CAMERA_PERSPECTIVE
      },
      .model = LoadModelFromMesh(GenMeshCylinder(1, 2, 16))
    },
  };
}

static int sparky_client_shutdown(void) {
  CloseWindow();
  state = (State) {0};
  TraceLog(LOG_INFO, "%s closed successfully", SPARKY_CLIENT_NAME);
  return 0;
}

int sparky_client_run(void) {
  TraceLog(LOG_INFO, "Initializing %s", SPARKY_CLIENT_NAME);
  sparky_client_init();
  sparky_client_renderer_loop {
    sparky_client_renderer_update(&state);
    sparky_client_renderer_draw(&state);
  }
  return sparky_client_shutdown();
}
