#ifndef DISPLAY_H
#define DISPLAY_H
#include <signal.h>

void setup_display(int argc, char **argv);
void display_game_frame();
void display_text(char* text);
void count_down_display(int seconds);
void matrix_cleanup();
#endif