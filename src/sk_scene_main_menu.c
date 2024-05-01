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


#include <string.h>
#include <sk_scene_options.h>
#include <sk_scene_loading.h>
#include <sk_scene_main_menu.h>

#define MAIN_MENU_TITLE        "SPARKY"
#define MAIN_MENU_TITLE_SIZE   80
#define MAIN_MENU_START        "Press <1> to start"
#define MAIN_MENU_START_SIZE   30
#define MAIN_MENU_OPTIONS      "Press <2> for options"
#define MAIN_MENU_OPTIONS_SIZE 30
#define MAIN_MENU_EXIT         "Press <3> to exit"
#define MAIN_MENU_EXIT_SIZE    30

void sk_scene_main_menu_update(sk_state *s) {
  if (IsMusicStreamPlaying(s->menu_music)) UpdateMusicStream(s->menu_music);
  if (IsKeyPressed(KEY_ONE)) {
    s->curr_scene.kind = SK_SCENE_KIND_LOADING;
    s->curr_scene.update = sk_scene_loading_update;
    s->curr_scene.draw = sk_scene_loading_draw;
    SetExitKey(KEY_NULL);
  }
  if (IsKeyPressed(KEY_TWO)) {
    s->curr_scene.kind = SK_SCENE_KIND_OPTIONS;
    s->curr_scene.update = sk_scene_options_update;
    s->curr_scene.draw = sk_scene_options_draw;
    SetExitKey(KEY_NULL);
  }
}

void sk_scene_main_menu_draw(sk_state *s) {
  ClearBackground(BLACK);
#ifndef NDEBUG
  DrawText("[DEBUG MODE]", GetScreenWidth() - 155, 10, 20, YELLOW);
#endif
  if (!s->is_online) DrawText("OFFLINE MODE", 10, 10, 20, YELLOW);
  DrawText("v" sk_xstr(SK_VERSION), 10, GetScreenHeight() - 25, 20, RAYWHITE);
  DrawText(MAIN_MENU_TITLE,
           (GetScreenWidth() - MeasureText(MAIN_MENU_TITLE, MAIN_MENU_TITLE_SIZE)) / 2,
           (GetScreenHeight() - MeasureText(MAIN_MENU_TITLE, MAIN_MENU_TITLE_SIZE)) / 2,
           MAIN_MENU_TITLE_SIZE,
           RAYWHITE);
  DrawText(MAIN_MENU_START,
           (GetScreenWidth() - MeasureText(MAIN_MENU_START, MAIN_MENU_START_SIZE)) / 2,
           ((GetScreenHeight() - MeasureText(MAIN_MENU_START, MAIN_MENU_START_SIZE)) / 2) + 115,
           MAIN_MENU_START_SIZE,
           RAYWHITE);
  DrawText(MAIN_MENU_OPTIONS,
           (GetScreenWidth() - MeasureText(MAIN_MENU_OPTIONS, MAIN_MENU_OPTIONS_SIZE)) / 2,
           ((GetScreenHeight() - MeasureText(MAIN_MENU_OPTIONS, MAIN_MENU_OPTIONS_SIZE)) / 2) + 200,
           MAIN_MENU_OPTIONS_SIZE,
           RAYWHITE);
  DrawText(MAIN_MENU_EXIT,
           (GetScreenWidth() - MeasureText(MAIN_MENU_EXIT, MAIN_MENU_EXIT_SIZE)) / 2,
           ((GetScreenHeight() - MeasureText(MAIN_MENU_EXIT, MAIN_MENU_EXIT_SIZE)) / 2) + 225,
           MAIN_MENU_EXIT_SIZE,
           RAYWHITE);
  if (s->config.err_title            &&
      s->config.err_body             &&
      strcmp(s->config.err_body, "") &&
      strcmp(s->config.err_title, "")) {
    DrawText(s->config.err_title, GetScreenWidth() - 500, GetScreenHeight() - 200, 20, RED);
    DrawText(s->config.err_body, GetScreenWidth() - 650, GetScreenHeight() - 150, 18, RED);
  }
}
