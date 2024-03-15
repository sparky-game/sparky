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


#include <sparky_client.h>
#include <sparky_config.h>
#include <sparky_client_renderer.h>

static Player player = {0};

static void sparky_client_init(void) {
  player = (Player) {
    .camera = (Camera3D) {
      .position = (Vector3) { 0.0f, 2.0f, 4.0f },
      .target = (Vector3) { 0.0f, 2.0f, 0.0f },
      .up = (Vector3) { 0.0f, 1.0f, 0.0f },
      .fovy = SPARKY_CLIENT_FOV,
      .projection = CAMERA_PERSPECTIVE
    }
  };
  sparky_client_renderer_open_window();
}

static int sparky_client_shutdown(void) {
  CloseWindow();
  player = (Player) {0};
  return 0;
}

int sparky_client_run(void) {
  sparky_client_init();
  sparky_client_renderer_loop {
    sparky_client_renderer_update(&player);
    sparky_client_renderer_draw(&player);
  }
  return sparky_client_shutdown();
}
