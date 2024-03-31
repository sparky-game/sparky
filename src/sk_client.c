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
#include <raylib.h>
#include <sk_state.h>
#include <arpa/inet.h>
#include <sk_config.h>
#include <sk_client.h>
#include <sk_server.h>
#include <sys/socket.h>
#include <sk_renderer.h>

u8 sk_client_run(const char *ip) {
  TraceLog(LOG_INFO, "Initializing %s", SK_CLIENT_NAME);
  u8 is_online = 0;
  int sock_fd;
  if (!ip) TraceLog(LOG_WARNING, "Running in offline mode");
  else {
    TraceLog(LOG_INFO, "Connecting to `%s` ...", ip);
    const struct sockaddr_in server_addr = {
      .sin_family = AF_INET,
      .sin_port = htons(SK_SERVER_PORT),
      .sin_addr.s_addr = inet_addr(ip)
    };
    sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock_fd == -1) {
      TraceLog(LOG_ERROR, "socket(2) :: %s", strerror(errno));
      return 1;
    }
    if (sendto(sock_fd,
               SK_SERVER_MSG_CONN_REQ,
               strlen(SK_SERVER_MSG_CONN_REQ),
               0,
               (const struct sockaddr *) &server_addr,
               sizeof(server_addr)) == -1) {
      TraceLog(LOG_ERROR, "sendto(2) :: %s", strerror(errno));
      close(sock_fd);
      return 1;
    }
    char pong_msg[SK_SERVER_MSG_MAX_SIZE];
    int pong_msg_n = recv(sock_fd, pong_msg, sizeof(pong_msg), MSG_WAITALL);
    if (pong_msg_n == -1) {
      TraceLog(LOG_ERROR, "recv(2) :: %s", strerror(errno));
      close(sock_fd);
      return 1;
    }
    pong_msg[pong_msg_n] = 0;
    if (!strcmp(pong_msg, SK_SERVER_MSG_CONN_RES)) {
      is_online = 1;
    }
    if (!is_online) {
      TraceLog(LOG_ERROR, "Unable to communicate with `%s`. Exiting...", ip);
      close(sock_fd);
      return 1;
    }
    TraceLog(LOG_INFO, "Connected successfully to `%s`", ip);
  }
  if (!ChangeDirectory(GetApplicationDirectory())) {
    TraceLog(LOG_WARNING, "Could not change CWD to the game's root directory");
  }
  sk_state state = sk_state_create(is_online);
  if (!is_online) {
    sk_renderer_create();
    sk_renderer_loop {
      sk_renderer_update(&state);
      sk_renderer_draw(&state);
    }
    sk_player_destroy(&state.player);
    sk_renderer_destroy();
  }
  else {
    TraceLog(LOG_WARNING, "Not implemented yet");
  }
  if (is_online) close(sock_fd);
  TraceLog(LOG_INFO, "%s closed successfully", SK_CLIENT_NAME);
  return 0;
}
