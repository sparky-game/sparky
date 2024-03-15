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


#include <sparky_config.h>
#include <sparky_client.h>
#include <sparky_client_renderer.h>

void sparky_client_renderer_open_window(void) {
  InitWindow(SPARKY_CLIENT_WIN_WIDTH,
             SPARKY_CLIENT_WIN_HEIGHT,
             SPARKY_CLIENT_NAME);
  SetTargetFPS(SPARKY_CLIENT_FPS);
  DisableCursor();
}

void sparky_client_renderer_update(Player *p) {
  Vector2 dm = GetMouseDelta();
  float look_sens = 0.05f;
  float walk_sens = 0.1f;
  UpdateCameraPro(&p->camera,
                  (Vector3) {
                    IsKeyDown(KEY_W) * walk_sens - IsKeyDown(KEY_S) * walk_sens,
                    IsKeyDown(KEY_D) * walk_sens - IsKeyDown(KEY_A) * walk_sens,
                    0.0f
                  },
                  (Vector3) {
                    dm.x * look_sens,
                    dm.y * look_sens,
                    0.0f
                  },
                  0.0f);
}

static void sparky_client_renderer_draw_world(Player *p) {
  BeginMode3D(p->camera);
  DrawPlane((Vector3) { 0.0f, 0.0f, 0.0f },
            (Vector2) { 32.0f, 32.0f },
            DARKGRAY);
  DrawCube((Vector3) { -16.0f, 2.5f, 0.0f },
           1.0f, 5.0f, 32.0f, BLUE);
  DrawCube((Vector3) { 16.0f, 2.5f, 0.0f },
           1.0f, 5.0f, 32.0f, LIME);
  DrawCube((Vector3) { 0.0f, 2.5f, 16.0f },
           32.0f, 5.0f, 1.0f, GOLD);
  EndMode3D();
}

static void sparky_client_renderer_draw_hud(void) {
  DrawFPS(10, 10);
}

void sparky_client_renderer_draw(Player *p) {
  BeginDrawing();
  ClearBackground(BLACK);
  sparky_client_renderer_draw_world(p);
  sparky_client_renderer_draw_hud();
  EndDrawing();
}
