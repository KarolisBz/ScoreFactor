#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "display.h"

#include "led-matrix.h"

struct rgb_matrix *matrix;
struct rgb_canvas *canvas;

// Function to display score on the LED matrix
void display_score(int* totalScore) {
    while (1) {
        sleep(1);
    }
}

void matrixCleanup() {
}
