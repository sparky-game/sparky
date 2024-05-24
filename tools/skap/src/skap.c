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


#include <assert.h>
#include <skap_file.h>
#include <skap_header.h>
#include <skap_idx_image.h>

#define ASSETPATH(s) "assets/" s
#define ARRLEN(x) (sizeof((x)) / sizeof((x)[0]))

static const char *imgs_paths[] = {
  ASSETPATH("icon.png")
};
static Image imgs[ARRLEN(imgs_paths)] = {0};
static skap_idx_image img_idxs[ARRLEN(imgs_paths)] = {0};

static void load_imgs(void) {
  for (usz i = 0; i < ARRLEN(imgs_paths); ++i) {
    imgs[i] = LoadImage(imgs_paths[i]);
    assert(imgs[i].data);
  }
}

static void unload_imgs(void) {
  for (usz i = 0; i < ARRLEN(imgs_paths); ++i) {
    UnloadImage(imgs[i]);
  }
}

int main(void) {
  load_imgs();
  FILE *fd = skap_file_create();
  skap_header header = skap_header_create();
  if (!skap_header_append(fd, &header)) {
    skap_file_destroy(fd);
    unload_imgs();
    return 1;
  }
  for (usz i = 0; i < ARRLEN(imgs_paths); ++i) {
    img_idxs[i] = skap_idx_image_create(imgs_paths[i], &imgs[i]);
    if (!skap_idx_image_append(fd, &img_idxs[i])) {
      skap_file_destroy(fd);
      unload_imgs();
      return 1;
    }
  }
  for (usz i = 0; i < ARRLEN(imgs_paths); ++i) {
    skap_idx_image_link_blob(&img_idxs[i], ftell(fd), imgs[i].width * imgs[i].height);
    printf("  WRITE   %s >> " SKAP_FILENAME "\n", imgs_paths[i]);
    if (fwrite(imgs[i].data, sizeof(Color), imgs[i].width * imgs[i].height, fd) != (usz) (imgs[i].width * imgs[i].height)) {
      fprintf(stderr, "ERROR: unable to write to file\n");
      skap_file_destroy(fd);
      unload_imgs();
      return 1;
    }
  }
  skap_file_destroy(fd);
  unload_imgs();
  return 0;
}
