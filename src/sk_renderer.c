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

void sk_renderer_create(sk_config *config) {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
  SetConfigFlags(FLAG_WINDOW_MOUSE_PASSTHROUGH);
  InitWindow(config->video.win_width,
             config->video.win_height,
             SK_CLIENT_NAME);
  assert(IsWindowReady());
  InitAudioDevice();
  assert(IsAudioDeviceReady());
  SetTargetFPS(config->video.fps_limit);
}

void sk_renderer_destroy(void) {
  CloseAudioDevice();
  CloseWindow();
}

void sk_renderer_update(sk_state *s) {
  s->curr_scene.update(s);
}

void sk_renderer_draw(sk_state *s) {
  BeginDrawing();
  s->curr_scene.draw(s);
  EndDrawing();
}
