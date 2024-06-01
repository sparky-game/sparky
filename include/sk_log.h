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

#include <raylib.h>

#define SK_LOG_ENABLE_DEBUG_LEVEL SetTraceLogLevel(LOG_DEBUG)

#define SK_LOG_COLOR_RESET   "\033[0m"
#define SK_LOG_COLOR_RED     "\033[1;31m"
#define SK_LOG_COLOR_YELLOW  "\033[1;33m"
#define SK_LOG_COLOR_MAGENTA "\033[1;35m"
#define SK_LOG_COLOR_CYAN    "\033[1;36m"

#define SK_LOG_DEBUG(msg, ...) TraceLog(LOG_DEBUG, SK_LOG_COLOR_CYAN msg SK_LOG_COLOR_RESET, ##__VA_ARGS__)
#define SK_LOG_INFO(msg, ...)  TraceLog(LOG_INFO, SK_LOG_COLOR_MAGENTA msg SK_LOG_COLOR_RESET, ##__VA_ARGS__)
#define SK_LOG_WARN(msg, ...)  TraceLog(LOG_WARNING, SK_LOG_COLOR_YELLOW msg SK_LOG_COLOR_RESET, ##__VA_ARGS__)
#define SK_LOG_ERROR(msg, ...) TraceLog(LOG_ERROR, SK_LOG_COLOR_RED msg SK_LOG_COLOR_RESET, ##__VA_ARGS__)
