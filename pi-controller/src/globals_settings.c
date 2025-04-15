// includes
#include <stdbool.h>
#include <stdatomic.h>
#include "globals_settings.h"

// settings
const int MAX_SCORE = 1000;
const int ROUND_LENGTH = 120; // game round length in seconds

// globals
atomic_int total_score = 0; // future proof via atomic int
int game_time_seconds = ROUND_LENGTH;