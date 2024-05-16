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


#include <sk_log.h>
#include <sk_lobby.h>

sk_lobby sk_lobby_create(u8 id) {
  sk_lobby l = {
    .id = id,
    .players_count = 0
  };
  for (u8 i = 0; i < SK_LOBBY_MAX_PLAYERS; ++i) {
    l.players[i] = (sk_player) {
      .lobby_id = -1,
      .lobby_slot_idx = -1
    };
  }
  return l;
}

void sk_lobby_destroy(sk_lobby *l) {
  *l = (sk_lobby) {0};
  l = 0;
}

u8 sk_lobby_add(sk_lobby *l, sk_player p) {
  if (l->players_count == SK_LOBBY_MAX_PLAYERS) {
    SK_LOG_DEBUG("Lobby %u :: unable to add more players (full)", l->id);
    return false;
  }
  for (u8 i = 0; i < SK_LOBBY_MAX_PLAYERS; ++i) {
    if (l->players[i].lobby_id != -1 &&
        l->players[i].lobby_slot_idx != -1 ) continue;
    p.lobby_id = l->id;
    p.lobby_slot_idx = i;
    l->players[i] = p;
    SK_LOG_INFO("Lobby %u :: added new player to slot %u/%u",
                l->id,
                i + 1,
                SK_LOBBY_MAX_PLAYERS);
  }
  ++l->players_count;
  return true;
}

u8 sk_lobby_kick(sk_lobby *l, i8 p_idx) {
  if (p_idx >= l->players_count          ||
      l->players[p_idx].lobby_id != l->id ||
      l->players[p_idx].lobby_slot_idx != p_idx) {
    SK_LOG_DEBUG("Lobby %u :: unable to kick non-existant player", l->id);
    return false;
  }
  l->players[p_idx].lobby_id = -1;
  l->players[p_idx].lobby_slot_idx = -1;
  l->players[p_idx] = (sk_player) {
    .lobby_id = -1,
    .lobby_slot_idx = -1
  };
  return true;
}
