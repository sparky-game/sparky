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

#include <sk_scene.h>
#include <sk_lobby.h>

#define SK_STATE_MAX_LOBBIES 256

typedef struct {
  u8 is_online;
  sk_scene curr_scene;
  union {
    struct {
      u8 lobbies_count;
      sk_lobby lobbies[SK_STATE_MAX_LOBBIES];
    };
    struct {
      sk_player player;
    };
  };
} sk_state;

sk_state sk_state_create(u8 is_online);

void sk_state_destroy(sk_state *s);
