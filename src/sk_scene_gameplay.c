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


#include <sk_scene_gameplay.h>

void sk_scene_gameplay_update(sk_state *s) {
  sk_player_move(&s->player, &s->config, sk_player_peek(&s->player, &s->config));
  sk_player_jump(&s->player, &s->config);
  if (GetMouseWheelMove()) sk_player_rotate_weapon(&s->player);
  if (IsKeyPressed(s->config.controls.reload)) sk_weapon_reload(s->player.weapon);
  if (IsMouseButtonPressed(s->config.controls.shoot)) {
    sk_shot shot = {0};
    if (!sk_weapon_shoot(s->player.weapon, s->player.id, &s->player.camera, &shot)) return;
    sk_rngbuf_push(&s->shots_rb, &shot);
  }
}

void sk_scene_gameplay_draw(sk_state *s) {
  // World
  ClearBackground(SKYBLUE);
  BeginMode3D(s->player.camera);
  sk_weapon_draw(s->player.weapon, &s->player.camera);
  sk_player_draw(&s->player);
  sk_map_draw(&s->map);
  EndMode3D();
  // HUD
  DrawText("Client Version: " sk_xstr(SK_VERSION), GetScreenWidth() - 190, GetScreenHeight() - 20, 14, LIGHTGRAY);
  DrawFPS(10, 10);
  DrawText(TextFormat("%.4f ms", GetFrameTime() * 1000), 10, 33, 20, LIME);
  if (s->is_online) {
    DrawText(TextFormat("N/A ms"), 10, 50, 20, LIME);
    DrawText(TextFormat("(d) N/A bps | (u) N/A bps"), 10, 70, 20, LIME);
  }
  DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, s->config.crosshair.radius, BLACK);
  DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, s->config.crosshair.radius - 0.9f, RAYWHITE);
  DrawText(TextFormat("%u", s->player.hp), 100, GetScreenHeight() - 100, 25, RAYWHITE);
  DrawText(TextFormat("%u | %u", s->player.weapon->ammo.magazine, s->player.weapon->ammo.reserve),
           GetScreenWidth() - 100,
           GetScreenHeight() - 100,
           25,
           RAYWHITE);
  DrawTexture(s->player.weapon_slots[SK_PLAYER_IDX_SIDE_WEAPON].icon,
              GetScreenWidth() - s->player.weapon_slots[SK_PLAYER_IDX_SIDE_WEAPON].icon.width - 30,
              GetScreenHeight() - 260,
              s->player.weapon == &s->player.weapon_slots[SK_PLAYER_IDX_SIDE_WEAPON] ? YELLOW : WHITE);
  DrawTexture(s->player.weapon_slots[SK_PLAYER_IDX_MAIN_WEAPON].icon,
              GetScreenWidth() - s->player.weapon_slots[SK_PLAYER_IDX_MAIN_WEAPON].icon.width - 30,
              GetScreenHeight() - 200,
              s->player.weapon == &s->player.weapon_slots[SK_PLAYER_IDX_MAIN_WEAPON] ? YELLOW : WHITE);
}
