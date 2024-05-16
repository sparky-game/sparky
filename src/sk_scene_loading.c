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


#include <sk_scene_loading.h>
#include <sk_scene_gameplay.h>

#define LOADING_TITLE      "LOADING..."
#define LOADING_TITLE_SIZE 50

static u8 is_loading_drawn_once = 0;

void sk_scene_loading_update(sk_state *s) {
  if (!is_loading_drawn_once) return;
  s->curr_scene.kind = SK_SCENE_KIND_GAMEPLAY;
  s->curr_scene.update = sk_scene_gameplay_update;
  s->curr_scene.draw = sk_scene_gameplay_draw;
  StopMusicStream(s->menu_music);
  sk_player_load(&s->player);
  sk_map_load(&s->map);
  SetExitKey(KEY_ESCAPE);
  DisableCursor();
}

void sk_scene_loading_draw(sk_state *s) {
  ClearBackground(BLACK);
#ifndef NDEBUG
  DrawText("[DEBUG MODE]", GetScreenWidth() - 155, 10, 20, YELLOW);
#endif
  if (!s->is_online) DrawText("OFFLINE MODE", 10, 10, 20, YELLOW);
  DrawText("v" sk_xstr(SK_VERSION), 10, GetScreenHeight() - 25, 20, RAYWHITE);
  DrawText(LOADING_TITLE,
           (GetScreenWidth() - MeasureText(LOADING_TITLE, LOADING_TITLE_SIZE)) / 2,
           50,
           LOADING_TITLE_SIZE,
           RAYWHITE);
  DrawTexture(s->loading_controls, GetScreenWidth() / 2 - s->loading_controls.width / 2, 100, WHITE);
  is_loading_drawn_once = 1;
}
