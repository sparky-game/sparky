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

void sparky_client_renderer_open_window(void) {
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
  float look_sens = 0.05f;
  float walk_sens = 0.1f;
  UpdateCameraPro(&s->player.camera,
                  (Vector3) {
                    IsKeyDown(KEY_W) * walk_sens - IsKeyDown(KEY_S) * walk_sens,
                    IsKeyDown(KEY_D) * walk_sens - IsKeyDown(KEY_A) * walk_sens,
                    0.0f
                  },
                  (Vector3) {
                    dm.x * look_sens,
                    dm.y * look_sens,
                    0.0f
                  },
                  0.0f);
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
  const char *title = "SPARKY";
  int title_size = 80;
  const char *subtitle = "Press <ENTER> to start";
  int subtitle_size = 30;
  DrawText(title,
           (GetScreenWidth() - MeasureText(title, title_size)) / 2,
           (GetScreenHeight() - MeasureText(title, title_size)) / 2,
           title_size,
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
            (Vector3) { 0.0f, 0.0f, 0.0f },
            1.0f, PURPLE);
  DrawPlane((Vector3) { 0.0f, 0.0f, 0.0f },
            (Vector2) { 32.0f, 32.0f },
            DARKGRAY);
  DrawCube((Vector3) { -16.0f, 2.5f, 0.0f },
           1.0f, 5.0f, 32.0f, RED);
  DrawCube((Vector3) { 16.0f, 2.5f, 0.0f },
           1.0f, 5.0f, 32.0f, LIME);
  DrawCube((Vector3) { 0.0f, 2.5f, 16.0f },
           32.0f, 5.0f, 1.0f, GOLD);
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
