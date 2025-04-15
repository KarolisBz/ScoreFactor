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
#define RESET_PIN 21        // Pin 40

// function declarations
void handle_interrupt();
void update_time_remaining(int *refreshRateCycle);
void inital_start_screen();
void start_game();
static void reset_callback(int gpio, int level, uint32_t tick);
void reset_init(int gpio_pin);

// static fields
static volatile sig_atomic_t interrupted = 0;
static bool game_started = false;
static uint32_t last_callback_time = 0;

int main(int argc, char **argv)
{
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

    // initializing reset pin
    reset_init(RESET_PIN); // no score for reset pin

    // setup display
    setup_display(argc, argv); // Display score on LED matrix

    // Display start screen
    inital_start_screen();

    // exit with enough time for cleenup
    exit(1);
}

// extra functions functionalites:
void handle_interrupt()
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

void inital_start_screen()
{
    // displaying start game
    while (!interrupted && !game_started)
    {
        // Display the score and time remaining
        display_text("Start!");

        // Sleep for a short duration to avoid busy waiting
        usleep(100000); // 0.1 seconds
    }

    start_game(9999); // supress recurssion call as this recursion is engineered
}

void start_game()
{
    // reset game stats in main thread
    game_time_seconds = ROUND_LENGTH; // reset game time to default
    atomic_store(&total_score, 0);    // reset score to 0

    // count down for game start
    count_down_display(5);

    // running game loop
    game_started = false;
    printf("System running. Press Ctrl+C to stop.\n");
    int refreshRateCycle = 0; // when reaches 10, 1 second has passed back to 0 hence "cycle"
    while (!interrupted && !game_started)
    {
        // Display the score and time remaining
        display_game_frame();

        // Update the time remaining
        update_time_remaining(&refreshRateCycle);

        // Sleep for a short duration to avoid busy waiting
        usleep(100000); // 0.1 seconds
    }

    if (interrupted) { return; } // infinte recursion engineered
    start_game();
}

static void reset_callback(int gpio, int level, uint32_t tick)
{
    if (level == PI_HIGH && (tick - last_callback_time) > 3000000)
    {
        // Reset the game state
        game_started = true;

        // Update last callback time
        last_callback_time = tick;
    }
}

void reset_init(int gpio_pin)
{
    gpioSetMode(gpio_pin, PI_INPUT);
    gpioSetAlertFunc(gpio_pin, reset_callback);
    printf("Reset pin initialized on GPIO %d\n", gpio_pin);
}