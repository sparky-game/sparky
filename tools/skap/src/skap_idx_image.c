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
#include <string.h>
#include <skap_idx_image.h>

void skap_idx_image_loadall(Image *imgs, const char **img_paths, usz size) {
  for (usz i = 0; i < size; ++i) {
    printf("  LOAD    %s\n", img_paths[i]);
    imgs[i] = LoadImage(img_paths[i]);
    assert(IsImageReady(imgs[i]));
  }
}

void skap_idx_image_unloadall(Image *imgs, usz size) {
  for (usz i = 0; i < size; ++i) {
    UnloadImage(imgs[i]);
  }
}

skap_idx_image skap_idx_image_create(const char *name, Image *img) {
  skap_idx_image i = {
    .metadata = (skap_idx_image_md) {
      .width = img->width,
      .height = img->height,
      .mipmaps = img->mipmaps,
      .format = img->format
    },
    .blob_offset = 0,
    .blob_size = 0
  };
  memset(i.metadata.name, 0, sizeof(i.metadata.name));
  strncpy(i.metadata.name, name, sizeof(i.metadata.name) - 1);
  return i;
}

u8 skap_idx_image_append(FILE *fd, skap_idx_image *i) {
  if (!fd || !i) {
    fprintf(stderr, "ERROR: skap_idx_image_append :: `fd` and `i` need to be valid pointers\n");
    return 0;
  }
  printf("  WRITE   skap_idx_image(%s) >> " SKAP_FILENAME "\n", i->metadata.name);
  if (fwrite(i, sizeof(skap_idx_image), 1, fd) != 1) {
    fprintf(stderr, "ERROR: skap_idx_image_append :: unable to write to file\n");
    return 0;
  }
  return 1;
}

void skap_idx_image_link_blob(skap_idx_image *i, usz blob_offset, usz blob_size) {
  if (!i || !blob_offset || !blob_size) {
    printf("WARNING: skap_idx_image_link_blob :: args need to be valid, skipping linkage\n");
    return;
  }
  printf("  LINK    skap_idx_image(%s) -> {%zu, %zu}\n", i->metadata.name, blob_offset, blob_size);
  i->blob_offset = blob_offset;
  i->blob_size = blob_size;
}

u8 skap_idx_image_blob_append(FILE *fd, const char *name, Image *img) {
  if (!fd || !img) {
    fprintf(stderr, "ERROR: skap_idx_image_blob_append :: `fd` and `img` need to be valid pointers\n");
    return 0;
  }
  printf("  WRITE   %s >> " SKAP_FILENAME "\n", name);
  if (fwrite(img->data, sizeof(Color), (usz) img->width * img->height, fd) != (usz) img->width * img->height) {
    fprintf(stderr, "ERROR: skap_idx_image_blob_append :: unable to write to file\n");
    return 0;
  }
  return 1;
}
