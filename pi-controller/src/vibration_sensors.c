#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>
#include "vibration_sensors.h"
#include "globals_settings.h"

#define MAX_GPIO 64                              // reasonable limit for Raspberry Pi GPIO pins for sensors
static uint32_t last_callback_time = 0;          // To store the last callback timestamp (currently not per sensor because they are digital, too sensative)
static int sensor_score_per_hit[MAX_GPIO] = {0}; // zero-initialize all seensor posabilities

static void vibration_callback(int gpio, int level, uint32_t tick)
{
    // Check if enough time has passed since the last callback
    int score_reward = sensor_score_per_hit[gpio];

    // If the level is high (indicating vibration detection) and debounce time has passed
    // // 1 second debounce time
    if (level == PI_HIGH && (tick - last_callback_time) > 1000000 && game_time_seconds > 0)
    {
        // Update the score
        if (atomic_load(&total_score) + score_reward > MAX_SCORE)
        {
            atomic_store(&total_score, MAX_SCORE);
        }
        else
        {
            atomic_fetch_add(&total_score, score_reward);
        }

        // Update last callback time
        last_callback_time = tick;

        printf("Vibration detected!, Score: %d\n", atomic_load(&total_score));
    }
}

void vibration_init(int gpio_pin, int score_per_hit)
{
    if (gpio_pin >= MAX_GPIO)
    {
        fprintf(stderr, "GPIO %d is out of range\n", gpio_pin);
        return;
    }

    sensor_score_per_hit[gpio_pin] = score_per_hit;

    gpioSetMode(gpio_pin, PI_INPUT);
    gpioSetAlertFunc(gpio_pin, vibration_callback);
    printf("Vibration sensor initialized on GPIO %d\n", gpio_pin);
}

void vibration_stop()
{
    gpioSetAlertFunc(20, NULL); // Remove callback
}
