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
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <raylib.h>
#include <sk_server.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <winsock2.h>
#include <synchapi.h>
#else
#include <time.h>
#endif

static volatile u8 running = 1;
static volatile u8 clients = 0;

static inline void handle_interrupt(int signum) {
  if (signum == SIGINT) running = 0;
}

static void wait_next_tick(double t) {
#if defined(_WIN32) || defined(_WIN64)
  Sleep(1000 * t);
#else
  long ns_t = 1e9 * t;
  struct timespec ts = {
    .tv_sec  = ns_t / (long) (1e9 - 1),
    .tv_nsec = ns_t % (long) (1e9 - 1)
  };
  nanosleep(&ts, &ts);
#endif
}

u8 sk_server_run(void) {
  TraceLog(LOG_INFO, "Initializing %s", SK_SERVER_NAME);
  const struct sockaddr_in server_addr = {
    .sin_family = AF_INET,
    .sin_port = htons(SK_SERVER_PORT),
    .sin_addr.s_addr = inet_addr("127.0.0.1")
  };
  int sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sock_fd == -1) {
    TraceLog(LOG_ERROR, "socket(2) :: %s", strerror(errno));
    return 1;
  }
  if (bind(sock_fd, (const struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
    TraceLog(LOG_ERROR, "bind(2) :: %s", strerror(errno));
    close(sock_fd);
    return 1;
  }
  TraceLog(LOG_INFO, "UDP socket binded to 127.0.0.1:%d", SK_SERVER_PORT);
  double dt = 1 / SK_SERVER_TICK_RATE;
  signal(SIGINT, handle_interrupt);
  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  char msg[SK_SERVER_MSG_MAX_SIZE];
  int msg_n = 0;
  while (running) {
    client_addr = (struct sockaddr_in) {0};
    client_addr_len = sizeof(client_addr);
    memset(msg, 0, sizeof(msg));
    msg_n = 0;
    msg_n = recvfrom(sock_fd,
                     msg,
                     sizeof(msg),
                     MSG_WAITALL,
                     (struct sockaddr *) &client_addr,
                     &client_addr_len);
    if (msg_n == -1) {
      TraceLog(LOG_ERROR, "recvfrom(2) :: %s", strerror(errno));
      continue;
    }
    msg[msg_n] = 0;
    if (!strcmp(msg, SK_SERVER_MSG_CONN_REQ)) {
      TraceLog(LOG_INFO, "Connection from client (%s:%d) requested", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
      // TODO: check if there is a free slot in a lobby
      u8 lobby_id = 0;
      u8 lobby_slot_id = 0;
      // TODO: assign him a lobby and a player slot inside it
      memset(msg, 0, sizeof(msg));
      sprintf(msg, SK_SERVER_MSG_CONN_RES, lobby_id, lobby_slot_id);
      if (sendto(sock_fd,
                 msg,
                 strlen(SK_SERVER_MSG_CONN_RES),
                 0,
                 (struct sockaddr *) &client_addr,
                 client_addr_len) == -1) {
        TraceLog(LOG_ERROR, "sendto(2) :: %s", strerror(errno));
        continue;
      }
      TraceLog(LOG_INFO, "Connection from client (%s:%d) accepted", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    }
    wait_next_tick(dt);
  }
  close(sock_fd);
  TraceLog(LOG_INFO, "%s closed successfully", SK_SERVER_NAME);
  return 0;
}
