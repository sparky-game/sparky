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


#include <assert.h>
#include <sk_scene_intro.h>
#include <sk_scene_main_menu.h>

#define INTRO_PHASE0_TXT1      "Wasym Atieh Alonso"
#define INTRO_PHASE0_TXT1_SIZE 30
#define INTRO_PHASE0_TXT2      "presents"
#define INTRO_PHASE0_TXT2_SIZE 26
#define INTRO_PHASE1_TXT       "a FOSS game"
#define INTRO_PHASE1_TXT_SIZE  30

void sk_scene_intro_update(sk_state *s) {
  assert(IsMusicReady(s->menu_music));
  if (!IsMusicStreamPlaying(s->menu_music)) {
    SetMusicVolume(s->menu_music, 0.35f);
    PlayMusicStream(s->menu_music);
  }
  else UpdateMusicStream(s->menu_music);
}

void sk_scene_intro_draw(sk_state *s) {
  static u8 phase = 0;
  static f32 time = 0;
  switch (phase) {
  case 0:
    ClearBackground(BLACK);
    DrawText(INTRO_PHASE0_TXT1,
             (GetScreenWidth() - MeasureText(INTRO_PHASE0_TXT1,
                                             INTRO_PHASE0_TXT1_SIZE)) / 2,
             (GetScreenHeight() - MeasureText(INTRO_PHASE0_TXT1,
                                              INTRO_PHASE0_TXT1_SIZE)) / 2,
             INTRO_PHASE0_TXT1_SIZE,
             RAYWHITE);
    DrawText(INTRO_PHASE0_TXT2,
             (GetScreenWidth() - MeasureText(INTRO_PHASE0_TXT2,
                                             INTRO_PHASE0_TXT2_SIZE)) / 2,
             ((GetScreenHeight() - MeasureText(INTRO_PHASE0_TXT2,
                                               INTRO_PHASE0_TXT2_SIZE)) / 2) - 55,
             INTRO_PHASE0_TXT2_SIZE,
             RAYWHITE);
    break;
  case 1:
    ClearBackground(BLACK);
    DrawText(INTRO_PHASE1_TXT,
             (GetScreenWidth() - MeasureText(INTRO_PHASE1_TXT,
                                             INTRO_PHASE1_TXT_SIZE)) / 2,
             (GetScreenHeight() - MeasureText(INTRO_PHASE1_TXT,
                                              INTRO_PHASE1_TXT_SIZE)) / 2,
             INTRO_PHASE1_TXT_SIZE,
             RAYWHITE);
    break;
  case 2:
    s->curr_scene.kind = SK_SCENE_KIND_MAIN_MENU;
    s->curr_scene.update = sk_scene_main_menu_update;
    s->curr_scene.draw = sk_scene_main_menu_draw;
    SetExitKey(KEY_THREE);
    return;
  default:
    assert(0 && "Unreachable");
  }
  if (time >= 9.3f) {
    time = 0;
    ++phase;
  }
  time += GetFrameTime();
}
