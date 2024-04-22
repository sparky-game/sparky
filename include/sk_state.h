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

#include <sk_map.h>
#include <sk_scene.h>
#include <sk_lobby.h>
#include <sk_config.h>

#define SK_STATE_MAX_LOBBIES 256

typedef struct {
  u8 lobbies_count;
  sk_lobby lobbies[SK_STATE_MAX_LOBBIES];
} sk_state_global;

typedef struct sk_state {
  u8 is_online;
  sk_config config;
  Image win_icon;
  sk_scene curr_scene;
  Music menu_music;
  union {
    sk_lobby lobby;
    struct {
      sk_map map;
      sk_player player;
    };
  };
} sk_state;

sk_state_global sk_state_global_create(void);

void sk_state_global_assign_lobby(sk_state_global *sg, i8 *lobby_id, i8 *lobby_slot_idx);

sk_state sk_state_create_offline(void);

void sk_state_destroy_offline(sk_state *s);

sk_state sk_state_create_online(u8 lobby_id);
