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

#define SK_SERVER_NAME         "sparky-server"
#define SK_SERVER_PORT         27015
#define SK_SERVER_TICK_RATE    128
#define SK_SERVER_MSG_MAX_SIZE 1024
#define SK_SERVER_MSG_HELLO    SK_SERVER_NAME "::hello"
#define SK_SERVER_MSG_HOWDY    SK_SERVER_NAME "::howdy::%hhd/%hhd"

i32 sk_server_socket_create(void);

void sk_server_socket_destroy(i32 sock_fd);

i32 sk_server_socket_bind(i32 sock_fd);

u8 sk_server_run(void);
