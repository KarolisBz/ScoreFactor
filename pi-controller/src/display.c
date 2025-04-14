#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "display.h"
#include <led-matrix-c.h>
#include <string.h>

struct RGBLedMatrix *matrix;
struct LedCanvas *canvas;

// Function to display score on the LED matrix
void display_score(int* totalScore, int argc, char **argv) {
    // init default options
    struct RGBLedMatrixOptions options;

    // Zero out the struct
    memset(&options, 0, sizeof(options));

    // Set some default values (adjust based on your setup and requirements)
    options.rows = 32;  // Set number of rows (modify as needed)
    options.chain_length = 1;  // Set number of displays chained
    options.brightness = 100;  // Set brightness (1 to 100)

    // Create the matrix based on options
    matrix = led_matrix_create_from_options(&options, &argc, &argv);

    // Print any flags for debugging (if the function exists)
    led_matrix_print_flags(stderr);

    while (1) {
        sleep(1);
    }
}

void matrixCleanup() {
    printf("Cleaning up the matrix resources...\n");
}
