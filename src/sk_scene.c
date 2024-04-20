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
#include <sk_scene.h>
#include <sk_state.h>
#include <sk_config.h>

#define INTRO_PHASE0_TXT1      "Wasym Atieh Alonso"
#define INTRO_PHASE0_TXT1_SIZE 30
#define INTRO_PHASE0_TXT2      "presents"
#define INTRO_PHASE0_TXT2_SIZE 26
#define INTRO_PHASE1_TXT       "a FOSS game"
#define INTRO_PHASE1_TXT_SIZE  30
#define MAIN_MENU_TXT          "SPARKY"
#define MAIN_MENU_TXT_SIZE     80

static void sk_scene_kind_gameplay_update(sk_state *s) {
  if (IsMouseButtonPressed(s->config.controls.shoot)) sk_weapon_shoot(&s->player.weapon);
  if (IsKeyPressed(s->config.controls.reload)) sk_weapon_reload(&s->player.weapon);
  sk_player_jump(&s->player, &s->config);
  sk_player_move(&s->player, &s->config, sk_player_peek(&s->player, &s->config));
}

static void sk_scene_kind_gameplay_draw(sk_state *s) {
  // World
  ClearBackground(SKYBLUE);
  BeginMode3D(s->player.camera);
  sk_weapon_draw(&s->player.weapon, &s->player.camera, (Vector3) { 1, -1, -3 }, 0.5f);
  sk_player_draw(&s->player);
  sk_map_draw(&s->map);
  EndMode3D();
  // HUD
  DrawText("v" sk_xstr(SK_VERSION),
           GetScreenWidth() - 100,
           GetScreenHeight() - 20,
           14,
           GRAY);
  DrawFPS(10, 10);
  DrawText(TextFormat("%.4f ms", GetFrameTime() * 1000), 10, 33, 20, LIME);
  if (s->is_online) {
    DrawText(TextFormat("N/A ms"), 10, 50, 20, LIME);
    DrawText(TextFormat("(d) N/A bps | (u) N/A bps"), 10, 70, 20, LIME);
  }
  // START: HUD's Crosshair
  DrawCircle(GetScreenWidth() / 2,
             GetScreenHeight() / 2,
             s->config.crosshair.radius,
             BLACK);
  DrawCircle(GetScreenWidth() / 2,
             GetScreenHeight() / 2,
             s->config.crosshair.radius - 0.9f,
             WHITE);
  // END: HUD's Crosshair
  DrawText(TextFormat("%u", s->player.hp),
           100,
           GetScreenHeight() - 100,
           25,
           RAYWHITE);
  DrawText(TextFormat("%u | %u",
                      s->player.weapon.ammo.magazine,
                      s->player.weapon.ammo.reserve),
           GetScreenWidth() - 100,
           GetScreenHeight() - 100,
           25,
           RAYWHITE);
}

static void sk_scene_kind_main_menu_update(sk_state *s) {
  if (IsMusicStreamPlaying(s->menu_music)) UpdateMusicStream(s->menu_music);
  if (IsKeyPressed(KEY_ENTER)) {
    s->curr_scene.kind = SK_SCENE_KIND_GAMEPLAY;
    s->curr_scene.update = sk_scene_kind_gameplay_update;
    s->curr_scene.draw = sk_scene_kind_gameplay_draw;
    StopMusicStream(s->menu_music);
    sk_player_load(&s->player, SK_WEAPON_KIND_7MM);
    sk_map_load(&s->map);
    DisableCursor();
  }
}

static void sk_scene_kind_main_menu_draw(sk_state *s) {
  (void) s;

  ClearBackground(BLACK);
  const char * const subtitle = "Press <ENTER> to start";
  u8 subtitle_size = 30;
  DrawText(MAIN_MENU_TXT,
           (GetScreenWidth() - MeasureText(MAIN_MENU_TXT,
                                           MAIN_MENU_TXT_SIZE)) / 2,
           (GetScreenHeight() - MeasureText(MAIN_MENU_TXT,
                                            MAIN_MENU_TXT_SIZE)) / 2,
           MAIN_MENU_TXT_SIZE,
           RAYWHITE);
  DrawText(subtitle,
           (GetScreenWidth() - MeasureText(subtitle, subtitle_size)) / 2,
           ((GetScreenHeight() - MeasureText(subtitle, subtitle_size)) / 2) + 115,
           subtitle_size,
           RAYWHITE);
  DrawText("v" sk_xstr(SK_VERSION),
           10,
           GetScreenHeight() - 25,
           20,
           RAYWHITE);
}

static void sk_scene_kind_intro_update(sk_state *s) {
  assert(IsMusicReady(s->menu_music));
  if (!IsMusicStreamPlaying(s->menu_music)) {
    SetMusicVolume(s->menu_music, 0.35f);
    PlayMusicStream(s->menu_music);
  }
  else UpdateMusicStream(s->menu_music);
}

static void sk_scene_kind_intro_draw(sk_state *s) {
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
    s->curr_scene.update = sk_scene_kind_main_menu_update;
    s->curr_scene.draw = sk_scene_kind_main_menu_draw;
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

sk_scene sk_scene_create(sk_scene_kind kind) {
  sk_scene s = {
    .kind = kind
  };
  switch (kind) {
  case SK_SCENE_KIND_INTRO:
    s.update = sk_scene_kind_intro_update;
    s.draw = sk_scene_kind_intro_draw;
    break;
  case SK_SCENE_KIND_MAIN_MENU:
    s.update = sk_scene_kind_main_menu_update;
    s.draw = sk_scene_kind_main_menu_draw;
    break;
  case SK_SCENE_KIND_GAMEPLAY:
    s.update = sk_scene_kind_gameplay_update;
    s.draw = sk_scene_kind_gameplay_draw;
    break;
  default:
    assert(0 && "Unreachable");
  }
  return s;
}
