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
use sk_launcher_base;
use SK_LAUNCHER_NAME;
use SK_LAUNCHER_TAB_LOG;
use SK_LAUNCHER_TAB_MODULES;

pub trait TopBar {
  fn update(&mut self, ctx: &egui::Context);
}

impl TopBar for sk_launcher_base::Launcher {
  fn update(&mut self, ctx: &egui::Context) {
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
  }
}
