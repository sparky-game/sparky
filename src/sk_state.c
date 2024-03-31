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


#include <sk_state.h>

sk_state sk_state_create(u8 is_online) {
  sk_state s = {
    .is_online = is_online,
    .curr_scene = (sk_scene) { .kind = SK_SCENE_KIND_MAIN_MENU }
  };
  if (is_online) {
    s.lobbies_count = 0;
    for (u16 i = 0; i < SK_STATE_MAX_LOBBIES; ++i) {
      s.lobbies[i] = sk_lobby_create(i);
    }
  }
  else {
    s.player = sk_player_create(SK_PLAYER_KIND_JETT);
  }
  return s;
}

void sk_state_destroy(sk_state *s) {
  (void) s;
}
