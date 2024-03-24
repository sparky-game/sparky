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

#include <stdint.h>

#define SPARKY_CLIENT_NAME                         "sparky-client"
#define SPARKY_CLIENT_MAIN_MENU_TITLE              "SPARKY"
#define SPARKY_CLIENT_MAIN_MENU_TITLE_SIZE         80
#define SPARKY_CLIENT_GRAVITY                      19
#define SPARKY_CLIENT_PLAYER_HEIGHT                2
#define SPARKY_CLIENT_PLAYER_JUMP_INIT_VELOCITY    9
#define SPARKY_CLIENT_PLAYER_CAM_WALK_SENSITIVITY  0.1
#define SPARKY_CLIENT_PLAYER_CAM_ROLL_ACCELERATION 1.5

#define SPARKY_SERVER_NAME      "sparky-server"
#define SPARKY_SERVER_PORT      27015
#define SPARKY_SERVER_TICK_RATE 128

typedef uint8_t u8;
