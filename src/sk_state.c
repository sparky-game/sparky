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
#include <sk_log.h>
#include <sk_state.h>
#include <sk_image.h>
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
  sk_state s = { .is_online = 0 };
  s.config = sk_config_create();
  sk_config_load("config.lua", &s.config);
  sk_renderer_create(&s.config);
#ifdef NDEBUG
  s.ap = (sk_assetpack) {0};
  if (!sk_assetpack_open(&s.ap)) SK_LOG_ERROR("sk_state_create_offline :: unable to load SKAP file (`assets.skap`)");
  sk_image_init(&s.ap);
#endif
  s.win_icon = sk_image_load("assets/icon.png");
  s.loading_controls = sk_image_gpu_load("assets/images/loading-controls.png");
  s.curr_scene = sk_scene_create(SK_SCENE_KIND_INTRO);
  s.menu_music = LoadMusicStream(TextFormat(MUSIC_PATH_PLACEHOLDER, "menu"));
  s.map = sk_map_create(SK_MAP_TRAINING);
  s.player = sk_player_create(0, 0, SK_PLAYER_KIND_AGENT69, &s.config);
  s.shots_rb = sk_rngbuf_create(2 << 14, sizeof(sk_shot), 1);
  assert(IsImageReady(s.win_icon));
  SetWindowIcon(s.win_icon);
  assert(IsTextureReady(s.loading_controls));
  GenTextureMipmaps(&s.loading_controls);
  return s;
}

void sk_state_destroy_offline(sk_state *s) {
  sk_rngbuf_destroy(&s->shots_rb);
  sk_player_destroy(&s->player);
  sk_map_destroy(&s->map);
  UnloadTexture(s->loading_controls);
  UnloadMusicStream(s->menu_music);
  UnloadImage(s->win_icon);
#ifdef NDEBUG
  sk_assetpack_close(&s->ap);
#endif
  sk_renderer_destroy();
  sk_config_destroy(&s->config);
  *s = (sk_state) {0};
  s = 0;
}

sk_state sk_state_create_online(u8 lobby_id) {
  return (sk_state) {
    .is_online = 1,
    .config = sk_config_create(),
    .curr_scene = sk_scene_create(SK_SCENE_KIND_INTRO),
    .menu_music = LoadMusicStream(TextFormat(MUSIC_PATH_PLACEHOLDER, "menu")),
    .lobby = sk_lobby_create(lobby_id)
  };
}
