#include <stdio.h>
#include <stdlib.h>
#define M 100
#define N 200
#define O 300

typedef spinlock{
    int status;
}spinlock_t;

void aquire_lock(spinlock *lock){
    while (Fetch_and_Increment(lock.status));
}

void release_lock(spinlock *lock){
    lock.status = 0;
}


int main() {
    int A[M][N];
    int B[N][O];
    int C[O][M];
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            *A[i * N + j] = rand()%10;
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < O; ++j) {
            *B[i * O + j] = rand()%10;
        }
    }
#pragma omp parallel for shared(A, B, C) privated(i ,j ,k)
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < O; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return 0;
}

