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
use libc::c_char;
use std::sync::Arc;
use sk_launcher_base;
use std::sync::atomic::Ordering;

extern "C" { fn sk_client_run(ip: *const c_char) -> u8; }

pub trait ClientWindow {
  fn update(&mut self, ctx: &egui::Context);
}

impl ClientWindow for sk_launcher_base::Launcher {
  fn update(&mut self, ctx: &egui::Context) {
    egui::Window::new("Client").show(ctx, |ui| {
      if self.is_client_running.load(Ordering::SeqCst) { ui.set_enabled(false); }
      ui.checkbox(&mut self.online_mode, "Online mode");
      if self.online_mode {
        ui.horizontal(|ui| {
          let ip_label = ui.label("IP: ");
          ui.text_edit_singleline(&mut self.ip).labelled_by(ip_label.id);
        });
      }
      if ui.button("Play").clicked() {
        self.is_client_running.store(true, Ordering::SeqCst);
        let is_client_running = Arc::clone(&self.is_client_running);
        if self.ip.is_empty() {
          thread::spawn(move || {
            unsafe { sk_client_run(std::ptr::null()); }
            is_client_running.store(false, Ordering::SeqCst);
          });
        }
        else {
          let ip_addr = std::ffi::CString::new(self.ip.clone()).unwrap();
          thread::spawn(move || {
            unsafe { sk_client_run(ip_addr.as_ptr()); }
            is_client_running.store(false, Ordering::SeqCst);
          });
        }
      }
    });
  }
}
