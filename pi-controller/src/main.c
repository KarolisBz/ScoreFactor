#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <signal.h>
#include "display.h"
#include "vibration_sensors.h"

// BCM pin numbering, all vibration pins
#define VIBRATION_PIN_S5 20  // Pin 38 on pi GPIO header (score 5)
#define VIBRATION_PIN_S4 13  // Pin 33 on pi GPIO header (score 4)
#define VIBRATION_PIN_S3 16  // Pin 36 on pi GPIO header (score 3)
#define VIBRATION_PIN_S2 19  // Pin 35 on pi GPIO header (score 2)
#define VIBRATION_PIN_S1 26  // Pin 37 on pi GPIO header (score 1)

// interrupt signal
volatile sig_atomic_t interrupted = 0;

// function declarations
void handle_interrupt(int sig);

int main(int argc, char **argv) {
    // initalizing variables
    int total_score = 0;

    // Register SIGINT (Ctrl+C)
    signal(SIGINT, handle_interrupt);

    // printing welcome message
    printf("Welcome to Score Factor!\n");

    // init gpio pins
    if (gpioInitialise() < 0) {
        printf("Failed to initialize pigpio\n");
        return 1;
    }

    // intilizing vibration pins
    vibration_init(VIBRATION_PIN_S5, &total_score, 5);
    vibration_init(VIBRATION_PIN_S4, &total_score, 4);
    vibration_init(VIBRATION_PIN_S3, &total_score, 3);
    vibration_init(VIBRATION_PIN_S2, &total_score, 2);
    vibration_init(VIBRATION_PIN_S1, &total_score, 1);

    // keep program running
    printf("System running. Press Ctrl+C to stop.\n");
    start_game(&total_score, argc, argv, &interrupted); // Display score on LED matrix

    // graceful shutdown
    gpioTerminate();
    matrix_cleanup();
    vibration_stop();
    // exit with enough time for cleenup
    exit(1);
}

// extra functions functionalites:
void handle_interrupt(int sig) {
    interrupted = 1;
}