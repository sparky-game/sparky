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


#include <string.h>
#include <raylib.h>
#include <sk_client.h>

int main(int argc, char **argv) {
  if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
    TraceLog(LOG_INFO, "usage: %s [--server]", argv[0]);
    return 0;
  }
  if (argc == 2 && !strcmp(argv[1], "--server")) {
    TraceLog(LOG_WARNING, "Server not implemented yet. Exiting...");
    return 0;
  }
  if (argc == 1) return sk_client_run();

  TraceLog(LOG_ERROR, "usage: %s [--server]", argv[0]);
  return 1;
}
