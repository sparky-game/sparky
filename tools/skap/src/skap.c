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


#include <skap_file.h>
#include <skap_header.h>
#include <skap_idx_image.h>

#define IMG_COUNT SKAP_ARRLEN(img_paths)

static const char *img_paths[] = {
  "assets/icon.png",
  "assets/images/loading-controls.png",
  "assets/images/7mm/icon.png",
  "assets/images/akm/icon.png"
};
static Image imgs[IMG_COUNT] = {0};
static skap_idx_image img_idxs[IMG_COUNT] = {0};
static usz img_idx_locs[IMG_COUNT] = {0};

int main(void) {
  int result = 0;
  SetTraceLogLevel(LOG_WARNING);
  skap_idx_image_loadall(imgs, img_paths, IMG_COUNT);
  FILE *fd = skap_file_create();
  skap_header header = skap_header_create();
  if (!skap_header_append(fd, &header)) skap_return_defer(1);
  for (usz i = 0; i < IMG_COUNT; ++i) {
    img_idxs[i] = skap_idx_image_create(img_paths[i], &imgs[i]);
    img_idx_locs[i] = ftell(fd);
    if (!skap_idx_image_append(fd, &img_idxs[i])) skap_return_defer(1);
  }
  for (usz i = 0; i < IMG_COUNT; ++i) {
    usz blob_loc = ftell(fd);
    skap_idx_image_link_blob(&img_idxs[i], blob_loc, (usz) imgs[i].width * imgs[i].height);
    fseek(fd, img_idx_locs[i], SEEK_SET);
    if (!skap_idx_image_append(fd, &img_idxs[i])) skap_return_defer(1);
    fseek(fd, blob_loc, SEEK_SET);
    if (!skap_idx_image_blob_append(fd, img_paths[i], &imgs[i])) skap_return_defer(1);
  }
 defer:
  skap_file_destroy(fd);
  skap_idx_image_unloadall(imgs, IMG_COUNT);
  return result;
}
