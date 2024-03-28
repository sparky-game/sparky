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


#include <sk_config.h>
#include <sk_client.h>
#include <sk_renderer.h>
#include <sk_gametypes.h>

static State state = {0};

static u8 destroy(void) {
  sk_player_destroy(&state.player);
  CloseAudioDevice();
  CloseWindow();
  state = (State) {0};
  TraceLog(LOG_INFO, "%s closed successfully", SK_CLIENT_NAME);
  return 0;
}

u8 sk_client_run(const char *ip) {
  TraceLog(LOG_INFO, "Initializing %s", SK_CLIENT_NAME);
  if (!ip) TraceLog(LOG_WARNING, "Running in offline mode");
  else TraceLog(LOG_INFO, "Connected to server @ %s", ip);

  if (!ChangeDirectory(GetApplicationDirectory())) {
    TraceLog(LOG_WARNING, "Could not change CWD to the game's root directory");
  }
  sk_renderer_init();
  state.current_scene = SCENE_MAIN_MENU;
  sk_player_create(&state, SK_PLAYER_KIND_JETT);

  sk_renderer_loop {
    sk_renderer_update(&state);
    sk_renderer_draw(&state);
  }
  return destroy();
}
