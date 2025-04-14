#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "display.h"
#include <led-matrix-c.h>
#include <string.h>

struct RGBLedMatrix *matrix;
struct LedCanvas *canvas;
struct LedFont *font;

// Function to display score on the LED matrix
void display_score(int* totalScore, int argc, char **argv) {
    // init default options
    struct RGBLedMatrixOptions options;

    // Zero out the struct
    memset(&options, 0, sizeof(options));

    // Set some default values
    options.hardware_mapping = "regular";
    options.rows = 32;
    options.cols = 64;
    options.chain_length = 1;  // Set number of displays chained
    options.parallel = 1;     // Set number of parallel chains
    options.limit_refresh_rate_hz = 100;
    options.brightness = 100;  // Set brightness (1 to 100)

    // Delay in microseconds
    int delayUq = (1000 / options.limit_refresh_rate_hz)*1000;

    // Create the matrix based on options
    matrix = led_matrix_create_from_options(&options, &argc, &argv);

    // get canvas from matrix
    canvas = led_matrix_get_canvas(matrix);

    // Print any flags for debugging (if the function exists)
    // led_matrix_print_flags(stderr);

    // load font
    font = load_font("lib/rpi-rgb-led-matrix/fonts/10x20.bdf");
    char scoreStr[20];

    while (1) {
        led_canvas_clear(canvas);
        sprintf(scoreStr, "%d", *totalScore);
        int xStart = 32 - (strlen(scoreStr) * 5); // center the text (half width - half text width)
        int y = 22; // led height - font height
        draw_text(canvas, font, xStart, y, 255, 0, 0, scoreStr, 0);
        usleep(delayUq);
    }
}

void matrixCleanup() {
    // Cleaning up the matrix resources..
    led_matrix_delete(matrix);
    delete_font(font);
    free(matrix);
    free(canvas);
    free(font);
}
