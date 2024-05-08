#
# GNU Sparky --- A 5v5 character-based libre tactical shooter
# Copyright (C) 2024 Wasym A. Alonso
#
# This file is part of Sparky.
#
# Sparky is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Sparky is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Sparky.  If not, see <http://www.gnu.org/licenses/>.
#


##################
# === MACROS === #
##################
LAUNCHER_NAME    = sk_launcher
GAME_NAME        = sparky
TEST_ENGINE_NAME = carbon
EDITOR_NAME      = sk_editor

include config.mk

# Version formatting
ifeq ($(wildcard .git/), .git/)
  ifneq ($(shell which git 2>/dev/null),)
    GIT_SHA := -git+$(shell git rev-parse --short HEAD)
  endif
  DEVEXTRAVERSION := $(or $(GIT_SHA), -dev)
endif
ifeq ($(SUBLEVEL), 0)
  DIST_VERSION = $(VERSION).$(PATCHLEVEL)$(EXTRAVERSION)
else
  DIST_VERSION = $(VERSION).$(PATCHLEVEL).$(SUBLEVEL)$(EXTRAVERSION)
endif
FULL_VERSION = $(DIST_VERSION)$(DEVEXTRAVERSION)

# Pretty Printing Output (PPO)
PPO_HOSTCC = HOSTCC
PPO_HOSTLD = HOSTLD
PPO_MKDIR  = MKDIR
PPO_CLEAN  = CLEAN
PPO_RSC    = RSC
PPO_CC     = CC
PPO_AR     = AR
PPO_LD     = LD

# Dependencies
CHECKDEPS_BINS  = mkdir mkfifo $(CC) ar rustc cargo jq
CHECKDEPS_HDRS  = stdint.h stddef.h X11/Xlib.h X11/Xcursor/Xcursor.h X11/extensions/Xrandr.h X11/extensions/Xinerama.h X11/extensions/XInput2.h
CHECKDEPS_TYPES = uint8_t int8_t uint16_t int16_t uint32_t int32_t uint64_t int64_t size_t long float double

# Directories
HDR_DIR               = include
SRC_DIR               = src
TEST_DIR              = test
BUILD_ROOT_DIR        = build
BUILD_DEBUG_DIR       = $(BUILD_ROOT_DIR)/debug
BUILD_RELEASE_DIR     = $(BUILD_ROOT_DIR)/release
EXTRAS_BUILD_ROOT_DIR = $(BUILD_ROOT_DIR)/$(GAME_NAME)_extras
ifdef D
  EXTRAS_BUILD_DIR = $(EXTRAS_BUILD_ROOT_DIR)/debug
  BUILD_DIR        = $(BUILD_DEBUG_DIR)
else
  EXTRAS_BUILD_DIR = $(EXTRAS_BUILD_ROOT_DIR)/release
  BUILD_DIR        = $(BUILD_RELEASE_DIR)
endif
TEST_BUILD_DIR   = $(BUILD_DIR)/$(TEST_DIR)
VENDOR_DIR       = vendor
RAYLIB_SRC_DIR   = $(VENDOR_DIR)/raylib/$(SRC_DIR)
RAYLIB_BUILD_DIR = $(BUILD_DIR)/raylib
LUA_SRC_DIR      = $(VENDOR_DIR)/lua
LUA_BUILD_DIR    = $(BUILD_DIR)/lua

# Files
RAYLIB_SRCS    := $(wildcard $(RAYLIB_SRC_DIR)/*.c)
RAYLIB_OBJS    := $(patsubst $(RAYLIB_SRC_DIR)/%.c, $(RAYLIB_BUILD_DIR)/%.o, $(RAYLIB_SRCS))
LUA_SRCS       := $(filter-out $(LUA_SRC_DIR)/onelua.c, $(wildcard $(LUA_SRC_DIR)/*.c))
LUA_OBJS       := $(patsubst $(LUA_SRC_DIR)/%.c, $(LUA_BUILD_DIR)/%.o, $(LUA_SRCS))
LAUNCHER_SRCS  := $(wildcard $(SRC_DIR)/$(LAUNCHER_NAME)*.rs)
SRCS           := $(wildcard $(SRC_DIR)/*.c)
OBJS           := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TEST_SRCS      := $(wildcard $(TEST_DIR)/$(SRC_DIR)/*.c)
TEST_OBJS      := $(patsubst $(TEST_DIR)/$(SRC_DIR)/%.c, $(TEST_BUILD_DIR)/%.o, $(TEST_SRCS))
TEST_DEPS_OBJS := $(filter-out $(BUILD_DIR)/$(GAME_NAME).o, $(OBJS))
EDITOR_SRCS    := $(wildcard $(SRC_DIR)/$(EDITOR_NAME)*.rs)

# Build flags
MAKEFLAGS_JOBS := $(patsubst -j%, %, $(filter -j%, $(MAKEFLAGS)))
ifndef MAKEFLAGS_JOBS
  CARGO_JOBS = -j1
endif
CC = gcc
ifeq ($(shell uname), Darwin)
  CC = clang
  MACOS_SPECIFIC_CFLAGS_OPTS  = -x objective-c
  MACOS_SPECIFIC_LDFLAGS_OPTS = -framework Cocoa -framework Carbon -framework CoreVideo -framework OpenGL -framework IOKit
else ifeq ($(shell uname), FreeBSD)
  CC = clang
else ifeq ($(shell uname), OpenBSD)
  CC = clang
  OPENBSD_SPECIFIC_LDFLAGS_OPTS = -lc++abi
endif
AR = ar -rc
ifdef Q_RSC
  CARGO_QUIET_OPTS = -q --message-format=json
endif
RSC      = cargo b $(CARGO_QUIET_OPTS) --target-dir $(EXTRAS_BUILD_ROOT_DIR) $(CARGO_JOBS) --locked
JQ_RSC   = jq -r 'if .reason == "compiler-artifact" and .target.name != "build-script-build" and .fresh == false then "  $(PPO_RSC)     " + .target.name else empty end'
FIFO_RSC = /tmp/sparky_cargo_pipe
ifdef D
  DEBUG_SYM_OPTS = -ggdb
else
  RSC                 += -r
  DISABLE_ASSERTS_OPTS = -D NDEBUG
  HIDE_WARNS_OPTS      = -w
  RELEASE_OPTS         = -pipe -O3
  ifeq ($(CC), gcc)
    RELEASE_OPTS += -fipa-pta
  endif
  ifneq ($(shell uname), Darwin)
    STRIP_OPTS = -s
  endif
endif
ifeq ($(CC), gcc)
  GCC_STATIC_LDFLAGS_OPTS = -static-libgcc
endif
ifneq ($(shell uname), Darwin)
  BUILDID_OPTS = -Wl,--build-id
endif
define RAYLIB_CPPFLAGS
  $(DISABLE_ASSERTS_OPTS)        \
  -D PLATFORM_DESKTOP            \
  -isystem /usr/local/$(HDR_DIR) \
  -isystem /usr/X11R6/$(HDR_DIR) \
  -isystem $(RAYLIB_SRC_DIR)     \
  -isystem $(RAYLIB_SRC_DIR)/external/glfw/$(HDR_DIR)
endef
define LUA_CPPFLAGS
  $(DISABLE_ASSERTS_OPTS) \
  -isystem $(LUA_SRC_DIR)
endef
define CPPFLAGS
  -D SK_VERSION=$(DIST_VERSION) \
  $(DISABLE_ASSERTS_OPTS)       \
  -D _POSIX_C_SOURCE=199309L    \
  -isystem $(RAYLIB_SRC_DIR)    \
  -isystem $(LUA_SRC_DIR)       \
  -I $(HDR_DIR)
endef
define TEST_CPPFLAGS
  $(DISABLE_ASSERTS_OPTS)                    \
  -isystem $(VENDOR_DIR)/$(TEST_ENGINE_NAME) \
  -I $(HDR_DIR)                              \
  -I $(TEST_DIR)/$(HDR_DIR)
endef
define RAYLIB_CFLAGS
  -std=gnu99                    \
  $(HIDE_WARNS_OPTS)            \
  $(DEBUG_SYM_OPTS)             \
  $(RELEASE_OPTS)               \
  $(MACOS_SPECIFIC_CFLAGS_OPTS) \
  -Wno-implicit-function-declaration
endef
define LUA_CFLAGS
  -std=c99          \
  $(DEBUG_SYM_OPTS) \
  $(RELEASE_OPTS)   \
  $(MACOS_SPECIFIC_CFLAGS_OPTS)
endef
define CFLAGS
  -std=gnu11        \
  -Wall             \
  -Wextra           \
  -pedantic         \
  -Werror           \
  $(DEBUG_SYM_OPTS) \
  $(RELEASE_OPTS)   \
  $(MACOS_SPECIFIC_CFLAGS_OPTS)
endef
define TEST_CFLAGS
  -std=c99                     \
  -Wall                        \
  -Wextra                      \
  -pedantic                    \
  -Werror                      \
  -fsanitize=address,undefined \
  $(DEBUG_SYM_OPTS)            \
  $(RELEASE_OPTS)              \
  $(MACOS_SPECIFIC_CFLAGS_OPTS)
endef
define LDFLAGS
  $(BUILDID_OPTS)                \
  $(HIDE_WARNS_OPTS)             \
  $(STRIP_OPTS)                  \
  $(RELEASE_OPTS)                \
  -L $(BUILD_DIR)                \
  -L $(EXTRAS_BUILD_DIR)         \
  -lraylib                       \
  -llua                          \
  -l$(LAUNCHER_NAME)             \
  -lpthread                      \
  -lm                            \
  $(GCC_STATIC_LDFLAGS_OPTS)     \
  $(MACOS_SPECIFIC_LDFLAGS_OPTS) \
  $(OPENBSD_SPECIFIC_LDFLAGS_OPTS)
endef
define TEST_LDFLAGS
  $(BUILDID_OPTS)    \
  $(HIDE_WARNS_OPTS) \
  $(STRIP_OPTS)      \
  $(RELEASE_OPTS)    \
  -L $(BUILD_DIR)    \
  -l:libasan.a       \
  -l:libubsan.a      \
  -lraylib           \
  -llua              \
  -lm
endef

# Build output
LAUNCHER_OUT = $(EXTRAS_BUILD_DIR)/lib$(LAUNCHER_NAME).a
RAYLIB_OUT   = $(BUILD_DIR)/libraylib.a
LUA_OUT      = $(BUILD_DIR)/liblua.a
ifdef D
  OUT = $(GAME_NAME)_debug
else
  OUT = $(GAME_NAME)
endif
TEST_OUT   = $(TEST_BUILD_DIR)/$(TEST_ENGINE_NAME)
EDITOR_OUT = $(EXTRAS_BUILD_DIR)/$(EDITOR_NAME)


###################
# === TARGETS === #
###################
.WAIT:
.PHONY: all checkdeps game check editor clean mrproper version help

all: checkdeps .WAIT $(BUILD_DIR) $(RAYLIB_BUILD_DIR) $(LUA_BUILD_DIR) game
	@:

checkdeps:
	@for i in $(CHECKDEPS_BINS); do                            \
	  if which $${i} >/dev/null 2>&1; then                     \
	    printf "checking for $${i}... \033[1;32myes\033[0m\n"; \
	  else                                                     \
	    printf "checking for $${i}... \033[1;31mno\033[0m\n";  \
	    exit 1;                                                \
	  fi;                                                      \
	done
	@for i in $(CHECKDEPS_HDRS); do                                 \
	  if echo "#include <$${i}>" | $(CC) -E - >/dev/null 2>&1; then \
	    printf "checking for $${i}... \033[1;32myes\033[0m\n";      \
	  else                                                          \
	    printf "checking for $${i}... \033[1;31mno\033[0m\n";       \
	    exit 1;                                                     \
	  fi;                                                           \
	done
	@for i in $(CHECKDEPS_TYPES); do                                                                                      \
	  if echo "#include <stdint.h>\n#include <stddef.h>\n$${i} x;" | $(CC) -x c -S - -o /dev/stdout >/dev/null 2>&1; then \
	    printf "checking for $${i}... \033[1;32myes\033[0m\n";                                                            \
	  else                                                                                                                \
	    printf "checking for $${i}... \033[1;31mno\033[0m\n";                                                             \
	    exit 1;                                                                                                           \
	  fi;                                                                                                                 \
	done

$(BUILD_DIR):
	@echo "  $(PPO_MKDIR)   $@"
	$(Q)mkdir -p $@

$(RAYLIB_BUILD_DIR):
	@echo "  $(PPO_MKDIR)   $@"
	$(Q)mkdir -p $@

$(LUA_BUILD_DIR):
	@echo "  $(PPO_MKDIR)   $@"
	$(Q)mkdir -p $@

$(TEST_BUILD_DIR):
	@echo "  $(PPO_MKDIR)   $@"
	$(Q)mkdir -p $@

game: $(OUT)
	@printf "INFO: \033[1;35m$(OUT) is ready  ($(FULL_VERSION))\033[0m\n"

$(OUT): $(RAYLIB_OUT) $(LUA_OUT) $(LAUNCHER_OUT) $(OBJS)
	@echo "  $(PPO_LD)      $@"
	$(Q)$(CC) $(OBJS) $(LDFLAGS) -o $@

$(RAYLIB_OUT): $(RAYLIB_OBJS)
	@echo "  $(PPO_AR)      $@"
	$(Q)$(AR) $@ $^

$(RAYLIB_BUILD_DIR)/%.o: $(RAYLIB_SRC_DIR)/%.c
	@echo "  $(PPO_CC)      $@"
	$(Q)$(CC) $(RAYLIB_CPPFLAGS) $(RAYLIB_CFLAGS) -c -MD $< -o $@

$(LUA_OUT): $(LUA_OBJS)
	@echo "  $(PPO_AR)      $@"
	$(Q)$(AR) $@ $^

$(LUA_BUILD_DIR)/%.o: $(LUA_SRC_DIR)/%.c
	@echo "  $(PPO_CC)      $@"
	$(Q)$(CC) $(LUA_CPPFLAGS) $(LUA_CFLAGS) -c -MD $< -o $@

$(LAUNCHER_OUT): $(LAUNCHER_SRCS)
	@if [ ! -e $(FIFO_RSC) ]; then \
	  mkfifo $(FIFO_RSC);          \
	fi
	@$(JQ_RSC) < $(FIFO_RSC) &
	$(Q)$(RSC) --lib > $(FIFO_RSC)
	@rm $(FIFO_RSC)
	@echo "  $(PPO_AR)      $@"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "  $(PPO_CC)      $@"
	$(Q)$(CC) $(CPPFLAGS) $(CFLAGS) -c -MD $< -o $@

check: checkdeps .WAIT $(BUILD_DIR) $(RAYLIB_BUILD_DIR) $(LUA_BUILD_DIR) $(TEST_BUILD_DIR) $(TEST_OUT)
	@printf "INFO: \033[1;35m$(TEST_OUT) is ready  ($(FULL_VERSION))\033[0m\n"
	$(Q)./$(TEST_OUT)

$(TEST_OUT): $(RAYLIB_OUT) $(LUA_OUT) $(TEST_DEPS_OBJS) $(TEST_OBJS)
	@echo "  $(PPO_HOSTLD)  $@"
	$(Q)$(CC) $(TEST_DEPS_OBJS) $(TEST_OBJS) $(TEST_LDFLAGS) -o $@

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/$(SRC_DIR)/%.c
	@echo "  $(PPO_HOSTCC)  $@"
	$(Q)$(CC) $(TEST_CPPFLAGS) $(TEST_CFLAGS) -c -MD $< -o $@

editor: checkdeps .WAIT $(EDITOR_OUT)
	@printf "INFO: \033[1;35m$(EDITOR_OUT) is ready  ($(FULL_VERSION))\033[0m\n"

$(EDITOR_OUT): $(EDITOR_SRCS)
	@if [ ! -e $(FIFO_RSC) ]; then \
	  mkfifo $(FIFO_RSC);          \
	fi
	@$(JQ_RSC) < $(FIFO_RSC) &
	$(Q)$(RSC) --bin $(EDITOR_NAME) > $(FIFO_RSC)
	@rm $(FIFO_RSC)
	@echo "  $(PPO_LD)      $@"

-include $(BUILD_DIR)/*.d
-include $(LUA_BUILD_DIR)/*.d
-include $(TEST_BUILD_DIR)/*.d
-include $(RAYLIB_BUILD_DIR)/*.d
-include $(EXTRAS_BUILD_DIR)/*.d

clean:
	@if [ -d $(BUILD_ROOT_DIR) ]; then           \
	  echo "  $(PPO_CLEAN)   $(BUILD_ROOT_DIR)"; \
	  rm -r $(BUILD_ROOT_DIR);                   \
	fi
	@if [ -e $(FIFO_RSC) ]; then           \
	  echo "  $(PPO_CLEAN)   $(FIFO_RSC)"; \
	  rm $(FIFO_RSC);                      \
	fi

mrproper: clean
	@if [ -e $(GAME_NAME) ]; then           \
	  echo "  $(PPO_CLEAN)   $(GAME_NAME)"; \
	  rm $(GAME_NAME);                      \
	fi
	@if [ -e $(GAME_NAME)_debug ]; then           \
	  echo "  $(PPO_CLEAN)   $(GAME_NAME)_debug"; \
	  rm $(GAME_NAME)_debug;                      \
	fi

version:
	@echo $(FULL_VERSION)

help:
	@echo "Targets"
	@echo "======="
	@echo "  all       :: Build all targets marked with [*]"
	@echo "* checkdeps :: Check dependencies for build process"
	@echo "* game      :: Build the bare game"
	@echo "  check     :: Build and run the test engine"
	@echo "  editor    :: Build the editor"
	@echo "  clean     :: Remove the 'build' directory"
	@echo "  mrproper  :: Remove and cleans everything"
	@echo "  version   :: Show the current version string"
	@echo "  help      :: Show this help and usage panel"
	@echo
	@echo "Execute 'make' or 'make all' to build all targets marked with [*]"
	@echo "For further info see the ./README.org file"
