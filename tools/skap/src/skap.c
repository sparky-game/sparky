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

#define ARRLEN(x) (sizeof((x)) / sizeof((x)[0]))
#define return_defer(x) do { result = 1; goto defer; } while(0)

static const char *imgs_paths[] = {
  "assets/icon.png",
  "assets/images/loading-controls.png"
};
static Image imgs[ARRLEN(imgs_paths)] = {0};
static skap_idx_image img_idxs[ARRLEN(imgs_paths)] = {0};
static usz img_idx_locs[ARRLEN(imgs_paths)] = {0};

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
  int result = 0;
  load_imgs();
  FILE *fd = skap_file_create();
  skap_header header = skap_header_create();
  if (!skap_header_append(fd, &header)) {
    return_defer(1);
  }
  for (usz i = 0; i < ARRLEN(imgs_paths); ++i) {
    img_idxs[i] = skap_idx_image_create(imgs_paths[i], &imgs[i]);
    img_idx_locs[i] = ftell(fd);
    if (!skap_idx_image_append(fd, &img_idxs[i])) {
      return_defer(1);
    }
  }
  for (usz i = 0; i < ARRLEN(imgs_paths); ++i) {
    usz blob_loc = ftell(fd);
    skap_idx_image_link_blob(&img_idxs[i], blob_loc, (usz) imgs[i].width * imgs[i].height);
    fseek(fd, img_idx_locs[i], SEEK_SET);
    if (!skap_idx_image_append(fd, &img_idxs[i])) {
      return_defer(1);
    }
    fseek(fd, blob_loc, SEEK_SET);
    if (!skap_idx_image_blob_append(fd, imgs_paths[i], &imgs[i])) {
      return_defer(1);
    }
  }
 defer:
  skap_file_destroy(fd);
  unload_imgs();
  return result;
}
