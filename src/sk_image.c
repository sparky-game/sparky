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


#include <sk_log.h>
#include <sk_image.h>

static sk_assetpack *skap = 0;

void sk_image_init(sk_assetpack *ap) { skap = ap; }

Image sk_image_load(const char *filename) {
#ifndef NDEBUG
  return LoadImage(filename);
#else
  Image img = {0};
  if (!sk_assetpack_lookup(skap, SK_ASSETPACK_BLOB_KIND_IMAGE, filename, &img)) {
    SK_LOG_ERROR("sk_image_load :: unable to retrieve image from SKAP file");
  }
  return img;
#endif
}

Texture2D sk_image_gpu_load(const char *filename) {
#ifndef NDEBUG
  return LoadTexture(filename);
#else
  if (!skap) SK_LOG_ERROR("sk_image_gpu_load :: SKAP was not initialized (maybe forgot to exec `sk_image_init` ?)");
  Image img = {0};
  if (!sk_assetpack_lookup(skap, SK_ASSETPACK_BLOB_KIND_IMAGE, filename, &img)) {
    SK_LOG_ERROR("sk_image_gpu_load :: unable to retrieve image from SKAP file");
  }
  Texture2D tex = LoadTextureFromImage(img);
  UnloadImage(img);
  return tex;
#endif
}
