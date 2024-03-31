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
#include <sk_config.h>
#include <sk_client.h>
#include <sk_server.h>
#include <sk_defines.h>
#include <sk_renderer.h>

static void __draw_main_menu(void) {
  ClearBackground(BLACK);
  const char * const subtitle = "Press <ENTER> to start";
  u8 subtitle_size = 30;
  DrawText(SK_CLIENT_MAIN_MENU_TITLE,
           (GetScreenWidth() - MeasureText(SK_CLIENT_MAIN_MENU_TITLE,
                                           SK_CLIENT_MAIN_MENU_TITLE_SIZE)) / 2,
           (GetScreenHeight() - MeasureText(SK_CLIENT_MAIN_MENU_TITLE,
                                            SK_CLIENT_MAIN_MENU_TITLE_SIZE)) / 2,
           SK_CLIENT_MAIN_MENU_TITLE_SIZE,
           RAYWHITE);
  DrawText(subtitle,
           (GetScreenWidth() - MeasureText(subtitle, subtitle_size)) / 2,
           ((GetScreenHeight() - MeasureText(subtitle, subtitle_size)) / 2) + 115,
           subtitle_size,
           RAYWHITE);
  DrawText("v" sk_xstr(SK_VERSION),
           10,
           GetScreenHeight() - 25,
           20,
           RAYWHITE);
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
  sk_player_draw(&s->player);
  sk_weapon_draw(&s->player.weapon, (Vector3) {
      s->player.camera.position.x + 1,
      s->player.camera.position.y - 1,
      s->player.camera.position.z - 3
    });
  __draw_floor();
  __draw_walls();
  EndMode3D();
}

static inline void __draw_fps(void) {
  DrawFPS(10, 10);
}

static inline void __draw_frametime(void) {
  DrawText(TextFormat("%.4f ms", GetFrameTime() * 1000), 10, 33, 20, LIME);
}

static inline void __draw_ping(void) {
  DrawText(TextFormat("N/A ms"), 10, 50, 20, LIME);
}

static inline void __draw_bandwidth(void) {
  DrawText(TextFormat("(d) N/A bps | (u) N/A bps"), 10, 70, 20, LIME);
}

static inline void __draw_crosshair(void) {
  DrawCircle(GetScreenWidth() / 2,
             GetScreenHeight() / 2,
             SK_CONFIG_CLIENT_CROSSHAIR_RADIUS,
             BLACK);
  DrawCircle(GetScreenWidth() / 2,
             GetScreenHeight() / 2,
             SK_CONFIG_CLIENT_CROSSHAIR_RADIUS - 0.9f,
             WHITE);
}

static void __draw_gameplay_hud(State *s) {
  __draw_fps();
  __draw_frametime();
  if (s->is_online) {
    __draw_ping();
    __draw_bandwidth();
  }
  __draw_crosshair();
}

void sk_renderer_draw(State *s) {
  BeginDrawing();
  switch (s->current_scene) {
  case SCENE_MAIN_MENU:
    __draw_main_menu();
    break;
  case SCENE_GAMEPLAY:
    __draw_gameplay_world(s);
    __draw_gameplay_hud(s);
    break;
  default:
    assert(0 && "Unreachable");
  }
  EndDrawing();
}
