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
#include <sparky_config.h>
#include <sparky_defines.h>
#include <sparky_client_renderer.h>

#define CAM_WALK_SENSITIVITY 0.1
#define CAM_ROLL_ACCELERATION 1.5

void sparky_client_renderer_open_window(void) {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(SPARKY_CONFIG_CLIENT_WIN_WIDTH,
             SPARKY_CONFIG_CLIENT_WIN_HEIGHT,
             SPARKY_CLIENT_NAME);
  SetTargetFPS(SPARKY_CONFIG_CLIENT_FPS);
}

static void sparky_client_renderer_update_main_menu(State *s) {
  if (IsKeyPressed(KEY_ENTER)) {
    s->current_scene = SCENE_GAMEPLAY;
    DisableCursor();
  }
}

static void sparky_client_renderer_update_gameplay(State *s) {
  Vector2 dm = GetMouseDelta();
  float cam_roll = 0;
  if (s->player.camera.up.y >= 0.98f) {
    if (IsKeyDown(SPARKY_CONFIG_CLIENT_PEEK_LEFT))       cam_roll += CAM_ROLL_ACCELERATION;
    else if (IsKeyDown(SPARKY_CONFIG_CLIENT_PEEK_RIGHT)) cam_roll -= CAM_ROLL_ACCELERATION;
  }
  if (!IsKeyDown(SPARKY_CONFIG_CLIENT_PEEK_LEFT) &&
      !IsKeyDown(SPARKY_CONFIG_CLIENT_PEEK_RIGHT)) {
    s->player.camera.up.z = 0;
    if (s->player.camera.up.x) s->player.camera.up.x *= 0.9f;
    if (s->player.camera.up.y < 1) s->player.camera.up.y = 1;
  }
  UpdateCameraPro(&s->player.camera,
                  (Vector3) {
                    IsKeyDown(SPARKY_CONFIG_CLIENT_MOVE_FORWARD) * CAM_WALK_SENSITIVITY -
                    IsKeyDown(SPARKY_CONFIG_CLIENT_MOVE_BACKWARDS) * CAM_WALK_SENSITIVITY,
                    IsKeyDown(SPARKY_CONFIG_CLIENT_MOVE_RIGHT) * CAM_WALK_SENSITIVITY -
                    IsKeyDown(SPARKY_CONFIG_CLIENT_MOVE_LEFT) * CAM_WALK_SENSITIVITY,
                    0
                  },
                  (Vector3) {
                    dm.x * SPARKY_CONFIG_CLIENT_MOUSE_SENSITIVITY,
                    dm.y * SPARKY_CONFIG_CLIENT_MOUSE_SENSITIVITY,
                    cam_roll
                  },
                  0);
}

void sparky_client_renderer_update(State *s) {
  switch (s->current_scene) {
  case SCENE_MAIN_MENU:
    sparky_client_renderer_update_main_menu(s);
    break;
  case SCENE_GAMEPLAY:
    sparky_client_renderer_update_gameplay(s);
    break;
  default:
    assert(0 && "sparky_client_renderer_update :: Unreachable");
    break;
  }
}

static void sparky_client_renderer_draw_main_menu(void) {
  ClearBackground(BLACK);
  const char *subtitle = "Press <ENTER> to start";
  int subtitle_size = 30;
  DrawText(SPARKY_CLIENT_MAIN_MENU_TITLE,
           (GetScreenWidth() - MeasureText(SPARKY_CLIENT_MAIN_MENU_TITLE,
                                           SPARKY_CLIENT_MAIN_MENU_TITLE_SIZE)) / 2,
           (GetScreenHeight() - MeasureText(SPARKY_CLIENT_MAIN_MENU_TITLE,
                                            SPARKY_CLIENT_MAIN_MENU_TITLE_SIZE)) / 2,
           SPARKY_CLIENT_MAIN_MENU_TITLE_SIZE,
           RAYWHITE);
  DrawText(subtitle,
           (GetScreenWidth() - MeasureText(subtitle, subtitle_size)) / 2,
           ((GetScreenHeight() - MeasureText(subtitle, subtitle_size)) / 2) + 115,
           subtitle_size,
           RAYWHITE);
}

static void sparky_client_renderer_draw_gameplay_world(State *s) {
  ClearBackground(SKYBLUE);
  BeginMode3D(s->player.camera);
  DrawModel(s->player.model,
            Vector3Subtract(s->player.camera.position, (Vector3) { 0, 2, 0 }),
            1, PURPLE);
  DrawPlane((Vector3) { 0, 0, 0 },
            (Vector2) { 32, 32 },
            DARKGRAY);
  DrawCube((Vector3) { -16, 2.5f, 0 },
           1, 5, 32, RED);
  DrawCube((Vector3) { 16, 2.5f, 0 },
           1, 5, 32, LIME);
  DrawCube((Vector3) { 0, 2.5f, 16 },
           32, 5, 1, GOLD);
  EndMode3D();
}

static void sparky_client_renderer_draw_gameplay_hud(void) {
  DrawFPS(10, 10);
  char dt[10];
  snprintf(dt, sizeof(dt), "%.4f ms", GetFrameTime() * 1000);
  DrawText(dt, 10, 33, 20, LIME);
}

void sparky_client_renderer_draw(State *s) {
  BeginDrawing();
  switch (s->current_scene) {
  case SCENE_MAIN_MENU:
    sparky_client_renderer_draw_main_menu();
    break;
  case SCENE_GAMEPLAY:
    sparky_client_renderer_draw_gameplay_world(s);
    sparky_client_renderer_draw_gameplay_hud();
    break;
  default:
    assert(0 && "sparky_client_renderer_draw :: Unreachable");
    break;
  }
  EndDrawing();
}
