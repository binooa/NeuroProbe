#include <stdio.h>
#include "neural_network.h"

void cblas_gemm(const enum CBLAS_ORDER Order, const enum CBLAS_TRANSPOSE TransA,
                const enum CBLAS_TRANSPOSE TransB, const int M, const int N,
                const int K, const double alpha, const double *A, const int lda,
                const double *B, const int ldb, const double beta, double *C,
                const int ldc) {
    int i, j, l;
    double ctemp;

    printf("\ngemm call NN:\t");
    printf("Matrix size : C[%dx%d]=A[%dx%d]xB[%dx%d]", M, N, M, K, K, N);    

    if (alpha == 1.0) {
        for (l = 0; l < K; ++l) {
            for (j = 0; j < N; ++j) {
                ctemp = B[l + j * ldb];
                for (i = 0; i < M; ++i) {
                    C[i + j * ldc] += A[i + l * lda] * ctemp;
                }
            }
        }
    } else {
        for (l = 0; l < K; ++l) {
            for (j = 0; j < N; ++j) {
                ctemp = alpha * B[l + j * ldb];
                for (i = 0; i < M; ++i) {
                    C[i + j * ldc] += A[i + l * lda] * ctemp;
                }
            }
        }
    }
}
