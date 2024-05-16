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
use std::thread;
use std::sync::Arc;
use sk_launcher_base;
use std::sync::atomic::Ordering;

extern "C" { fn sk_server_run() -> u8; }

pub trait ServerWindow {
  fn update(&mut self, ctx: &egui::Context);
}

impl ServerWindow for sk_launcher_base::Launcher {
  fn update(&mut self, ctx: &egui::Context) {
    egui::Window::new("Server").show(ctx, |ui| {
      if self.is_server_running.load(Ordering::SeqCst) { ui.set_enabled(false); }
      if ui.button("Start").clicked() {
        self.is_server_running.store(true, Ordering::SeqCst);
        let is_server_running = Arc::clone(&self.is_server_running);
        thread::spawn(move || {
          unsafe { sk_server_run(); }
          is_server_running.store(false, Ordering::SeqCst);
        });
      }
    });
  }
}
