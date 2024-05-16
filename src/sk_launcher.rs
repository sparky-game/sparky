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

mod sk_launcher_base;
mod sk_launcher_topbar;
mod sk_launcher_centralpanel;
mod sk_launcher_modulestab;
mod sk_launcher_logtab;
mod sk_launcher_clientwindow;
mod sk_launcher_serverwindow;

use std::env;
use eframe::egui;

static SK_LAUNCHER_NAME: &str = "sparky::launcher";
static SK_LAUNCHER_TAB_MODULES: &str = "Modules";
static SK_LAUNCHER_TAB_LOG: &str = "Console Log";

#[no_mangle]
pub extern "C" fn sk_launcher_run() -> u8 {
  println!("INFO: Initializing {}", SK_LAUNCHER_NAME);
  env::set_current_dir(env::current_exe().expect("ERROR: Unable to get binary path")
                       .parent().expect("ERROR: Unable to get binary parent directory path")
  ).expect("ERROR: Could not change CWD to the game's root directory");
  let win_icon = image::open("assets/icon.png").expect("ERROR: Failed to open icon path").to_rgba8();
  let (win_icon_width, win_icon_height) = win_icon.dimensions();
  eframe::run_native(
    SK_LAUNCHER_NAME,
    eframe::NativeOptions {
      viewport: egui::ViewportBuilder::default()
        .with_inner_size([600.0, 400.0])
        .with_min_inner_size([600.0, 400.0])
        .with_icon(egui::IconData {
          rgba: win_icon.into_raw(),
          width: win_icon_width,
          height: win_icon_height
        }),
      ..Default::default()
    },
    Box::new(|_| Box::new(sk_launcher_base::Launcher::default()) as Box<dyn eframe::App>)
  ).expect("Unexpected error. Shutting down...");
  println!("INFO: {} closed successfully", SK_LAUNCHER_NAME);
  return 0;
}
