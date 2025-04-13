#include <stdio.h>
#include <unistd.h>
#include "add.h"
#include <pigpio.h>
#include "vibration_sensors.h"

#define VIBRATION_PIN 20  // GPIO20 = Pin 38

int main() {
    printf("Welcome to Score Factor!\n");
    // Your code logic here

    int sum = add(2, 3); // Example function call
    printf("Sum: %d\n", sum); // Example output

    // init gpio pins
    if (gpioInitialise() < 0) {
        printf("Failed to initialize pigpio\n");
        return 1;
    }

    // intilizing vibration pins
    vibration_init(VIBRATION_PIN);

    printf("System running. Press Ctrl+C to stop.\n");
    while (1) {
        sleep(1);
    }

    // closing program
    vibration_stop();
    gpioTerminate();
    return 0;
}