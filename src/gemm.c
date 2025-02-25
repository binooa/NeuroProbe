#include <stdio.h>
#include "neural_network.h"

void cblas_gemm(const enum CBLAS_ORDER Order, const enum CBLAS_TRANSPOSE TransA,
                const enum CBLAS_TRANSPOSE TransB, const int M, const int N,
                const int K, const double alpha, const double *A, const int lda,
                const double *B, const int ldb, const double beta, double *C,
                const int ldc) {
    int i, j, l;
    int istart, iend, jstart, jend, lstart, lend;
    double ctemp;


    printf("\ngemm call NN:\t");
    printf("Matrix size : C[%dx%d]=A[%dx%d]xB[%dx%d]", M, N, M, K, K, N);    

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

