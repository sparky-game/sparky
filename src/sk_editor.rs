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


extern crate eframe;

mod sk_editor_base;

use eframe::egui;

static SK_EDITOR_NAME: &str = "sparky::editor";

fn main() {
  println!("INFO: Initializing {}", SK_EDITOR_NAME);
  let win_icon = image::open("assets/icon.png").expect("ERROR: Failed to open icon path").to_rgba8();
  let (win_icon_width, win_icon_height) = win_icon.dimensions();
  eframe::run_native(
    SK_EDITOR_NAME,
    eframe::NativeOptions {
      viewport: egui::ViewportBuilder::default()
        .with_inner_size([800.0, 600.0])
        .with_min_inner_size([800.0, 600.0])
        .with_icon(egui::IconData {
          rgba: win_icon.into_raw(),
          width: win_icon_width,
          height: win_icon_height
        }),
      ..Default::default()
    },
    Box::new(|_| Box::new(sk_editor_base::Editor::default()) as Box<dyn eframe::App>)
  ).expect("Unexpected error. Shutting down...");
  println!("INFO: {} closed successfully", SK_EDITOR_NAME);
}
