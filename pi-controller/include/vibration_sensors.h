#ifndef VIBRATION_SENSORS_H
#define VIBRATION_SENSORS_H

void vibration_init(int gpio_pin, int* total_score, int score_per_hit);
void vibration_stop();

#endif
