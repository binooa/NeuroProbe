#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "neural_network.h"

int main() {
    int inputSize = 2;
    int numHiddenLayers = 10;
    int outputSize = 1;
    int numNeuronsperlayer = 1024;

    // Prompt user for input
    printf("Enter the number of hidden layers: ");
    scanf("%d", &numHiddenLayers);

    printf("Enter the number of neurons per hidden layer: ");
    scanf("%d", &numNeuronsperlayer);

    if (numHiddenLayers <= 0 || numNeuronsperlayer <= 0) {
        printf("Error: Number of layers and neurons must be greater than zero.\n");
        return 1;
    }

    int *hiddenSizes = (int*)malloc(numHiddenLayers * sizeof(int));
    if (!hiddenSizes) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < numHiddenLayers; i++) {
        hiddenSizes[i] = numNeuronsperlayer;
    }

    double *input = (double*)malloc(inputSize * sizeof(double));
    srand((unsigned) time(NULL) * getpid());
    for(int i = 0; i < inputSize; i++) {
        input[i] = 1.0;
    }

    double **hiddenNeurons = (double **)malloc(numHiddenLayers * sizeof(double *));
    double *output = (double *)malloc(outputSize * sizeof(double));
    double **weights = (double **)malloc((numHiddenLayers+1) * sizeof(double *));
    double **biases = (double **)malloc(numHiddenLayers * sizeof(double *));

    for (int i = 0; i < numHiddenLayers+1; i++) {
        int inputLayerSize = (i == 0) ? inputSize : hiddenSizes[i - 1];
        int outputLayerSize = (i < numHiddenLayers) ? hiddenSizes[i] : outputSize;
        weights[i] = (double *)malloc(inputLayerSize * outputLayerSize * sizeof(double));
        biases[i] = (double *)malloc(outputLayerSize * sizeof(double));
        hiddenNeurons[i] = (double *)malloc(outputLayerSize * sizeof(double));

        initializeWeights(weights[i], inputLayerSize, outputLayerSize);
        initializeHiddenNeurons(hiddenNeurons[i], outputLayerSize);
        initializeBias(biases[i], outputLayerSize);
    }

    forwardPass(input, hiddenNeurons, weights, biases, &output, inputSize, outputSize, hiddenSizes, numHiddenLayers);

    printf("\nDetails of Neural Network");
    printf("\nNumber of Input neurons : %d ", inputSize);
    printf("\nNumber of hidden layers : %d ", numHiddenLayers);
    printf("\nNumber of Output Neurons : %d ", outputSize);
    printf("\nNumber of hidden neurons in each layer: "); 

    for (int i = 0; i < numHiddenLayers; i++) {
        printf("[%d] = %d\t", i, hiddenSizes[i]);
    }
    printf("\n");

    free(input);
    free(hiddenSizes);
    free(weights);
    free(biases);
    free(hiddenNeurons);
    free(output);

    return 0;
}
