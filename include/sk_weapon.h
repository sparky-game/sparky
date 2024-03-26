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
#include <sk_defines.h>

// fwd-decl
struct Player;

typedef struct {
  Model model;
  ModelAnimation *model_anims;
  u8 model_anims_count;
  u8 model_anim_frame_count;
  Sound sound_shoot;
} sk_weapon;

typedef enum {
  SK_WEAPON_KIND_7MM
} sk_weapon_kind;

static const char * const sk_weapon_kinds[] = {
  [SK_WEAPON_KIND_7MM] = "7mm"
};

void sk_weapon_create(struct Player *p, sk_weapon_kind kind);

void sk_weapon_destroy(sk_weapon *w);

void sk_weapon_shoot(sk_weapon *w);
