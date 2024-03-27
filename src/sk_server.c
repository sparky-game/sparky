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


#include <raylib.h>
#include <signal.h>
#include <sk_server.h>

#define NBNET_IMPL
#include <nbnet.h>
#include <net_drivers/udp.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <winsock2.h>
#include <synchapi.h>
#else
#include <time.h>
#endif

static volatile u8 running = 1;

static inline void __handle_interrupt(int signum) {
  if (signum == SIGINT) running = 0;
}

static void __wait_next_tick(double t) {
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

static inline u8 __shutdown(void) {
  NBN_GameServer_Stop();
  TraceLog(LOG_INFO, "%s closed successfully", SK_SERVER_NAME);
  return 0;
}

u8 sk_server_run(void) {
  TraceLog(LOG_INFO, "Initializing %s", SK_SERVER_NAME);
  NBN_UDP_Register();
  if (NBN_GameServer_StartEx(SK_SERVER_NAME, SK_SERVER_PORT, 1) == -1) {
    TraceLog(LOG_ERROR, "Unable to start the server");
    return 1;
  }
  // TODO: register msgs
  double dt = 1 / SK_SERVER_TICK_RATE;
  signal(SIGINT, __handle_interrupt);
  while (running) {
    __wait_next_tick(dt);
  }
  return __shutdown();
}
