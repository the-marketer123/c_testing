.PHONY: all clean

# =========================
# Project settings
# =========================
PROJECT_NAME ?= game
BUILD_MODE   ?= RELEASE

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
REL_DIR = releases

RAYLIB_PATH ?= ../..
COMPILER_PATH ?= C:/raylib/w64devkit/bin

# =========================
# Platform detection
# =========================
PLATFORM ?= PLATFORM_DESKTOP

ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(OS),Windows_NT)
        PLATFORM_OS = WINDOWS
        export PATH := $(COMPILER_PATH):$(PATH)
    else
        UNAMEOS := $(shell uname)
        ifeq ($(UNAMEOS),Linux)
            PLATFORM_OS = LINUX
        endif
        ifeq ($(UNAMEOS),Darwin)
            PLATFORM_OS = OSX
        endif
    endif
endif

# =========================
# Extension
# =========================
ifeq ($(PLATFORM_OS),WINDOWS)
    EXT = .exe
else
    EXT =
endif

# =========================
# Compiler
# =========================
CC = g++

# =========================
# Build mode flags
# =========================
ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS = -g -O0
else
    CFLAGS = -O2 -s
endif

CFLAGS += -Wall -std=c++14 -D_DEFAULT_SOURCE -Wno-missing-braces

# =========================
# Includes
# =========================
INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external

# =========================
# Linking
# =========================
LDFLAGS = -L$(RAYLIB_PATH)/src
LDLIBS  = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Windows libs
ifeq ($(PLATFORM_OS),WINDOWS)
    LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
endif

# Hide console in release (Windows only)
ifeq ($(PLATFORM_OS),WINDOWS)
    ifeq ($(BUILD_MODE),RELEASE)
        LDFLAGS += -mwindows -Wl,--subsystem,windows
    endif
endif

# =========================
# Files
# =========================
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

# =========================
# Default target
# =========================
all: $(PROJECT_NAME)

# =========================
# Link step
# =========================
ifeq ($(BUILD_MODE),RELEASE)
$(REL_DIR):
	mkdir $(REL_DIR)

$(PROJECT_NAME): $(OBJS) | $(REL_DIR)
	$(CC) -o $(REL_DIR)/$@$(EXT) $^ $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS)
else
$(BIN_DIR):
	mkdir $(BIN_DIR)

$(PROJECT_NAME): $(OBJS) | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@$(EXT) $^ $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS)
endif

# =========================
# Compile step
# =========================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS)

# Create obj folder
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# =========================
# Clean
# =========================
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) *.exe *.out *.o
	@echo Clean complete