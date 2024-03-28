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

#define SK_SERVER_NAME      "sparky-server"
#define SK_SERVER_PORT      27015
#define SK_SERVER_TICK_RATE 128

#define NBN_LogTrace(...)   TraceLog(LOG_TRACE, __VA_ARGS__)
#define NBN_LogDebug(...)   TraceLog(LOG_DEBUG, __VA_ARGS__)
#define NBN_LogInfo(...)    TraceLog(LOG_INFO, __VA_ARGS__)
#define NBN_LogWarning(...) TraceLog(LOG_WARNING, __VA_ARGS__)
#define NBN_LogError(...)   TraceLog(LOG_ERROR, __VA_ARGS__)

u8 sk_server_run(void);
