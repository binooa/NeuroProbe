// gcc neroprobe_lite_model_with_likwid_marker.c -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC -pg -ggdb -march='skylake' -lm
// sudo likwid-perfctr -C S0:0 -g MEM_DP ./a.out
// sudo likwid-memsweeper
#include <stdio.h>
#include <stdlib.h>
//#include <cblas.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#define XAVIER_SCALE 1.0
enum CBLAS_ORDER {
    CblasRowMajor,
    CblasColMajor
};

enum CBLAS_TRANSPOSE {
    CblasNoTrans,
    CblasTrans,
    CblasConjTrans
};


void cblas_gemm(const enum CBLAS_ORDER Order, const enum CBLAS_TRANSPOSE TransA,
                const enum CBLAS_TRANSPOSE TransB, const int M, const int N,
                const int K, const double alpha, const double *A, const int lda,
                const double *B, const int ldb, const double beta, double *C,
                const int ldc) {
    int i, j, l;
    int istart, iend, jstart, jend, lstart, lend;
    double ctemp;

    printf("\ngemm call NN:\t");
    printf("Matrix size : C[%dx%d]=A[%dx%d]xB[%dx%d]",M,N,M,K,K,N);    

    
    if (M <= 0 || N <= 0 || ((alpha == 0.0 || K == 0) && beta == 1.0))
        return;

    if (alpha == 0.0) {
        if (beta == 0.0) {
            for (j = 0; j < N; ++j) {
                for (i = 0; i < M; ++i) {
                    C[i + j * ldc] = 0.0;
                }
            }
        } else {
            for (j = 0; j < N; ++j) {
                for (i = 0; i < M; ++i) {
                    C[i + j * ldc] *= beta;
                }
            }
        }
        return;
    }

    if (TransA == CblasNoTrans) {
        istart = 0;
        iend = M;
        lstart = 0;
        lend = K;
    } else {
        istart = 0;
        iend = K;
        lstart = 0;
        lend = M;
    }

    if (TransB == CblasNoTrans) {
        jstart = 0;
        jend = N;
        l = ldb;
    } else {
        jstart = 0;
        jend = K;
        l = ldc;
    }

    if (beta == 0.0) {
        for (j = jstart; j < jend; ++j) {
            for (i = istart; i < iend; ++i) {
                C[i + j * ldc] = 0.0;
            }
        }
    } else if (beta != 1.0) {
        for (j = jstart; j < jend; ++j) {
            for (i = istart; i < iend; ++i) {
                C[i + j * ldc] *= beta;
            }
        }
    }

    if (alpha == 1.0) {
        for (l = lstart; l < lend; ++l) {
            for (j = jstart; j < jend; ++j) {
                ctemp = B[l + j * ldb];
                for (i = istart; i < iend; ++i) {
                    C[i + j * ldc] += A[i + l * lda] * ctemp;
                }
            }
        }
    } else {
        for (l = lstart; l < lend; ++l) {
            for (j = jstart; j < jend; ++j) {
                ctemp = alpha * B[l + j * ldb];
                for (i = istart; i < iend; ++i) {
                    C[i + j * ldc] += A[i + l * lda] * ctemp;
                }
            }
        }
    }
}







void initializeWeights(double *weights, int rows, int cols) {
    // Initialize weights with random values between -1 and 1 using Xavier Initialization
	//srand(time(NULL));
    srand((unsigned) time(NULL) * getpid());
    double scale = XAVIER_SCALE / (sqrt(rows) + sqrt(cols));    
    for (int i = 0; i < rows * cols; i++) {
        //weights[i] = (2.0 * rand() / RAND_MAX) - 1.0;
        weights[i] = 1.0;
        //weights[i] = scale * (2.0 * rand() / RAND_MAX - 1.0);
        //weights[i] = scale * (2.0 * ((rand() % 63) - 25) / RAND_MAX - 1.0);
    }
}


void initializeHiddenNeurons(double *hneuron, int size) {
    // Initialize weights with random values between -1 and 1 using Xavier Initialization
	//srand(time(NULL));
    srand((unsigned) time(NULL) * getpid());
    int rows=1;
    int cols=size;
    double scale = XAVIER_SCALE / (sqrt(rows) + sqrt(cols));  
    for (int i = 0; i < size; i++) {
        hneuron[i] = 1.0;
        //hneuron[i] = (scale * (2.0 * rand() / RAND_MAX - 1.0))+0.2;
        //hneuron[i] = scale * (2.0 * ((rand() % 63) - 25) / RAND_MAX - 1.0);
    }
}

void initializeBias(double *bias, int size) {
    // Initialize bias with zeros
    for (int i = 0; i < size; i++) {
        bias[i] = 0.0;
    }
}

void printMatrix(double *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.2f ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

void forwardPass(double *input, double **hNeurons, double **weights, double **biases, double **output, int inneuronSize,int outneuronSize,
                 int *layerSizes, int numLayers) {
    double *layerInput = input;
    //double *layerOutput = output;
    double *layerOutput;
    int inputSize;
    int outputSize;
    double *layerWeights;
    double *layerBiases;

    for (int layer = 0; layer < numLayers+1; layer++) {

        inputSize = (layer == 0) ? inneuronSize : layerSizes[layer-1];
        outputSize = (layer < numLayers) ? layerSizes[layer] : outneuronSize;

        layerOutput=hNeurons[layer];
        
        layerWeights = weights[layer];
        layerBiases = biases[layer];
        //printf("\n__________________________________________________________________________\n");
        //printf("Layer : %d\n",layer);
        //printf("Input Layer Size, Output Layer : %d,%d\n",inputSize,outputSize); 
        //printf("\nGEMM Matrices");               
        //printf("\n Matrix A\n");
        //printMatrix(layerInput, 1, inputSize);
        //printf("\n Matrix B\n");
        //printMatrix(layerWeights, inputSize, outputSize);                   
        // Compute layer output = layerInput * layerWeights + layerBiases
        //int m   is ROW MATRIX, hence 1 // Number of rows in A and C
        //int n   outputSize // Number of columns in B and C
        //int k   inputSize // Number of columns in A and rows in B
        cblas_gemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,   1,        outputSize,  inputSize, 1.0, layerInput, 1, layerWeights, inputSize, 0.0, layerOutput, 1);
        //cblas_gemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1.0, A, m, B, k, 0.0, C, m);
        //printf("\n Matrix C\n");        
        //printMatrix(layerOutput, 1, outputSize);
        for (int i = 0; i < outputSize; i++) {
            layerOutput[i] += layerBiases[i];
        }

        // Set layerInput and update inputSize for the next layer
        layerInput = layerOutput;
        //inputSize = outputSize;
    }
    *output=layerOutput;
 
}

int main() {
    // Define network architecture
    // Static Network Inizialization 
    //------------------------------------
    //int inputSize = 2; //2
    //int hiddenSizes[] = {4,3,2}; //{4,3,2};
    //int outputSize = 1; //1
    //int numLayers = sizeof(hiddenSizes) / sizeof(hiddenSizes[0]);
    //------------------------------------

    //Dynamic Network Inizialization 
    //------------------------------------
    // Input by User - Model Configuration
    int count=0; //loop counter 
    int Nval=10; // loop iteration maximum value
    int inputSize=2;
    int numHiddenLayers=10;
    int outputSize = 1;
    int numNeuronsperlayer=1024;
//while(count<Nval)
//{
//    printf("\n----------------------------------\nIteration : %d",count);
    //----------------------------
    srand(time(NULL));  // Initialize random number generator with current time
    //int inputSize = (rand() % (10-1))+3;  // Random size between 1 and 10 //2
    //int numHiddenLayers = (rand() % (100-1))+10;  // Random size between 1 and 10
    int* hiddenSizes = (int*)malloc(numHiddenLayers * sizeof(int));
    // Assign random values
    for (int i = 0; i < numHiddenLayers; i++) {
        //hiddenSizes[i] = (rand() % (100-1))+12;  // Random value between 0 and 99
        hiddenSizes[i] = numNeuronsperlayer;  
    }
    // Printing the values
    //for (int i = 0; i < numHiddenLayers; i++) {
    //    printf("hiddenSizes[%d] = %d\n", i, hiddenSizes[i]);
    //}

    //int outputSize = 1; //1
    int numLayers =numHiddenLayers;
    //int numLayers = sizeof(hiddenSizes) / sizeof(hiddenSizes[0]);
    //------------------------------------

    //printf("\nNumber of Layers : %d",numLayers);

    // Define input neurons
    //double input[inputSize];
    double *input = (double*)malloc(inputSize * sizeof(double));
    //srand(time(NULL));
    srand((unsigned) time(NULL) * getpid());
    for(int i=0;i<inputSize;i++)
    {
        //input[i] = (2.0 * rand() / RAND_MAX - 1.0);
        input[i] =1.0;
    }
    //printf("\nInput Matrix\n");
    //printMatrix(input, 1, inputSize);
    //Allocate memory for hidden neurons
    double **hiddenNeurons = (double **)malloc(numLayers * sizeof(double *));

    // Allocate memory for output
    double *output = (double *)malloc(outputSize * sizeof(double));

    // Allocate memory for weights and biases
    double **weights = (double **)malloc((numLayers+1) * sizeof(double *));
    double **biases = (double **)malloc(numLayers * sizeof(double *));
    for (int i = 0; i < numLayers+1; i++) {
        int inputLayerSize = (i == 0) ? inputSize : hiddenSizes[i - 1];
        int outputLayerSize = (i < numLayers) ? hiddenSizes[i] : outputSize;
        weights[i] = (double *)malloc(inputLayerSize * outputLayerSize * sizeof(double));
        biases[i] = (double *)malloc(outputLayerSize * sizeof(double));
        hiddenNeurons[i]=(double *)malloc(outputLayerSize * sizeof(double));

        initializeWeights(weights[i], inputLayerSize, outputLayerSize);
        //printf("\nWeight Matrix[%d]\n",i);
        //printMatrix(weights[i], inputLayerSize, outputLayerSize);

        initializeHiddenNeurons(hiddenNeurons[i], outputLayerSize);
        //printf("\nHidden Neurons Matrix[%d]\n",i);
        //printMatrix(hiddenNeurons[i], 1, outputLayerSize);

        initializeBias(biases[i], outputLayerSize);
    }



    // Perform forward pass
    forwardPass(input, hiddenNeurons,weights, biases, &output, inputSize, outputSize, hiddenSizes, numLayers);

    // Print results
    printf("\nDetails of Neural Network");
    printf("\nNumber of Input neurons : %d ",inputSize );
    printf("\nNumber of hidden layers : %d ",numLayers );
    printf("\nNumber of Output Neurons : %d ",outputSize );    
    printf("\nNumber of hidden neurons in each layers : "); 
    // Printing the values
    for (int i = 0; i < numHiddenLayers; i++) {
        printf(" [%d] = %d\t", i, hiddenSizes[i]);
    }
    printf("\nInput Neurons: ");
    for(int i=0;i<inputSize;i++)
    {
        printf("%f\t", input[i]);
    }
    printf("\nOutput Value: ");    
    for(int i=0;i<outputSize;i++)
    {
        printf("\nOutput: %f\n", output[i]);
    }    
    
    

    // Free allocated memory
    /*for (int i = 0; i < numLayers+1; i++) {
        free(weights[i]);
        free(biases[i]);
         free(hiddenNeurons[i]);
    }*/
    free(input);
    free(hiddenSizes);
    free(weights);
    free(biases);
    free(hiddenNeurons);
    free(output);

//    count=count+1;
//    inputSize=inputSize+2;
//    numHiddenLayers=numHiddenLayers+1;
//    outputSize = outputSize+1;
//    numNeuronsperlayer=numNeuronsperlayer+10;

//    int test;
//    scanf("%d",&test);
//}
    return 0;
}
