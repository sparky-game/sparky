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


#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <skap_file.h>
#include <skap_defines.h>

FILE *skap_file_create(void) {
  if (!access(SKAP_FILENAME, F_OK)) {
    printf("  RENAME  " SKAP_FILENAME " -> " SKAP_FILENAME ".old\n");
    if (rename(SKAP_FILENAME, SKAP_FILENAME ".old") == -1) {
      fprintf(stderr, "ERROR: rename(2) unable to rename the file (%s)\n", strerror(errno));
      return 0;
    }
  }
  else printf("  TOUCH   " SKAP_FILENAME "\n");
  return fopen(SKAP_FILENAME, "ab");
}

void skap_file_destroy(FILE *fd) {
  if (!fd) {
    printf("WARNING: skap_file_destroy :: `fd` is not a valid pointer, skipping destruction\n");
    return;
  }
  fclose(fd);
}
