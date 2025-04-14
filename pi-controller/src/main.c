#include <stdio.h>
#include <unistd.h>
#include "add.h"
#include <pigpio.h>
#include "display.h"
#include "vibration_sensors.h"

// BCM pin numbering, all vibration pins
#define VIBRATION_PIN_S5 20  // Pin 38 on pi GPIO header (score 5)
#define VIBRATION_PIN_S4 13  // Pin 33 on pi GPIO header (score 4)
#define VIBRATION_PIN_S3 16  // Pin 36 on pi GPIO header (score 3)
#define VIBRATION_PIN_S2 19  // Pin 35 on pi GPIO header (score 2)
#define VIBRATION_PIN_S1 26  // Pin 37 on pi GPIO header (score 1)

int main() {
    // initalizing variables
    int total_score = 0;

    // printing welcome message
    printf("Welcome to Score Factor!\n");

    int sum = add(2, 3); // Example function call
    printf("Sum: %d\n", sum); // Example output

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
    display_score(&total_score); // Display score on LED matrix

    // closing program
    matrixCleanup();
    vibration_stop();
    gpioTerminate();
    return 0;
}