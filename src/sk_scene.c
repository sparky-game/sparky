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


#include <assert.h>
#include <sk_scene.h>
#include <sk_scene_intro.h>
#include <sk_scene_options.h>
#include <sk_scene_gameplay.h>
#include <sk_scene_main_menu.h>

sk_scene sk_scene_create(sk_scene_kind kind) {
  sk_scene s = {
    .kind = kind
  };
  switch (kind) {
  case SK_SCENE_KIND_INTRO:
    s.update = sk_scene_intro_update;
    s.draw = sk_scene_intro_draw;
    break;
  case SK_SCENE_KIND_MAIN_MENU:
    s.update = sk_scene_main_menu_update;
    s.draw = sk_scene_main_menu_draw;
    break;
  case SK_SCENE_KIND_OPTIONS:
    s.update = sk_scene_options_update;
    s.draw = sk_scene_options_draw;
    break;
  case SK_SCENE_KIND_GAMEPLAY:
    s.update = sk_scene_gameplay_update;
    s.draw = sk_scene_gameplay_draw;
    break;
  default:
    assert(0 && "Unreachable");
  }
  return s;
}
