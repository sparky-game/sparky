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


#include <errno.h>
#include <dialog.h>
#include <sys/ioctl.h>

#define sk_xstr(s) sk_str(s)
#define sk_str(s) #s

#ifndef SK_VERSION
#define SK_VERSION "v0.0-UNDEFINED"
#endif
#define CONFIG_FILE "config.mk"
#define TITLE "Sparky " sk_xstr(SK_VERSION) " Build Configuration"
#define PADDING_HEIGHT 8
#define PADDING_WIDTH 7

char *items[] = {
  "D",     "Enable debug mode",                   "off",
  "Q",     "Make the build output less verbose",  "on",
  "Q_RSC", "Make the Rust compiler less verbose", "on"
};

int main(void) {
  struct winsize term_winsize;
  int status = 0, term_rows = 0, term_cols = 0;
  if (ioctl(STDIN_FILENO, TIOCGWINSZ, &term_winsize) == -1) {
    fprintf(stderr, "ERROR: unable to retrieve terminal's window size (%s)\n", strerror(errno));
  }
  term_rows = term_winsize.ws_row;
  term_cols = term_winsize.ws_col;
  init_dialog(stdin, stdout);
  dialog_vars.backtitle = CONFIG_FILE " - " TITLE;
  dialog_vars.ok_label = "Save";
  dlg_put_backtitle();
  status = dialog_checklist(TITLE,
                            "Arrow keys navigate the menu.  <Space> toggles the options.",
                            term_rows - PADDING_HEIGHT, term_cols - PADDING_WIDTH, 0,
                            3,
                            items,
                            FLAG_CHECK);
  end_dialog();
  if (status) printf("\n\n\nYour configuration changes were NOT saved.\n\n");
  else {
    printf("\n\nconfiguration written to " CONFIG_FILE "\n\n");
    printf("*** End of the configuration.\n");
    printf("*** Execute 'make' to start the build or try 'make help'.\n\n");
  }
  return status;
}
