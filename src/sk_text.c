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
#include <sk_text.h>

u8 sk_text_help(char *prog_name) {
  printf(sk_text_help_msg, prog_name);
  return 0;
}

u8 sk_text_version(void) {
  printf(sk_text_version_msg, sk_xstr(SK_VERSION));
  return 0;
}

u8 sk_text_unrecog_opt(char *prog_name) {
  fprintf(stderr, sk_text_unrecog_opt_msg, prog_name, prog_name);
  return 1;
}
