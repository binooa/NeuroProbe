#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "neural_network.h"

void initializeWeights(double *weights, int rows, int cols) {
    srand((unsigned) time(NULL) * getpid());
    double scale = XAVIER_SCALE / (sqrt(rows) + sqrt(cols));    
    for (int i = 0; i < rows * cols; i++) {
        weights[i] = scale;
    }
}

void initializeHiddenNeurons(double *hneuron, int size) {
    srand((unsigned) time(NULL) * getpid());
    double scale = 2.0 / (sqrt(size));   
    for (int i = 0; i < size; i++) {
        hneuron[i] = scale;
    }
}

void initializeBias(double *bias, int size) {
    for (int i = 0; i < size; i++) {
        bias[i] = 0.0;
    }
}
