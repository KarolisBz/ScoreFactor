#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>
#include "vibration_sensors.h"

static uint32_t last_callback_time = 0;  // To store the last callback timestamp

static void vibration_callback(int gpio, int level, uint32_t tick) {
    // Check if enough time has passed since the last callback
    uint32_t current_time = tick;

    // If the level is high (indicating vibration detection) and debounce time has passed
    if (level == PI_HIGH && (current_time - last_callback_time) > 1000000) { // 1 second debounce time
        printf("Vibration detected!\n");

        // Update last callback time
        last_callback_time = current_time;
    }
}

void vibration_init(int gpio_pin) {
    gpioSetMode(gpio_pin, PI_INPUT);
    gpioSetAlertFunc(gpio_pin, vibration_callback);
    printf("Vibration sensor initialized on GPIO %d\n", gpio_pin);
}

void vibration_stop() {
    gpioSetAlertFunc(20, NULL);  // Remove callback
}
