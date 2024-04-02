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


use eframe::egui;
extern crate eframe;

#[no_mangle]
pub extern "C" fn sk_launcher_run() -> () {
  let options = eframe::NativeOptions {
    viewport: egui::ViewportBuilder::default().with_inner_size([320.0, 240.0]),
    ..Default::default()
  };
  eframe::run_native("sparky-client::launcher", options, Box::new(|_cc| {
    Box::new(Launcher::default()) as Box<dyn eframe::App>
  }));
}

struct Launcher {
  name: String,
  age: u32
}

impl Default for Launcher {
  fn default() -> Self {
    Self {
      name: "Wasym".to_owned(),
      age: 23
    }
  }
}

impl eframe::App for Launcher {
  fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
    egui::CentralPanel::default().show(ctx, |ui| {
      ui.heading("Sparky Launcher");
      ui.horizontal(|ui| {
        let name_label = ui.label("Name: ");
        ui.text_edit_singleline(&mut self.name).labelled_by(name_label.id);
      });
      ui.add(egui::Slider::new(&mut self.age, 0..=120).text("age"));
      if ui.button("Increment").clicked() { self.age += 1 }
      ui.label(format!("Hello '{}', age {}", self.name, self.age));
    });
  }
}
