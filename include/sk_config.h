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

#include <sk_defines.h>

typedef struct {
  f32 radius;
} sk_config_crosshair;

typedef struct {
  u16 win_width;
  u16 win_height;
  u16 fps_limit;
} sk_config_video;

typedef struct {
  u8 fov;
  f32 mouse_sensitivity;
} sk_config_general;

typedef struct {
  u16 move_forward;
  u16 move_backwards;
  u16 move_left;
  u16 move_right;
  u16 peek_left;
  u16 peek_right;
  u16 jump;
  u16 shoot;
  u16 reload;
} sk_config_controls;

typedef struct {
  sk_config_crosshair crosshair;
  sk_config_video video;
  sk_config_general general;
  sk_config_controls controls;
  const char *err_title;
  const char *err_body;
} sk_config;

sk_config sk_config_create(void);

void sk_config_destroy(sk_config *c);

void sk_config_load(const char *filepath, sk_config *c);

void sk_config_write(const char *filepath, sk_config *c);
