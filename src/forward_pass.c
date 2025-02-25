#include "neural_network.h"

void forwardPass(double *input, double **hNeurons, double **weights, double **biases, double **output, int inneuronSize, int outneuronSize,
                 int *layerSizes, int numLayers) {
    double *layerInput = input;
    double *layerOutput;
    int inputSize;
    int outputSize;
    double *layerWeights;
    double *layerBiases;

    for (int layer = 0; layer < numLayers+1; layer++) {
        inputSize = (layer == 0) ? inneuronSize : layerSizes[layer-1];
        outputSize = (layer < numLayers) ? layerSizes[layer] : outneuronSize;
        layerOutput = hNeurons[layer];
        layerWeights = weights[layer];
        layerBiases = biases[layer];

        cblas_gemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 1, outputSize, inputSize, 1.0, layerInput, 1, layerWeights, inputSize, 0.0, layerOutput, 1);

        for (int i = 0; i < outputSize; i++) {
            layerOutput[i] += layerBiases[i];
        }

        layerInput = layerOutput;
    }
    *output = layerOutput;
}

