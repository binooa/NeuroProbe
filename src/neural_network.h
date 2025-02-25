#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#define XAVIER_SCALE 1.0

typedef enum { CblasRowMajor, CblasColMajor } CBLAS_ORDER;
typedef enum { CblasNoTrans, CblasTrans, CblasConjTrans } CBLAS_TRANSPOSE;

void cblas_gemm(CBLAS_ORDER, CBLAS_TRANSPOSE, CBLAS_TRANSPOSE, int, int, int, double, const double*, int, const double*, int, double, double*, int);
void initializeWeights(double*, int, int);
void initializeHiddenNeurons(double*, int);
void initializeBias(double*, int);
void forwardPass(double*, double**, double**, double**, double**, int, int, int*, int);
void printMatrix(double*, int, int);

#endif
