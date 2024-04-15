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
#include <sk_state.h>
#include <sk_renderer.h>

#define MUSIC_PATH_PLACEHOLDER "assets/music/%s.mp3"

sk_state_global sk_state_global_create(void) {
  sk_state_global sg = { .lobbies_count = 0 };
  for (u16 i = 0; i < SK_STATE_MAX_LOBBIES; ++i) {
    sg.lobbies[i] = sk_lobby_create(i);
  }
  return sg;
}

void sk_state_global_assign_lobby(sk_state_global *sg, i8 *lobby_id, i8 *lobby_slot_idx) {
  for (u16 i = 0; i < SK_STATE_MAX_LOBBIES; ++i) {
    if (sg->lobbies[i].players_count == SK_LOBBY_MAX_PLAYERS) continue;
    for (u8 j = 0; j < SK_LOBBY_MAX_PLAYERS; ++j) {
      if (sg->lobbies[i].players[j].lobby_id == -1 &&
          sg->lobbies[i].players[j].lobby_slot_idx == -1) {
        *lobby_id = i;
        *lobby_slot_idx = j;
        SK_LOG_INFO("sk_state_global_assign_lobby :: assigned lobby %i, slot %i",
                    *lobby_id,
                    *lobby_slot_idx);
        return;
      }
    }
  }
  *lobby_id = -1;
  *lobby_slot_idx = -1;
  SK_LOG_WARN("sk_state_global_assign_lobby :: all lobbies are full");
}

sk_state sk_state_create_offline(void) {
  sk_renderer_create();
  return (sk_state) {
    .is_online = 0,
    .curr_scene = (sk_scene) { .kind = SK_SCENE_KIND_INTRO },
    .menu_music = LoadMusicStream(TextFormat(MUSIC_PATH_PLACEHOLDER, "menu")),
    .map = sk_map_create(SK_MAP_CAMPING),
    .player = sk_player_create(0, 0, SK_PLAYER_KIND_AGENT69)
  };
}

void sk_state_destroy_offline(sk_state *s) {
  sk_map_destroy(&s->map);
  sk_player_destroy(&s->player);
  UnloadMusicStream(s->menu_music);
  sk_renderer_destroy();
}

sk_state sk_state_create_online(u8 lobby_id) {
  return (sk_state) {
    .is_online = 1,
    .curr_scene = (sk_scene) { .kind = SK_SCENE_KIND_MAIN_MENU },
    .lobby = sk_lobby_create(lobby_id)
  };
}
