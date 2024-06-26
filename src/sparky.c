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
#include <sk_log.h>
#include <sk_text.h>
#include <sk_client.h>
#include <sk_server.h>
#include <sk_launcher.h>

int main(int argc, char **argv) {
#ifndef NDEBUG
  SK_LOG_ENABLE_DEBUG_LEVEL;
  SK_LOG_WARN("Running in debug mode");
#endif

  if (argc == 1) return sk_client_run(0);
  if (argc == 2 && (!strcmp(argv[1], "-g") || !strcmp(argv[1], "--gui"))) return sk_launcher_run();
  if (argc == 3 && (!strcmp(argv[1], "-i") || !strcmp(argv[1], "--ip"))) return sk_client_run(argv[2]);
  if (argc == 2 && (!strcmp(argv[1], "-s") || !strcmp(argv[1], "--server"))) return sk_server_run();
  if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) return sk_text_help(argv[0]);
  if (argc == 2 && (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version"))) return sk_text_version();

  return sk_text_unrecog_opt(argv[0]);
}
