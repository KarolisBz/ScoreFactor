#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>
#include "vibration_sensors.h"


#define MAX_GPIO 64 // reasonable limit for Raspberry Pi GPIO pins for sensors

typedef struct {
    int* total_score;
    int score_per_hit;
    uint32_t last_callback_time; // To store the last callback timestamp
} SensorContext;

static SensorContext sensor_contexts[MAX_GPIO] = {0};  // zero-initialize all seensor posabilities

static void vibration_callback(int gpio, int level, uint32_t tick) {
    // Check if enough time has passed since the last callback
    SensorContext* sc = &sensor_contexts[gpio];

    // If the level is high (indicating vibration detection) and debounce time has passed
    if (level == PI_HIGH && (tick - sc->last_callback_time) > 1000000) { // 1 second debounce time
        // Update the score
        *(sc->total_score) += sc->score_per_hit;
        // Update last callback time
        sc->last_callback_time = tick;

        printf("Vibration detected!, Score: %d\n", *sc->total_score) ;
    }
}

void vibration_init(int gpio_pin, int* total_score, int score_per_hit) {
    if (gpio_pin >= MAX_GPIO) {
        fprintf(stderr, "GPIO %d is out of range\n", gpio_pin);
        return;
    }

    sensor_contexts[gpio_pin].total_score = total_score;
    sensor_contexts[gpio_pin].score_per_hit = score_per_hit;
    sensor_contexts[gpio_pin].last_callback_time = 0;

    gpioSetMode(gpio_pin, PI_INPUT);
    gpioSetAlertFunc(gpio_pin, vibration_callback);
    printf("Vibration sensor initialized on GPIO %d\n", gpio_pin);
}

void vibration_stop() {
    gpioSetAlertFunc(20, NULL);  // Remove callback
}
