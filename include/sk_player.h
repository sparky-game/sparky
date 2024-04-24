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

#include <raylib.h>
#include <sk_config.h>
#include <sk_weapon.h>

typedef enum {
  SK_PLAYER_KIND_AGENT69
} sk_player_kind;

typedef struct sk_player {
  sk_uuid id;
  i8 lobby_id;
  i8 lobby_slot_idx;
  sk_player_kind kind;
  Camera3D camera;
  Model model;
  sk_weapon weapon;
  f32 v_y;
  u8 hp;
} sk_player;

static const char * const sk_player_kinds[] = {
  [SK_PLAYER_KIND_AGENT69] = "agent69"
};

sk_player sk_player_create(i8 lobby_id, i8 lobby_slot_idx, sk_player_kind kind, sk_config *config);

void sk_player_destroy(sk_player *p);

void sk_player_load(sk_player *p, sk_weapon_kind initial_weapon_kind);

void sk_player_jump(sk_player *p, sk_config *config);

f32 sk_player_peek(sk_player *p, sk_config *config);

void sk_player_move(sk_player *p, sk_config *config, f32 roll);

void sk_player_draw(sk_player *p);
