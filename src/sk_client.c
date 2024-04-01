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
#include <string.h>
#include <unistd.h>
#include <sk_log.h>
#include <sk_state.h>
#include <arpa/inet.h>
#include <sk_config.h>
#include <sk_client.h>
#include <sk_server.h>
#include <sys/socket.h>
#include <sk_renderer.h>

u8 sk_client_run(const char *ip) {
  SK_LOG_INFO("Initializing %s", SK_CLIENT_NAME);
  if (!ChangeDirectory(GetApplicationDirectory())) {
    SK_LOG_WARN("Could not change CWD to the game's root directory");
  }
  if (!ip) {
    SK_LOG_WARN("Running in offline mode");
    sk_state state = sk_state_create_offline();
    sk_renderer_create();
    sk_renderer_loop {
      sk_renderer_update(&state);
      sk_renderer_draw(&state);
    }
    sk_player_destroy(&state.player);
    sk_renderer_destroy();
  }
  else {
    const struct sockaddr_in server_addr = {
      .sin_family = AF_INET,
      .sin_port = htons(SK_SERVER_PORT),
      .sin_addr.s_addr = inet_addr(ip)
    };
    int sock_fd = sk_server_socket_create();
    if (sock_fd == -1) return 1;
    SK_LOG_INFO("Connecting to `%s` ...", ip);
    if (sendto(sock_fd,
               SK_SERVER_MSG_HELLO,
               strlen(SK_SERVER_MSG_HELLO),
               0,
               (const struct sockaddr *) &server_addr,
               sizeof(server_addr)) == -1) {
      SK_LOG_ERROR("sendto(2) :: %s", strerror(errno));
      close(sock_fd);
      return 1;
    }
    char howdy_msg[SK_SERVER_MSG_MAX_SIZE];
    int howdy_msg_n = recv(sock_fd, howdy_msg, sizeof(howdy_msg), MSG_WAITALL);
    if (howdy_msg_n == -1) {
      SK_LOG_ERROR("recv(2) :: %s", strerror(errno));
      close(sock_fd);
      return 1;
    }
    howdy_msg[howdy_msg_n] = 0;
    SK_LOG_DEBUG(howdy_msg);
    // TODO: hardcoded now to 0/0 ... change this to save the received IDs
    if (strcmp(howdy_msg, TextFormat(SK_SERVER_MSG_HOWDY, 0, 0))) {
      SK_LOG_ERROR("Unable to communicate with `%s`. Exiting...", ip);
      close(sock_fd);
      return 1;
    }
    SK_LOG_INFO("Connected successfully to `%s`", ip);
    SK_LOG_WARN("Exit due to not being implemented yet");
    sk_server_socket_destroy(sock_fd);
  }
  SK_LOG_INFO("%s closed successfully", SK_CLIENT_NAME);
  return 0;
}
