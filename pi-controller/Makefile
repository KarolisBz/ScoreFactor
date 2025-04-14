# Compiler (64 ARM) and flags
CC = gcc # aarch64-linux-gnu-gcc
CXX = g++ # C++ compiler (used only for linking)
CFLAGS = -Wall -I./include -I$(CURDIR)/lib/rpi-rgb-led-matrix/include

# Linker flags (include pigpio and dependencies)
LDFLAGS = -lpigpio -lrt -lpthread -L$(CURDIR)/lib/rpi-rgb-led-matrix/lib -lrgbmatrix


# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Source files
SRC_FILES = $(filter-out %.cpp, $(wildcard $(SRC_DIR)/*.c))
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

run: $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(BUILD_DIR)/run $(LDFLAGS)

# Creating object files in build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensuring build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Cleaning up build files and rpi matrix
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/run