#ifndef GLOBALS_SETTINGS_H
#define GLOBALS_SETTINGS_H

// includes
#include <stdatomic.h>

// settings
extern const int MAX_SCORE;
extern const int ROUND_LENGTH; // game round length in seconds

// globals
extern atomic_int total_score;
extern int game_time_seconds;

#endif
