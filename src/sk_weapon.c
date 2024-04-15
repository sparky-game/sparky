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
#include <string.h>
#include <assert.h>
#include <sk_weapon.h>
#include <raymath.h>

#define MODEL_PATH_PLACEHOLDER        "assets/models/%s.glb"
#define SOUND_SHOOT_PATH_PLACEHOLDER  "assets/sounds/%s/shoot.wav"
#define SOUND_RELOAD_PATH_PLACEHOLDER "assets/sounds/%s/reload.wav"

sk_weapon sk_weapon_create(sk_weapon_kind kind) {
  const char * const name = sk_weapon_kind2name[kind];
  const sk_weapon_ammo_spec ammo_spec = sk_weapon_kind2ammo[kind];
  sk_weapon w = {
    .kind = kind,
    .model = LoadModel(TextFormat(MODEL_PATH_PLACEHOLDER, name)),
    .model_anims = LoadModelAnimations(TextFormat(MODEL_PATH_PLACEHOLDER, name), (int *) &w.model_anims_count),
    .sound_shoot = LoadSound(TextFormat(SOUND_SHOOT_PATH_PLACEHOLDER, name)),
    .sound_reload = LoadSound(TextFormat(SOUND_RELOAD_PATH_PLACEHOLDER, name)),
    .ammo = (sk_weapon_ammo_spec) {
      .magazine = ammo_spec.magazine,
      .reserve = ammo_spec.reserve * ammo_spec.magazine
    }
  };
  assert(w.model_anims_count == 1);
  assert(IsModelAnimationValid(w.model, w.model_anims[0]));
  return w;
}

void sk_weapon_destroy(sk_weapon *w) {
  UnloadSound(w->sound_shoot);
  UnloadModelAnimations(w->model_anims, w->model_anims_count);
  UnloadModel(w->model);
  w = 0;
}

void sk_weapon_draw(sk_weapon *w, Camera3D *cam, Vector3 offset, f32 scale) {
  Vector3 weapon_pos = Vector3Add(cam->position, offset);
  // Vector3 weapon_pos = Vector3Project(Vector3Add(cam->position, offset), cam->target);
  DrawModelEx(w->model,
              weapon_pos,
              (Vector3) { 1, 0, 0 },
              275,
              (Vector3) { scale, scale, scale },
              WHITE);
}

void sk_weapon_shoot(sk_weapon *w) {
  if (!w->ammo.magazine || IsSoundPlaying(w->sound_reload)) return;
  ++w->model_anim_frame_count;
  UpdateModelAnimation(w->model, w->model_anims[0], w->model_anim_frame_count);
  if (w->model_anim_frame_count >= w->model_anims[0].frameCount) w->model_anim_frame_count = 0;
  PlaySound(w->sound_shoot);
  --w->ammo.magazine;
}

void sk_weapon_reload(sk_weapon *w) {
  const sk_weapon_ammo_spec ammo_spec = sk_weapon_kind2ammo[w->kind];
  if (!w->ammo.reserve || w->ammo.magazine == ammo_spec.magazine) return;
  PlaySound(w->sound_reload);
  u8 diff_ammo = w->ammo.reserve >= ammo_spec.magazine ? ammo_spec.magazine - w->ammo.magazine : w->ammo.reserve - w->ammo.magazine;
  w->ammo.magazine += diff_ammo;
  w->ammo.reserve -= diff_ammo;
}
