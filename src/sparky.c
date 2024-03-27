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
#include <raylib.h>
#include <sk_client.h>
#include <sk_server.h>

#define xstr(s) str(s)
#define str(s) #s

static const char *help_msg = "Usage: %s [OPTION]\n"
  "GNU Sparky --- A 5v5 character-based libre tactical shooter\n\n"
  "If no option is provided, the client will start in offline mode.\n\n"
  "Options:\n"
  "  -i, --ip <IP> \t start the client and connect to the server at <IP>\n"
  "  -s, --server \t\t start the server\n"
  "  -h, --help \t\t display this help and exit\n"
  "  -v, --version \t output version information and exit\n\n"
  "Report bugs to: <https://github.com/iWas-Coder/sparky/issues>\n"
  "GNU Sparky home page: <https://github.com/iWas-Coder/sparky>\n"
  "General help using GNU software: <https://www.gnu.org/gethelp/>\n";
static const char *version_msg = "GNU Sparky %s\n"
  "Copyright (C) 2024 Wasym A. Alonso\n"
  "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl-3.0>.\n"
  "This is free software: you are free to change and redistribute it.\n"
  "There is NO WARRANTY, to the extent permitted by law.\n\n"
  "Written by Wasym A. Alonso.\n";
static const char *unrecog_opt_msg = "%s: unrecognized option\n"
  "Try '%s --help' for more information.\n";

int main(int argc, char **argv) {
#ifndef NDEBUG
#define NBN_DEBUG
  SetTraceLogLevel(LOG_DEBUG);
  TraceLog(LOG_WARNING, "Running in debug mode");
#endif

  if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
    printf(help_msg, argv[0]);
    return 0;
  }
  if (argc == 2 && (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version"))) {
    printf(version_msg, xstr(SK_VERSION));
    return 0;
  }
  if (argc == 2 && (!strcmp(argv[1], "-s") || !strcmp(argv[1], "--server"))) return sk_server_run();
  if (argc == 3 && (!strcmp(argv[1], "-i") || !strcmp(argv[1], "--ip"))) return sk_client_run(argv[2]);
  if (argc == 1) return sk_client_run(0);

  fprintf(stderr, unrecog_opt_msg, argv[0], argv[0]);
  return 1;
}
