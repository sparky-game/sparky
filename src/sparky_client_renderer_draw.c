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
#include <sparky_defines.h>
#include <sparky_client_renderer.h>

static void draw_main_menu(void) {
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

static void draw_gameplay_world(State *s) {
  ClearBackground(SKYBLUE);
  BeginMode3D(s->player.camera);
  DrawModel(s->player.model,
            Vector3Subtract(s->player.camera.position,
                            (Vector3) { 0, SPARKY_CLIENT_PLAYER_HEIGHT, 0 }),
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

static void draw_gameplay_hud(void) {
  DrawFPS(10, 10);
  char dt[10];
  snprintf(dt, sizeof(dt), "%.4f ms", GetFrameTime() * 1000);
  DrawText(dt, 10, 33, 20, LIME);
}

void sparky_client_renderer_draw(State *s) {
  BeginDrawing();
  switch (s->current_scene) {
  case SCENE_MAIN_MENU:
    draw_main_menu();
    break;
  case SCENE_GAMEPLAY:
    draw_gameplay_world(s);
    draw_gameplay_hud();
    break;
  default:
    assert(0 && "sparky_client_renderer_draw :: Unreachable");
  }
  EndDrawing();
}
