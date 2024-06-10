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


#include <stdlib.h>
#include <string.h>
#include <sk_log.h>
#include <sk_assetpack.h>
#include <skap_idx_image.h>

u8 sk_assetpack_open(sk_assetpack *ap) {
  if (!ap) {
    SK_LOG_ERROR("sk_assetpack_open :: `ap` needs to be a valid pointer");
    return 0;
  }
  FILE *fd = fopen("assets.skap", "rb");
  if (!fd) {
    SK_LOG_ERROR("sk_assetpack_open :: unable to open SKAP file (`assets.skap`)");
    return 0;
  }
  if (fread(&ap->header, sizeof(skap_header), 1, fd) != 1) {
    SK_LOG_ERROR("sk_assetpack_open :: unable to load header from SKAP file");
    *ap = (sk_assetpack) {0};
    ap = 0;
    fclose(fd);
    return 0;
  }
  if (strncmp(ap->header.signature, "SKAP", 4)) {
    SK_LOG_ERROR("sk_assetpack_open :: `assets.skap` is not a valid SKAP file");
    *ap = (sk_assetpack) {0};
    ap = 0;
    fclose(fd);
    return 0;
  }
  ap->idxs[SK_ASSETPACK_BLOB_KIND_IMAGE] = sk_hashmap_create(ap->header.idx_image_count, sizeof(skap_idx_image));
  for (usz i = 0; i < ap->header.idx_image_count; ++i) {
    skap_idx_image img_idx = {0};
    if (fread(&img_idx, sizeof(skap_idx_image), 1, fd) != 1) {
      SK_LOG_ERROR("sk_assetpack_open :: unable to load idx_image #%zu", i + 1);
      sk_hashmap_destroy(&ap->idxs[SK_ASSETPACK_BLOB_KIND_IMAGE]);
      *ap = (sk_assetpack) {0};
      ap = 0;
      fclose(fd);
      return 0;
    }
    if (!sk_hashmap_set(&ap->idxs[SK_ASSETPACK_BLOB_KIND_IMAGE], img_idx.metadata.name, &img_idx)) {
      SK_LOG_ERROR("sk_assetpack_open :: unable to insert idx_image #%zu in hashmap", i + 1);
      sk_hashmap_destroy(&ap->idxs[SK_ASSETPACK_BLOB_KIND_IMAGE]);
      *ap = (sk_assetpack) {0};
      ap = 0;
      fclose(fd);
      return 0;
    }
  }
  ap->blob_section_start_pos = ftell(fd);
  ap->fd = fd;
  return 1;
}

void sk_assetpack_close(sk_assetpack *ap) {
  if (!ap) {
    SK_LOG_WARN("sk_assetpack_close :: `ap` is not a valid pointer, skipping destruction");
    return;
  }
  for (usz i = 0; i < SK_ASSETPACK_BLOB_KIND_COUNT; ++i) sk_hashmap_destroy(&ap->idxs[i]);
  fclose(ap->fd);
  *ap = (sk_assetpack) {0};
  ap = 0;
}

u8 sk_assetpack_lookup(sk_assetpack *ap, sk_assetpack_blob_kind kind, const char *name, void *out_obj) {
  if (!name || !out_obj) {
    SK_LOG_ERROR("sk_assetpack_lookup :: `ap`, `name` and `out_obj` need to be valid pointers");
    return 0;
  }
  if (kind == SK_ASSETPACK_BLOB_KIND_IMAGE) {
    skap_idx_image img_idx = {0};
    if (!sk_hashmap_get(&ap->idxs[kind], name, &img_idx)) {
      SK_LOG_ERROR("sk_assetpack_lookup :: unable to retrieve idx_image `%s` from hashmap", name);
      return 0;
    }
    fseek(ap->fd, img_idx.blob_offset, SEEK_SET);
    ((Image *) out_obj)->width = img_idx.metadata.width;
    ((Image *) out_obj)->height = img_idx.metadata.height;
    ((Image *) out_obj)->mipmaps = img_idx.metadata.mipmaps;
    ((Image *) out_obj)->format = img_idx.metadata.format;
    ((Image *) out_obj)->data = malloc(sizeof(Color) * img_idx.blob_size);
    if (fread(((Image *) out_obj)->data, sizeof(Color), img_idx.blob_size, ap->fd) != img_idx.blob_size) {
      SK_LOG_ERROR("sk_assetpack_lookup :: unable to load image blob (`%s`) from SKAP file", name);
      free(((Image *) out_obj)->data);
      *((Image *) out_obj) = (Image) {0};
      return 0;
    }
    if (!IsImageReady(*((Image *) out_obj))) {
      SK_LOG_ERROR("sk_assetpack_lookup :: resulting parsed image (`%s`) is not valid");
      free(((Image *) out_obj)->data);
      *((Image *) out_obj) = (Image) {0};
      return 0;
    }
    fseek(ap->fd, ap->blob_section_start_pos, SEEK_SET);
  }
  else {
    SK_LOG_ERROR("sk_assetpack_lookup :: `kind` needs to be valid");
    return 0;
  }
  return 1;
}
