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
NAME = sparky

include config.mk

# Dev version string appended if no EXTRAVERSION is defined
ifndef EXTRAVERSION
  IS_GIT = yes
  EXTRAVERSION += $(or $(and $(wildcard .git/), -git+$$(git rev-parse --short HEAD)), -dev)
endif
# Version formatting
ifdef IS_GIT
  ifeq ($(SUBLEVEL), 0)
    DIST_VERSION = $(VERSION).$(PATCHLEVEL)
  else
    DIST_VERSION = $(VERSION).$(PATCHLEVEL).$(SUBLEVEL)
  endif
  FULL_VERSION = $(DIST_VERSION)$(EXTRAVERSION)
else
  DIST_VERSION = $(VERSION).$(PATCHLEVEL)$(EXTRAVERSION)
  FULL_VERSION = $(DIST_VERSION)
endif

# Pretty Printing Output (PPO)
PPO_MKDIR = MKDIR
PPO_CLEAN = CLEAN
PPO_CC    = CC
PPO_AR    = AR
PPO_LD    = LD

# Directories
SRC_DIR          = src
HDR_DIR          = include
BUILD_DIR        = build
VENDOR_DIR       = vendor
RAYLIB_SRC_DIR   = $(VENDOR_DIR)/raylib/$(SRC_DIR)
RAYLIB_BUILD_DIR = $(BUILD_DIR)/raylib

# Files
RAYLIB_SRCS := $(wildcard $(RAYLIB_SRC_DIR)/*.c)
RAYLIB_OBJS := $(patsubst $(RAYLIB_SRC_DIR)/%.c, $(RAYLIB_BUILD_DIR)/%.o, $(RAYLIB_SRCS))
SRCS        := $(wildcard $(SRC_DIR)/*.c)
OBJS        := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Build flags
CC              = gcc
AR              = ar -rc
RAYLIB_CPPFLAGS = -D PLATFORM_DESKTOP -I $(RAYLIB_SRC_DIR) -I $(RAYLIB_SRC_DIR)/external/glfw/$(HDR_DIR)
CPPFLAGS        = -I $(RAYLIB_SRC_DIR) -I $(HDR_DIR)
ifdef O
  OPT = -pipe -O3
endif
ifdef O_S
  OPT_STRIP = -s
endif
ifdef D
  ifdef O_S
    $(error Config options `O_S` and `D` are mutually exclusive)
  endif
  DEB = -ggdb
endif
RAYLIB_CFLAGS = $(DEB) $(OPT)
CFLAGS        = -Wall -Wextra -pedantic -Werror -fanalyzer $(DEB) $(OPT)
LDFLAGS       = -Wl,--build-id $(OPT_STRIP) $(OPT) -L $(BUILD_DIR) -lraylib -lm

# Build output
RAYLIB_OUT = $(BUILD_DIR)/libraylib.a
OUT        = $(NAME)

# Build targets
TGTS     = game
ALL_TGTS = $(BUILD_DIR) $(RAYLIB_BUILD_DIR) $(TGTS)


###################
# === TARGETS === #
###################
.PHONY: all $(TGTS) clean mrproper version help

all: $(ALL_TGTS)
	@:

game: $(RAYLIB_OUT) $(OUT)
	@echo "Game: $(OUT) is ready  ($(FULL_VERSION))"

$(BUILD_DIR):
	@echo "  $(PPO_MKDIR)   $@"
	$(Q)mkdir -p $@

$(RAYLIB_BUILD_DIR):
	@echo "  $(PPO_MKDIR)   $@"
	$(Q)mkdir -p $@

$(RAYLIB_OUT): $(RAYLIB_OBJS)
	@echo "  $(PPO_AR)      $@"
	$(Q)$(AR) $@ $^

$(OUT): $(OBJS)
	@echo "  $(PPO_LD)      $@"
	$(Q)$(CC) $^ $(LDFLAGS) -o $@

$(RAYLIB_BUILD_DIR)/%.o: $(RAYLIB_SRC_DIR)/%.c
	@echo "  $(PPO_CC)      $@"
	$(Q)$(CC) $(RAYLIB_CPPFLAGS) $(RAYLIB_CFLAGS) -c -MD $< -o $@

-include $(RAYLIB_BUILD_DIR)/*.d

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "  $(PPO_CC)      $@"
	$(Q)$(CC) $(CPPFLAGS) $(CFLAGS) -c -MD $< -o $@

-include $(BUILD_DIR)/*.d

clean:
	@if [ -d $(BUILD_DIR) ]; then           \
	  echo "  $(PPO_CLEAN)   $(BUILD_DIR)"; \
	  rm -r $(BUILD_DIR);                   \
	fi

mrproper: clean
	@if [ -e $(OUT) ]; then           \
	  echo "  $(PPO_CLEAN)   $(OUT)"; \
	  rm $(OUT);                      \
	fi

version:
	@echo $(FULL_VERSION)

help:
	@echo "Targets"
	@echo "======="
	@echo "  all      :: Build all targets marked with [*]"
	@echo "* game     :: Build the bare game"
	@echo "  clean    :: Remove the 'build' directory"
	@echo "  mrproper :: Remove and cleans everything"
	@echo "  version  :: Shows the current version string"
	@echo "  help     :: Shows this help and usage panel"
	@echo
	@echo "Execute 'make' or 'make all' to build all targets marked with [*]"
	@echo "For further info see the ./README.org file"
