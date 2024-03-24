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

static void __draw_main_menu(void) {
  ClearBackground(BLACK);
  const char *subtitle = "Press <ENTER> to start";
  u8 subtitle_size = 30;
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

static inline void __draw_player(State *s) {
  DrawModel(s->player.model,
            (Vector3) {
              s->player.camera.position.x - 4,
              s->player.camera.position.y - SPARKY_CLIENT_PLAYER_HEIGHT,
              s->player.camera.position.z
            },
            1,
            WHITE);
}

static inline void __draw_weapon(State *s) {
  DrawModelEx(s->player.weapon.model,
              (Vector3) {
                s->player.camera.position.x + 1,
                s->player.camera.position.y - 1,
                s->player.camera.position.z - 3
              },
              (Vector3) { 1, 0, 0 },
              275,
              (Vector3) { 0.5f, 0.5f, 0.5f },
              WHITE);
}

static inline void __draw_floor(void) {
  DrawPlane((Vector3) { 0, 0, 0 }, (Vector2) { 32, 32 }, DARKGRAY);
}

static inline void __draw_walls(void) {
  DrawCube((Vector3) { -16, 2.5f, 0 }, 1, 5, 32, MAROON);
  DrawCube((Vector3) { 16, 2.5f, 0 }, 1, 5, 32, LIME);
  DrawCube((Vector3) { 0, 2.5f, 16 }, 32, 5, 1, GOLD);
}

static void __draw_gameplay_world(State *s) {
  ClearBackground(SKYBLUE);
  BeginMode3D(s->player.camera);
  __draw_player(s);
  __draw_weapon(s);
  __draw_floor();
  __draw_walls();
  EndMode3D();
}

static inline void __draw_fps(void) {
  DrawFPS(10, 10);
}

static inline void __draw_frametime(void) {
  char dt[10];
  snprintf(dt, sizeof(dt), "%.4f ms", GetFrameTime() * 1000);
  DrawText(dt, 10, 33, 20, LIME);
}

static inline void __draw_crosshair(void) {
  DrawCircle(GetScreenWidth() / 2,
             GetScreenHeight() / 2,
             SPARKY_CONFIG_CLIENT_CROSSHAIR_RADIUS,
             BLACK);
  DrawCircle(GetScreenWidth() / 2,
             GetScreenHeight() / 2,
             SPARKY_CONFIG_CLIENT_CROSSHAIR_RADIUS - 0.9f,
             WHITE);
}

static void __draw_gameplay_hud(void) {
  __draw_fps();
  __draw_frametime();
  __draw_crosshair();
}

void sparky_client_renderer_draw(State *s) {
  BeginDrawing();
  switch (s->current_scene) {
  case SCENE_MAIN_MENU:
    __draw_main_menu();
    break;
  case SCENE_GAMEPLAY:
    __draw_gameplay_world(s);
    __draw_gameplay_hud();
    break;
  default:
    assert(0 && "Unreachable");
  }
  EndDrawing();
}
