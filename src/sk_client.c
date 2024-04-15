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


#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sk_log.h>
#include <sk_state.h>
#include <arpa/inet.h>
#include <sk_config.h>
#include <sk_client.h>
#include <sk_server.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sk_renderer.h>

static void offline_mode(void) {
  SK_LOG_WARN("Running in offline mode");
  sk_state state = sk_state_create_offline();
  sk_renderer_loop {
    sk_renderer_update(&state);
    sk_renderer_draw(&state);
  }
  sk_state_destroy_offline(&state);
}

static i8 online_mode(const char *ip) {
  const struct sockaddr_in server_addr = {
    .sin_family = AF_INET,
    .sin_port = htons(SK_SERVER_PORT),
    .sin_addr.s_addr = inet_addr(ip)
  };
  i32 sock_fd = sk_server_socket_create();
  if (sock_fd == -1) return -1;
  SK_LOG_INFO("Connecting to `%s` ...", ip);
  if (sendto(sock_fd,
             SK_SERVER_MSG_HELLO,
             strlen(SK_SERVER_MSG_HELLO),
             0,
             (const struct sockaddr *) &server_addr,
             sizeof(server_addr)) == -1) {
    SK_LOG_ERROR("sendto(2) :: %s", strerror(errno));
    close(sock_fd);
    return -1;
  }
  char howdy_msg[SK_SERVER_MSG_MAX_SIZE];
  i32 howdy_msg_n = recv(sock_fd, howdy_msg, sizeof(howdy_msg), MSG_WAITALL);
  if (howdy_msg_n == -1) {
    SK_LOG_ERROR("recv(2) :: %s", strerror(errno));
    SK_LOG_ERROR("Unable to communicate with `%s`. Exiting...", ip);
    close(sock_fd);
    return -1;
  }
  howdy_msg[howdy_msg_n] = 0;
  i8 assigned_lobby_id = -1;
  i8 assigned_lobby_slot_idx = -1;
  u8 matched_data = sscanf(howdy_msg, SK_SERVER_MSG_HOWDY, &assigned_lobby_id, &assigned_lobby_slot_idx);
  (void) matched_data;
  assert(matched_data == 2);
  if (assigned_lobby_id == -1 || assigned_lobby_slot_idx == -1) {
    SK_LOG_ERROR("Connection rejected from `%s`. Exiting...", ip);
    close(sock_fd);
    return -1;
  }
  SK_LOG_INFO("Connected successfully to `%s` (lobby %i, slot %i)", ip, assigned_lobby_id, assigned_lobby_slot_idx);
  SK_LOG_WARN("Exiting due to not being fully implemented yet");
  sk_server_socket_destroy(sock_fd);
  return 0;
}

u8 sk_client_run(const char *ip) {
  SK_LOG_INFO("Initializing %s", SK_CLIENT_NAME);
  if (!ChangeDirectory(GetApplicationDirectory())) {
    SK_LOG_WARN("Could not change CWD to the game's root directory");
  }
  if (!ip) offline_mode();
  else if (online_mode(ip) == -1) {
    SK_LOG_ERROR("%s closed abruptly due to errors", SK_CLIENT_NAME);
    return 1;
  }
  SK_LOG_INFO("%s closed successfully", SK_CLIENT_NAME);
  return 0;
}
