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

#include <sk_player.h>
#include <sk_defines.h>

#define SK_LOBBY_MAX_PLAYERS 10

typedef struct {
  u8 id;
  u8 players_count;
  sk_player players[SK_LOBBY_MAX_PLAYERS];
} sk_lobby;

sk_lobby sk_lobby_create(u8 id);

void sk_lobby_destroy(sk_lobby *l);

u8 sk_lobby_add(sk_lobby *l, sk_player p);

u8 sk_lobby_kick(sk_lobby *l, i8 p_idx);
