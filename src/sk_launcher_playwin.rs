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


use libc::c_char;
use eframe::egui;

extern "C" {
  fn sk_client_run(ip: *const c_char) -> u8;
  fn sk_server_run() -> u8;
}

pub struct PlayWin {
  ip: String
}

impl Default for PlayWin {
  fn default() -> Self {
    Self {
      ip: "".to_owned()
    }
  }
}

impl eframe::App for PlayWin {
  fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
    egui::TopBottomPanel::top("Sparky Launcher").show(ctx, |ui| {
      ui.horizontal(|ui| {
        egui::widgets::global_dark_light_mode_switch(ui);
      });
    });
    egui::CentralPanel::default().show(ctx, |ui| {
      egui::Window::new("Client")
        .default_size([100.0, 100.0])
        .show(ctx, |ui| {
          ui.horizontal(|ui| {
            let ip_label = ui.label("IP: ");
            ui.text_edit_singleline(&mut self.ip).labelled_by(ip_label.id);
          });
          if ui.button("Play").clicked() { unsafe { sk_client_run(std::ptr::null()); } }
        });
      egui::Window::new("Server")
        .default_size([100.0, 100.0])
        .show(ctx, |ui| {
          if ui.button("Start").clicked() { unsafe { sk_server_run(); } }
        });
    });
  }
}
