#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pigpio.h>
#include <signal.h>
#include <stdatomic.h>
#include "display.h"
#include "vibration_sensors.h"
#include "globals_settings.h"

// BCM pin numbering, all vibration pins
#define VIBRATION_PIN_S5 20 // Pin 38 on pi GPIO header (score 5)
#define VIBRATION_PIN_S4 13 // Pin 33 on pi GPIO header (score 4)
#define VIBRATION_PIN_S3 16 // Pin 36 on pi GPIO header (score 3)
#define VIBRATION_PIN_S2 19 // Pin 35 on pi GPIO header (score 2)
#define VIBRATION_PIN_S1 26 // Pin 37 on pi GPIO header (score 1)

// function declarations
void handle_interrupt(int sig);
void update_time_remaining(int *refreshRateCycle);

// static fields
static volatile sig_atomic_t interrupted = 0;

int main(int argc, char **argv)
{
    // initalizing variables
    game_time_seconds = ROUND_LENGTH;

    // Register SIGINT (Ctrl+C)
    signal(SIGINT, handle_interrupt);

    // printing welcome message
    printf("Welcome to Score Factor!\n");

    // init gpio pins
    if (gpioInitialise() < 0)
    {
        printf("Failed to initialize pigpio\n");
        return 1;
    }

    // intilizing vibration pins
    vibration_init(VIBRATION_PIN_S5, 5);
    vibration_init(VIBRATION_PIN_S4, 4);
    vibration_init(VIBRATION_PIN_S3, 3);
    vibration_init(VIBRATION_PIN_S2, 2);
    vibration_init(VIBRATION_PIN_S1, 1);

    // setup display
    setup_display(argc, argv); // Display score on LED matrix

    // running game loop
    printf("System running. Press Ctrl+C to stop.\n");
    int refreshRateCycle = 0; // when reaches 10, 1 second has passed back to 0 hence "cycle"
    while (!interrupted)
    {
        // Display the score and time remaining
        display_game_frame();

        // Update the time remaining
        update_time_remaining(&refreshRateCycle);

        // Sleep for a short duration to avoid busy waiting
        usleep(100000); // 0.1 seconds
    }

    // exit with enough time for cleenup
    exit(1);
}

// extra functions functionalites:
void handle_interrupt(int sig)
{
    interrupted = 1;
    vibration_stop();
    gpioTerminate();
    matrix_cleanup();
}

void update_time_remaining(int *refreshRateCycle)
{
    // updating cycle
    if (*refreshRateCycle >= 10)
    {
        *refreshRateCycle = 0;

        // prevent negative time
        if (game_time_seconds > 0)
        {
            game_time_seconds--;
        }
    }

    ++(*refreshRateCycle);
}