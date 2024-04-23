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


#include <lua.h>
#include <raylib.h>
#include <lualib.h>
#include <sk_log.h>
#include <lauxlib.h>
#include <sk_config.h>

sk_config sk_config_create(void) {
  return (sk_config) {
    .crosshair = (sk_config_crosshair) {
      .radius = 2.5f
    },
    .video = (sk_config_video) {
      .win_width = 1280,
      .win_height = 720,
      .fps_limit = 144
    },
    .general = (sk_config_general) {
      .fov = 60,
      .mouse_sensitivity = 0.05f
    },
    .controls = (sk_config_controls) {
      .move_forward = KEY_W,
      .move_backwards = KEY_S,
      .move_left = KEY_A,
      .move_right = KEY_D,
      .peek_left = KEY_Q,
      .peek_right = KEY_E,
      .jump = KEY_SPACE
    }
  };
}

void sk_config_destroy(sk_config *c) {
  *c = (sk_config) {0};
  c = 0;
}

void sk_config_load(const char *filepath, sk_config *c) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  if (luaL_loadfile(L, filepath) || lua_pcall(L, 0, 0, 0)) {
    c->err_title = TextFormat("Unable to load config file (%s)", filepath);
    c->err_body = TextFormat("%s", lua_tostring(L, -1));
    SK_LOG_ERROR("%s :: %s", c->err_title, c->err_body);
    lua_close(L);
    return;
  }
  lua_getglobal(L, "Crosshair");
  lua_getfield(L, -1, "radius");
  if ((f32) lua_tonumber(L, -1) > 0) c->crosshair.radius = (f32) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `Crosshair.radius` needs to be > 0. Using default instead");
  lua_pop(L, 1);
  lua_pop(L, 1);
  lua_getglobal(L, "Video");
  lua_getfield(L, -1, "win_width");
  if ((i16) lua_tonumber(L, -1) > 0) c->video.win_width = (u16) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `Video.win_width` needs to be > 0. Using default instead");
  lua_pop(L, 1);
  lua_getfield(L, -1, "win_height");
  if ((i16) lua_tonumber(L, -1) > 0) c->video.win_height = (u16) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `Video.win_height` needs to be > 0. Using default instead");
  lua_pop(L, 1);
  lua_getfield(L, -1, "fps_limit");
  if ((i16) lua_tonumber(L, -1) > 0) c->video.fps_limit = (u16) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `Video.fps_limit` needs to be > 0. Using default instead");
  lua_pop(L, 1);
  lua_pop(L, 1);
  lua_getglobal(L, "General");
  lua_getfield(L, -1, "fov");
  if ((i8) lua_tonumber(L, -1) > 0) c->general.fov = (u8) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `General.fov` needs to be > 0. Using default instead");
  lua_pop(L, 1);
  lua_getfield(L, -1, "mouse_sensitivity");
  if ((f32) lua_tonumber(L, -1) > 0) c->general.mouse_sensitivity = (f32) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `General.mouse_sensitivity` needs to be > 0. Using default instead");
  lua_pop(L, 1);
  lua_pop(L, 1);
  lua_getglobal(L, "Controls");
  lua_getfield(L, -1, "move_forward");
  if ((i16) lua_tonumber(L, -1) > 0) c->controls.move_forward = (u16) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `Controls.move_forward` needs to be > 0. Using default instead");
  lua_pop(L, 1);
  lua_getfield(L, -1, "move_backwards");
  if ((i16) lua_tonumber(L, -1) > 0) c->controls.move_backwards = (u16) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `Controls.move_backwards` needs to be > 0. Using default instead");
  lua_pop(L, 1);
  lua_getfield(L, -1, "move_left");
  if ((i16) lua_tonumber(L, -1) > 0) c->controls.move_left = (u16) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `Controls.move_left` needs to be > 0. Using default instead");
  lua_pop(L, 1);
  lua_getfield(L, -1, "move_right");
  if ((i16) lua_tonumber(L, -1) > 0) c->controls.move_right = (u16) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `Controls.move_right` needs to be > 0. Using default instead");
  lua_pop(L, 1);
  lua_getfield(L, -1, "peek_left");
  if ((i16) lua_tonumber(L, -1) > 0) c->controls.peek_left = (u16) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `Controls.peek_left` needs to be > 0. Using default instead");
  lua_pop(L, 1);
  lua_getfield(L, -1, "peek_right");
  if ((i16) lua_tonumber(L, -1) > 0) c->controls.peek_right = (u16) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `Controls.peek_right` needs to be > 0. Using default instead");
  lua_pop(L, 1);
  lua_getfield(L, -1, "jump");
  if ((i16) lua_tonumber(L, -1) > 0) c->controls.jump = (u16) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `Controls.jump` needs to be > 0. Using default instead");
  lua_pop(L, 1);
  lua_getfield(L, -1, "shoot");
  if ((i16) lua_tonumber(L, -1) >= 0) c->controls.shoot = (u16) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `Controls.jump` needs to be >= 0. Using default instead");
  lua_pop(L, 1);
  lua_getfield(L, -1, "reload");
  if ((i16) lua_tonumber(L, -1) > 0) c->controls.reload = (u16) lua_tonumber(L, -1);
  else SK_LOG_WARN("sk_config_load :: `Controls.reload` needs to be > 0. Using default instead");
  lua_pop(L, 1);
  lua_pop(L, 1);
  lua_close(L);
}

void sk_config_write(const char *filepath, sk_config *c) {
  (void) filepath;
  (void) c;
}
