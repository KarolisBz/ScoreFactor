# Compiler (64 ARM) and flags
CC = gcc # aarch64-linux-gnu-gcc
CFLAGS = -Wall -I./include 

# Linker flags (include pigpio and dependencies)
LDFLAGS = -L$(CURDIR)/lib/rpi-rgb-led-matrix/lib -lpigpio -lrt -lpthread -lrgbmatrix

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
RGB_LIB_DIR = $(CURDIR)/lib/rpi-rgb-led-matrix

# Targets
run: $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(BUILD_DIR)/run $(LDFLAGS)

# Creating object files in build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

rpi_rgb_led_matrix:
	$(MAKE) -C $(RGB_LIB_DIR)

# Ensuring build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Cleaning up build files and rpi matrix
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/run