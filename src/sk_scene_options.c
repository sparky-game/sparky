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


#include <sk_scene_options.h>
#include <sk_scene_main_menu.h>

void sk_scene_options_update(sk_state *s) {
  if (IsMusicStreamPlaying(s->menu_music)) UpdateMusicStream(s->menu_music);
  if (IsKeyPressed(KEY_ESCAPE)) {
    s->curr_scene.kind = SK_SCENE_KIND_MAIN_MENU;
    s->curr_scene.update = sk_scene_main_menu_update;
    s->curr_scene.draw = sk_scene_main_menu_draw;
    SetExitKey(KEY_THREE);
  }
}

void sk_scene_options_draw(sk_state *s) {
  ClearBackground(BLACK);
#ifndef NDEBUG
  DrawText("[DEBUG MODE]", GetScreenWidth() - 155, 10, 20, YELLOW);
#endif
  if (!s->is_online) DrawText("OFFLINE MODE", 10, 10, 20, YELLOW);
}
