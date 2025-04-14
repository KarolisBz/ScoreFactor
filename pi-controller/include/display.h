#ifndef display
#define display
#include <signal.h>

void start_game(int* totalScore, int argc, char **argv, volatile sig_atomic_t *interrupted);
void matrix_cleanup();
#endif