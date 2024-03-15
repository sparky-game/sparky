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


#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sparky_log.h>

#define LOG_MSG_SIZE_LIMIT 32000

static void strfmt_v(char *dest, const char *fmt, void *va_list) {
  if (!dest) return;
  char buf[LOG_MSG_SIZE_LIMIT];
  int bytes = vsnprintf(buf, LOG_MSG_SIZE_LIMIT, fmt, va_list);
  buf[bytes] = 0;
  memcpy(dest, buf, bytes + 1);
}

void sparky_log(log_level level, const char *msg, ...) {
  const char *level_strs[] = {
    "ERROR",
    "WARN",
    "INFO"
  };
  char out_msg[LOG_MSG_SIZE_LIMIT] = {0};
  __builtin_va_list arg_ptr;
  va_start(arg_ptr, msg);
  strfmt_v(out_msg, msg, arg_ptr);
  va_end(arg_ptr);
  if (level < LOG_LEVEL_WARN) fprintf(stderr, "%s: %s\n", level_strs[level], out_msg);
  else printf("%s: %s\n", level_strs[level], out_msg);
}
