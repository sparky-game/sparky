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
#include <sk_config.h>
#include <sk_client.h>
#include <sk_renderer.h>

void sk_renderer_create(void) {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
  SetConfigFlags(FLAG_WINDOW_MOUSE_PASSTHROUGH);
  InitWindow(SK_CONFIG_CLIENT_WIN_WIDTH,
             SK_CONFIG_CLIENT_WIN_HEIGHT,
             SK_CLIENT_NAME);
  assert(IsWindowReady());
  InitAudioDevice();
  assert(IsAudioDeviceReady());
  SetTargetFPS(SK_CONFIG_CLIENT_FPS);
}

void sk_renderer_destroy(void) {
  CloseAudioDevice();
  CloseWindow();
}

void sk_renderer_update(sk_state *s) {
  switch (s->curr_scene.kind) {
  case SK_SCENE_KIND_INTRO:
    assert(IsMusicReady(s->menu_music));
    if (!IsMusicStreamPlaying(s->menu_music)) {
      SetMusicVolume(s->menu_music, 0.35f);
      PlayMusicStream(s->menu_music);
    }
    else UpdateMusicStream(s->menu_music);
    break;
  case SK_SCENE_KIND_MAIN_MENU:
    if (IsMusicStreamPlaying(s->menu_music)) UpdateMusicStream(s->menu_music);
    if (IsKeyPressed(KEY_ENTER)) {
      s->curr_scene.kind = SK_SCENE_KIND_GAMEPLAY;
      StopMusicStream(s->menu_music);
      sk_player_load(&s->player, SK_WEAPON_KIND_7MM);
      sk_map_load(&s->map);
      DisableCursor();
    }
    break;
  case SK_SCENE_KIND_GAMEPLAY:
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) sk_weapon_shoot(&s->player.weapon);
    if (IsKeyPressed(KEY_R)) sk_weapon_reload(&s->player.weapon);
    sk_player_jump(&s->player);
    sk_player_move(&s->player, sk_player_peek(&s->player));
    break;
  default:
    assert(0 && "Unreachable");
  }
}
