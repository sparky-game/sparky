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

typedef enum {
  LOG_LEVEL_ERROR,
  LOG_LEVEL_WARN,
  LOG_LEVEL_INFO
} log_level;

#define SPARKY_LOG_ERROR(msg, ...) sparky_log(LOG_LEVEL_ERROR, msg, ##__VA_ARGS__)
#define SPARKY_LOG_WARN(msg, ...) sparky_log(LOG_LEVEL_WARN, msg, ##__VA_ARGS__)
#define SPARKY_LOG_INFO(msg, ...) sparky_log(LOG_LEVEL_INFO, msg, ##__VA_ARGS__)

void sparky_log(log_level level, const char *msg, ...);
