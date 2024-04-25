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

use libc::c_char;
use eframe::egui;

struct Launcher {
  curr_tab: String,
  ip: String
}

extern "C" {
  fn sk_client_run(ip: *const c_char) -> u8;
  fn sk_server_run() -> u8;
}

static SK_LAUNCHER_NAME: &str = "sparky::launcher";
static SK_LAUNCHER_TAB_MODULES: &str = "Modules";
static SK_LAUNCHER_TAB_LOG: &str = "Console Log";

impl Default for Launcher {
  fn default() -> Self {
    Self {
      curr_tab: "Modules".to_owned(),
      ip: "".to_owned()
    }
  }
}

impl eframe::App for Launcher {
  fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
    egui::TopBottomPanel::top(SK_LAUNCHER_NAME).show(ctx, |ui| {
      ui.horizontal(|ui| {
        egui::widgets::global_dark_light_mode_switch(ui);
        ui.separator();
        if ui.selectable_label(self.curr_tab == SK_LAUNCHER_TAB_MODULES, SK_LAUNCHER_TAB_MODULES).clicked() {
          self.curr_tab = SK_LAUNCHER_TAB_MODULES.to_owned();
        }
        if ui.selectable_label(self.curr_tab == SK_LAUNCHER_TAB_LOG, SK_LAUNCHER_TAB_LOG).clicked() {
          self.curr_tab = SK_LAUNCHER_TAB_LOG.to_owned();
        }
      });
    });
    egui::CentralPanel::default().show(ctx, |_| {
      if self.curr_tab == SK_LAUNCHER_TAB_MODULES {
        egui::Window::new("Client").show(ctx, |ui| {
          ui.horizontal(|ui| {
            let ip_label = ui.label("IP: ");
            ui.text_edit_singleline(&mut self.ip).labelled_by(ip_label.id);
          });
          if ui.button("Play").clicked() {
            if self.ip.is_empty() { unsafe { sk_client_run(std::ptr::null()); } }
            else {
              let ip_addr = std::ffi::CString::new(self.ip.clone()).unwrap();
              unsafe { sk_client_run(ip_addr.as_ptr()); }
            }
          }
        });
        egui::Window::new("Server").show(ctx, |ui| {
          if ui.button("Start").clicked() { unsafe { sk_server_run(); } }
        });
      }
      else if self.curr_tab == SK_LAUNCHER_TAB_LOG {
        // TODO: Add a section where all stdout/stderr output is shown
      }
    });
  }
}

#[no_mangle]
pub extern "C" fn sk_launcher_run() -> u8 {
  println!("INFO: Initializing {}", SK_LAUNCHER_NAME);
  let options = eframe::NativeOptions {
    viewport: egui::ViewportBuilder::default()
      .with_inner_size([800.0, 600.0])
      .with_min_inner_size([300.0, 220.0]),
    ..Default::default()
  };
  let _ = eframe::run_native(
    SK_LAUNCHER_NAME,
    options,
    Box::new(|_| Box::new(Launcher::default()) as Box<dyn eframe::App>)
  );
  println!("INFO: {} closed successfully", SK_LAUNCHER_NAME);
  return 0;
}
