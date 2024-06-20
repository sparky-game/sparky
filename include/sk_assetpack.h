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

#include <stdio.h>
#include <sk_hashmap.h>
#include <skap_header.h>

typedef enum {
  SK_ASSETPACK_BLOB_KIND_IMAGE,
  SK_ASSETPACK_BLOB_KIND_AUDIO,
  SK_ASSETPACK_BLOB_KIND_COUNT
} sk_assetpack_blob_kind;

typedef struct {
  FILE *fd;
  usz blob_section_start_pos;
  skap_header header;
  sk_hashmap idxs[SK_ASSETPACK_BLOB_KIND_COUNT];
} sk_assetpack;

u8 sk_assetpack_open(sk_assetpack *ap);

void sk_assetpack_close(sk_assetpack *ap);

u8 sk_assetpack_lookup(sk_assetpack *ap, sk_assetpack_blob_kind kind, const char *name, void *out_blob);
