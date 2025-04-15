#include <stdio.h>
#include <stdlib.h>
#include <led-matrix-c.h>
#include <string.h>
#include "display.h"
#include "globals_settings.h"

static struct RGBLedMatrix *matrix = NULL;
static struct LedCanvas *canvas = NULL;
static struct LedFont *fontLarge = NULL;
static struct LedFont *font = NULL;
static char scoreStr[20];
static char timeRemaining[20];

void setup_display(int argc, char **argv)
{
    // init default options
    struct RGBLedMatrixOptions options;

    // Zero out the struct
    memset(&options, 0, sizeof(options));

    // Set some default values
    options.hardware_mapping = "regular";
    options.rows = 32;
    options.cols = 64;
    options.chain_length = 1; // Set number of displays chained
    options.parallel = 1;     // Set number of parallel chains
    options.brightness = 30;  // Set brightness (1 to 100)

    // Create the matrix based on options
    matrix = led_matrix_create_from_options(&options, &argc, &argv);

    // get canvas from matrix
    canvas = led_matrix_get_canvas(matrix);

    // load font
    fontLarge = load_font("lib/rpi-rgb-led-matrix/fonts/10x20.bdf");
    font = load_font("lib/rpi-rgb-led-matrix/fonts/8x13B.bdf");
}

// Function to display score on the LED matrix
void display_game_frame()
{
    // clearing old frame
    led_canvas_clear(canvas);
    sprintf(scoreStr, "%d", total_score);

    // fetching time left
    int minutes = game_time_seconds / 60;
    int seconds = game_time_seconds % 60;
    sprintf(timeRemaining, "%d:%02d", minutes, seconds);

    // draws the score
    int xStart = 32 - (strlen(scoreStr) * 5); // center the text (half width - half text width)
    int yScore = 28;
    draw_text(canvas, fontLarge, xStart, yScore, 255, 0, 0, scoreStr, 0);

    // draws the label and time, with different colors
    draw_text(canvas, font, -1, 11, 255, 252, 81, "Time", 0);
    draw_text(canvas, font, 33, 11, 255, 255, 255, timeRemaining, 0);
}

void matrix_cleanup()
{
    // Cleaning up the matrix resources..
    led_matrix_delete(matrix);
    delete_font(fontLarge);
    delete_font(font);
    free(matrix);
    free(canvas);
    free(fontLarge);
    free(font);
}