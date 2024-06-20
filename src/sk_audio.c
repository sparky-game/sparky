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
#include <sk_audio.h>

static sk_assetpack *skap = 0;

void sk_audio_init(sk_assetpack *ap) { skap = ap; }

Sound sk_audio_load(const char *filename) {
#ifndef NDEBUG
  return LoadSound(filename);
#else
  if (!skap) SK_LOG_ERROR("sk_audio_load :: SKAP was not initialized (maybe forgot to exec `sk_audio_init` ?)");
  Wave wave = {0};
  if (!sk_assetpack_lookup(skap, SK_ASSETPACK_BLOB_KIND_AUDIO, filename, &wave)) {
    SK_LOG_ERROR("sk_audio_load :: unable to retrieve audio from SKAP file");
  }
  Sound sound = LoadSoundFromWave(wave);
  UnloadWave(wave);
  return sound;
#endif
}

Music sk_audio_stream_load(const char *filename) {
#ifndef NDEBUG
  return LoadMusicStream(filename);
#else
  if (!skap) SK_LOG_ERROR("sk_audio_stream_load :: SKAP was not initialized (maybe forgot to exec `sk_audio_init` ?)");
  Wave wave = {0};
  if (!sk_assetpack_lookup(skap, SK_ASSETPACK_BLOB_KIND_AUDIO, filename, &wave)) {
    SK_LOG_ERROR("sk_audio_stream_load :: unable to retrieve audio from SKAP file");
  }
  return LoadMusicStreamFromMemory(".mp3", wave.data, wave.frameCount * wave.channels * (wave.sampleSize / 8));
#endif
}
