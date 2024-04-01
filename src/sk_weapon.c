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

sk_weapon sk_weapon_create(sk_weapon_kind kind) {
  sk_weapon w = {0};
  w.model = LoadModel(TextFormat("assets/models/%s.glb", sk_weapon_kinds[kind]));
  w.model_anims = LoadModelAnimations(TextFormat("assets/models/%s.glb", sk_weapon_kinds[kind]),
                                      (int *) &w.model_anims_count);
  assert(w.model_anims_count == 1);
  assert(IsModelAnimationValid(w.model, w.model_anims[0]));
  w.model_anim_frame_count = 0;
  w.sound_shoot = LoadSound(TextFormat("assets/sounds/%s/shoot.wav", sk_weapon_kinds[kind]));
  w.kind = kind;
  return w;
}

void sk_weapon_destroy(sk_weapon *w) {
  UnloadSound(w->sound_shoot);
  UnloadModelAnimations(w->model_anims, w->model_anims_count);
  UnloadModel(w->model);
  w = 0;
}

void sk_weapon_draw(sk_weapon *w, Vector3 pos) {
  DrawModelEx(w->model,
              pos,
              (Vector3) { 1, 0, 0 },
              275,
              (Vector3) { 0.5f, 0.5f, 0.5f },
              WHITE);
}

void sk_weapon_shoot(sk_weapon *w) {
  ++w->model_anim_frame_count;
  UpdateModelAnimation(w->model, w->model_anims[0], w->model_anim_frame_count);
  if (w->model_anim_frame_count >= w->model_anims[0].frameCount) w->model_anim_frame_count = 0;
  PlaySound(w->sound_shoot);
}
