#include "neural_network.h"
#include <stdio.h>
#include <sys/time.h>

void cblas_gemm(CBLAS_ORDER Order, CBLAS_TRANSPOSE TransA,
                CBLAS_TRANSPOSE TransB, int M, int N,
                int K, double alpha, const double *A, int lda,
                const double *B, int ldb, double beta, double *C, int ldc) {
    int i, j, l;
    int istart, iend, jstart, jend, lstart, lend;
    double ctemp;
    static int gemm_call=0;

    // Suppress warnings for unused parameters
    (void) Order;
    (void) TransA;
    (void) TransB;
    gemm_call++;
    printf("\ngemm call without computation block : %d\t",gemm_call);

    struct timeval start, end;
    double elapsedTime;
    gettimeofday(&start, NULL);  // Start time
    
    /*
    printf("Matrix size : C[%dx%d]=A[%dx%d]xB[%dx%d]", M, N, M, K, K, N);

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
    } else {
        jstart = 0;
        jend = K;
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
    }*/
    gettimeofday(&end, NULL);  // End time
    // Compute time difference in seconds
    elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

    printf("\nExecution time of current gemm call: %f seconds\n", elapsedTime);
}
