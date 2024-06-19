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
#include <assert.h>
#include <string.h>
#include <skap_idx_audio.h>

void skap_idx_audio_loadall(Wave *audios, const char **audio_paths, usz size) {
  InitAudioDevice();
  assert(IsAudioDeviceReady());
  for (usz i = 0; i < size; ++i) {
    printf("  LOAD    %s\n", audio_paths[i]);
    audios[i] = LoadWave(audio_paths[i]);
    assert(IsWaveReady(audios[i]));
  }
}

void skap_idx_audio_unloadall(Wave *audios, usz size) {
  for (usz i = 0; i < size; ++i) UnloadWave(audios[i]);
  CloseAudioDevice();
}

skap_idx_audio skap_idx_audio_create(const char *name, Wave *audio) {
  skap_idx_audio i = {
    .metadata = (skap_idx_audio_md) {
      .frame_count = audio->frameCount,
      .sample_rate = audio->sampleRate,
      .sample_size = audio->sampleSize,
      .channels    = audio->channels
    },
    .blob_offset = 0,
    .blob_size   = 0
  };
  memset(i.metadata.name, 0, sizeof(i.metadata.name));
  strncpy(i.metadata.name, name, sizeof(i.metadata.name) - 1);
  return i;
}

u8 skap_idx_audio_append(FILE *fd, skap_idx_audio *i) {
  if (!fd || !i) {
    fprintf(stderr, "ERROR: skap_idx_audio_append :: `fd` and `i` need to be valid pointers\n");
    return 0;
  }
  printf("  WRITE   skap_idx_audio(%s) >> " SKAP_FILENAME "\n", i->metadata.name);
  if (fwrite(i, sizeof(skap_idx_audio), 1, fd) != 1) {
    fprintf(stderr, "ERROR: skap_idx_audio_append :: unable to write to file\n");
    return 0;
  }
  return 1;
}

void skap_idx_audio_link_blob(skap_idx_audio *i, usz blob_offset, usz blob_size) {
  if (!i || !blob_offset || !blob_size) {
    printf("WARNING: skap_idx_audio_link_blob :: args need to be valid, skipping linkage\n");
    return;
  }
  printf("  LINK    skap_idx_audio(%s) -> {%zu, %zu}\n", i->metadata.name, blob_offset, blob_size);
  i->blob_offset = blob_offset;
  i->blob_size   = blob_size;
}

u8 skap_idx_audio_blob_append(FILE *fd, const char *name, Wave *audio) {
  if (!fd || !audio) {
    fprintf(stderr, "ERROR: skap_idx_audio_blob_append :: `fd` and `audio` need to be valid pointers\n");
    return 0;
  }
  printf("  WRITE   %s >> " SKAP_FILENAME "\n", name);
  usz audio_len = (usz) audio->frameCount * audio->channels * (audio->sampleSize / 8);
  if (fwrite(audio->data, sizeof(u8), audio_len, fd) != audio_len) {
    fprintf(stderr, "ERROR: skap_idx_audio_blob_append :: unable to write to file\n");
    return 0;
  }
  return 1;
}
