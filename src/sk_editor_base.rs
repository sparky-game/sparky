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
use SK_EDITOR_NAME;

pub struct Editor {
  pub curr_tab: String
}

impl Default for Editor {
  fn default() -> Self {
    Self {
      curr_tab: "Map".to_owned()
    }
  }
}

impl eframe::App for Editor {
  fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
    egui::TopBottomPanel::top(SK_EDITOR_NAME).show(ctx, |ui| {
      ui.horizontal(|ui| {
        egui::widgets::global_dark_light_mode_switch(ui);
        ui.separator();
      });
    });
  }
}
