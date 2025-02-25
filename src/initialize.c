#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "neural_network.h"

void initializeWeights(double *weights, int rows, int cols) {
    srand((unsigned) time(NULL) * getpid());
    double scale = XAVIER_SCALE / (sqrt(rows) + sqrt(cols));    
    for (int i = 0; i < rows * cols; i++) {
        weights[i] = 1.0;
    }
}

void initializeHiddenNeurons(double *hneuron, int size) {
    srand((unsigned) time(NULL) * getpid());
    for (int i = 0; i < size; i++) {
        hneuron[i] = 1.0;
    }
}

void initializeBias(double *bias, int size) {
    for (int i = 0; i < size; i++) {
        bias[i] = 0.0;
    }
}
