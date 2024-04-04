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


extern crate libc;
extern crate eframe;

mod sk_launcher_playwin;

use eframe::egui;

static SK_LAUNCHER_NAME: &str = "sparky-client::launcher";

#[no_mangle]
pub extern "C" fn sk_launcher_run() -> u8 {
  println!("INFO: Initializing {}", SK_LAUNCHER_NAME);
  let options = eframe::NativeOptions {
    viewport: egui::ViewportBuilder::default()
      .with_inner_size([800.0, 600.0])
      .with_min_inner_size([300.0, 220.0])
      .with_drag_and_drop(true),
    ..Default::default()
  };
  let _ = eframe::run_native(
    "sparky-client::launcher",
    options,
    Box::new(|_| Box::new(sk_launcher_playwin::PlayWin::default()) as Box<dyn eframe::App>)
  );
  println!("INFO: {} closed successfully", SK_LAUNCHER_NAME);
  return 0;
}
