#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#define XAVIER_SCALE 1.0

// Define enums outside function declarations
typedef enum {
    CblasRowMajor,
    CblasColMajor
} CBLAS_ORDER;

typedef enum {
    CblasNoTrans,
    CblasTrans,
    CblasConjTrans
} CBLAS_TRANSPOSE;

// Declare function prototypes
void cblas_gemm(CBLAS_ORDER Order, CBLAS_TRANSPOSE TransA,
                CBLAS_TRANSPOSE TransB, int M, int N, int K,
                double alpha, const double *A, int lda,
                const double *B, int ldb, double beta, double *C, int ldc);

void initializeWeights(double*, int, int);
void initializeHiddenNeurons(double*, int);
void initializeBias(double*, int);
void forwardPass(double*, double**, double**, double**, double**, int, int, int*, int);
void printMatrix(double*, int, int);

#endif
