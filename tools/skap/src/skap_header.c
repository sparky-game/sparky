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


#include <time.h>
#include <stdio.h>
#include <skap_header.h>

static u64 concat_num(u64 x, u64 y) {
  u64 n = 10;
  while (y >= n) n *= 10;
  return n * x + y;
}

static u64 compute_build_ver(void) {
  time_t t = time(0);
  struct tm *t_spec = localtime(&t);
  u64 t_spec_arr[] = {
    t_spec->tm_mon + 1,
    t_spec->tm_mday,
    t_spec->tm_hour,
    t_spec->tm_min
  };
  u64 build_ver = t_spec->tm_year + 1900;
  for (size_t i = 0; i < 4; ++i) {
    if (t_spec_arr[i] < 10) build_ver *= 10;
    build_ver = concat_num(build_ver, t_spec_arr[i]);
  }
  return build_ver;
}

skap_header skap_header_create(usz idx_image_count) {
  return (skap_header) {
    .signature = { 'S', 'K', 'A', 'P' },
    .fmt_ver = 1,
    .build_ver = compute_build_ver(),
    .idx_image_count = idx_image_count
  };
}

u8 skap_header_append(FILE *fd, skap_header *h) {
  if (!fd || !h) {
    fprintf(stderr, "ERROR: skap_header_append :: `fd` and `h` need to be valid pointers\n");
    return 0;
  }
  printf("  WRITE   skap_header >> " SKAP_FILENAME "\n");
  if (fwrite(h, sizeof(skap_header), 1, fd) != 1) {
    fprintf(stderr, "ERROR: skap_header_append :: unable to write to file\n");
    return 0;
  }
  return 1;
}
