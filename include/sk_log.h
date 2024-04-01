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
#define SK_LOG_DEBUG(...) TraceLog(LOG_DEBUG, __VA_ARGS__)
#define SK_LOG_INFO(...)  TraceLog(LOG_INFO, __VA_ARGS__)
#define SK_LOG_WARN(...)  TraceLog(LOG_WARNING, __VA_ARGS__)
#define SK_LOG_ERROR(...) TraceLog(LOG_ERROR, __VA_ARGS__)
