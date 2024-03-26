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
#include <sk_weapon.h>
#include <sk_gametypes.h>

#define FILEPATH_BUFFER_MAX_SIZE 64

void sk_weapon_create(Player *p, sk_weapon_kind kind) {
  char filepath[FILEPATH_BUFFER_MAX_SIZE] = {0};
  sprintf(filepath, "assets/models/%s.glb", sk_weapon_kinds[kind]);
  p->weapon.model = LoadModel(filepath);
  p->weapon.model_anims = LoadModelAnimations(filepath,
                                             (int *) &p->weapon.model_anims_count);
  p->weapon.model_anim_frame_count = 0;
  memset(filepath, 0, sizeof(filepath));
  sprintf(filepath, "assets/sounds/%s/shoot.wav", sk_weapon_kinds[kind]);
  p->weapon.sound_shoot = LoadSound(filepath);
}

void sk_weapon_destroy(sk_weapon *w) {
  UnloadSound(w->sound_shoot);
  UnloadModelAnimations(w->model_anims, w->model_anims_count);
  UnloadModel(w->model);
  *w = (sk_weapon) {0};
}

void sk_weapon_shoot(sk_weapon *w) {
  ++w->model_anim_frame_count;
  UpdateModelAnimation(w->model, w->model_anims[0], w->model_anim_frame_count);
  if (w->model_anim_frame_count >= w->model_anims[0].frameCount) w->model_anim_frame_count = 0;
  PlaySound(w->sound_shoot);
}
