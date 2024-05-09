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

#include <raylib.h>
#include <sk_uuid.h>
#include <sk_defines.h>

typedef enum {
  SK_WEAPON_KIND_7MM,
  SK_WEAPON_KIND_AKM
} sk_weapon_kind;

typedef struct {
  u8 magazine;
  u8 reserve;
} sk_weapon_ammo_spec;

typedef struct {
  sk_weapon_kind kind;
  Model model;
  ModelAnimation *model_anims;
  u8 model_anims_count;
  u8 model_anim_frame_count;
  Sound sound_equip;
  Sound sound_shoot;
  Sound sound_reload;
  sk_weapon_ammo_spec ammo;
} sk_weapon;

typedef struct {
  Ray bullet;
  sk_uuid shooter_id;
  sk_weapon_kind weapon_kind;
} sk_shot;

static const char * const sk_weapon_kind2name[] = {
  [SK_WEAPON_KIND_7MM] = "7mm",
  [SK_WEAPON_KIND_AKM] = "akm"
};

static const sk_weapon_ammo_spec sk_weapon_kind2ammo[] = {
  [SK_WEAPON_KIND_7MM] = { 12, 3 },
  [SK_WEAPON_KIND_AKM] = { 25, 2 }
};

sk_weapon sk_weapon_create(sk_weapon_kind kind);

void sk_weapon_destroy(sk_weapon *w);

void sk_weapon_draw(sk_weapon *w, Camera3D *cam);

u8 sk_weapon_shoot(sk_weapon *w, sk_uuid id, Camera3D *cam, sk_shot *shot);

void sk_weapon_reload(sk_weapon *w);
