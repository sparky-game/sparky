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
