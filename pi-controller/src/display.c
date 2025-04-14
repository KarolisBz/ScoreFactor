#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <led-matrix-c.h>
#include <string.h>
#include <signal.h>
#include "display.h"

static struct RGBLedMatrix *matrix = NULL;
static struct LedCanvas *canvas = NULL;
static struct LedFont *fontLarge = NULL;
static struct LedFont *font = NULL;

static const int ROUND_LENGTH = 120; // Length of the round in seconds

// Function to display score on the LED matrix
void start_game(int* totalScore, int argc, char **argv, volatile sig_atomic_t *interrupted) {
    // init default options
    struct RGBLedMatrixOptions options;
    int total_seconds = ROUND_LENGTH;
    int refreshRateCycle = 0; // when reaches 10, 1 second has passed back to 0 hence "cycle"

    // Zero out the struct
    memset(&options, 0, sizeof(options));

    // Set some default values
    options.hardware_mapping = "regular";
    options.rows = 32;
    options.cols = 64;
    options.chain_length = 1;  // Set number of displays chained
    options.parallel = 1;     // Set number of parallel chains
    options.brightness = 30;  // Set brightness (1 to 100)

    // Create the matrix based on options
    matrix = led_matrix_create_from_options(&options, &argc, &argv);

    // get canvas from matrix
    canvas = led_matrix_get_canvas(matrix);

    // load font
    fontLarge = load_font("lib/rpi-rgb-led-matrix/fonts/10x20.bdf");
    font = load_font("lib/rpi-rgb-led-matrix/fonts/8x13B.bdf");
    char scoreStr[20];
    char timeRemaining[20];

    while (!*interrupted) {
        // clearing old frame
        led_canvas_clear(canvas);
        sprintf(scoreStr, "%d", *totalScore);

        // fetching time left
        int minutes = total_seconds / 60;
        int seconds = total_seconds % 60;
        sprintf(timeRemaining, "%d:%02d", minutes, seconds);

        // draws the score
        int xStart = 32 - (strlen(scoreStr) * 5); // center the text (half width - half text width)
        int yScore = 28;
        draw_text(canvas, fontLarge, xStart, yScore, 255, 0, 0, scoreStr, 0);

        // draws the label and time, with different colors
        draw_text(canvas, font, -1, 11, 255, 252, 81, "Time", 0);
        draw_text(canvas, font, 33, 11, 255, 255, 255, timeRemaining, 0);

        // updating cycle
        refreshRateCycle++;
        if (refreshRateCycle >= 10) {
            refreshRateCycle = 0;

            // prevent negative time
            if (total_seconds > 0) {
                total_seconds--;
            }
        }

        // 100ms delay for refresh rate
        usleep(100000);
    }
}

void matrix_cleanup() {
    // Cleaning up the matrix resources..
    led_matrix_delete(matrix);
    delete_font(fontLarge);
    delete_font(font);
    free(matrix);
    free(canvas);
    free(fontLarge);
    free(font);
}
