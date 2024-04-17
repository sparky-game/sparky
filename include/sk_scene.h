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


#pragma once

typedef struct sk_state sk_state;

typedef enum {
  SK_SCENE_KIND_INTRO,
  SK_SCENE_KIND_MAIN_MENU,
  SK_SCENE_KIND_GAMEPLAY
} sk_scene_kind;

typedef struct {
  sk_scene_kind kind;
  void (*update)(sk_state *s);
  void (*draw)(sk_state *s);
} sk_scene;

sk_scene sk_scene_create(sk_scene_kind kind);
