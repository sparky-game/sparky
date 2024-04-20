--
-- GNU Sparky --- A 5v5 character-based libre tactical shooter
-- Copyright (C) 2024 Wasym A. Alonso
--
-- This file is part of Sparky.
--
-- Sparky is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- Sparky is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with Sparky.  If not, see <http://www.gnu.org/licenses/>.
--


local MOUSE_BUTTON_LEFT = 0
local KEY_SPACE         = 32
local KEY_A             = 65
local KEY_D             = 68
local KEY_E             = 69
local KEY_Q             = 81
local KEY_R             = 82
local KEY_S             = 83
local KEY_W             = 87

Crosshair = {
  radius = 2.5
}

Video = {
  win_width = 1280,
  win_height = 720,
  fps_limit = 144
}

General = {
  fov = 60,
  mouse_sensitivity = 0.05
}

Controls = {
  move_forward = KEY_W,
  move_backwards = KEY_S,
  move_left = KEY_A,
  move_right = KEY_D,
  peek_left = KEY_Q,
  peek_right = KEY_E,
  jump = KEY_SPACE,
  shoot = MOUSE_BUTTON_LEFT,
  reload = KEY_R
}
