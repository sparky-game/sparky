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

static const char * const sk_text_help_msg = "Usage: %s [OPTION]\n"
  "GNU Sparky --- A 5v5 character-based libre tactical shooter\n\n"
  "If no option is provided, the client will start in offline mode.\n\n"
  "Options:\n"
  "  -g, --gui \t start the graphical launcher\n"
  "  -i, --ip <IP> \t start the client and connect to the server at <IP>\n"
  "  -s, --server \t\t start the server\n"
  "  -h, --help \t\t display this help and exit\n"
  "  -v, --version \t output version information and exit\n\n"
  "Report bugs to: <https://github.com/iWas-Coder/sparky/issues>\n"
  "GNU Sparky home page: <https://github.com/iWas-Coder/sparky>\n"
  "General help using GNU software: <https://www.gnu.org/gethelp/>\n";

static const char * const sk_text_version_msg = "GNU Sparky %s\n"
  "Copyright (C) 2024 Wasym A. Alonso\n"
  "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl-3.0>.\n"
  "This is free software: you are free to change and redistribute it.\n"
  "There is NO WARRANTY, to the extent permitted by law.\n\n"
  "Written by Wasym A. Alonso.\n";

static const char * const sk_text_unrecog_opt_msg = "%s: unrecognized option\n"
  "Try '%s --help' for more information.\n";
