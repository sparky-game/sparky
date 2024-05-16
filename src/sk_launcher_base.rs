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


use egui;
use std::sync::Arc;
use sk_launcher_topbar;
use SK_LAUNCHER_TAB_MODULES;
use sk_launcher_centralpanel;
use std::sync::atomic::AtomicBool;

pub struct Launcher {
  pub curr_tab: String,
  pub online_mode: bool,
  pub ip: String,
  pub is_client_running: Arc<AtomicBool>,
  pub is_server_running: Arc<AtomicBool>
}

impl Default for Launcher {
  fn default() -> Self {
    Self {
      curr_tab: SK_LAUNCHER_TAB_MODULES.to_owned(),
      online_mode: false,
      ip: "".to_owned(),
      is_client_running: Arc::new(AtomicBool::new(false)),
      is_server_running: Arc::new(AtomicBool::new(false))
    }
  }
}

impl eframe::App for Launcher {
  fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
    <Launcher as sk_launcher_topbar::TopBar>::update(self, ctx);
    <Launcher as sk_launcher_centralpanel::CentralPanel>::update(self, ctx);
  }
}
