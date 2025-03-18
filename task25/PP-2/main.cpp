#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//25
void initialize_matrix(int n, int* matrix) {
    for (int i = 0; i < n * n; i++) {
        scanf("%d", &matrix[i]);
        //matrix[i] = rand() % 10;
    }
}

void print_matrix(int n, int* matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i * n + j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    int rank, size, n;
    int* A = nullptr, * B = nullptr, * C = nullptr;
    int* local_A = nullptr, * local_C = nullptr;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    n = size;

    if (rank == 0) {
        printf("The size of the matrix (n x n): %d", n);
        //scanf("%d", &n);

        if (n % size != 0) {
            printf("Matrix size must be divisible by the number of processes.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    B = (int*)malloc(n * n * sizeof(int));
    A = (int*)malloc(n * n * sizeof(int));


    if (rank == 0) {
        C = (int*)malloc(n * n * sizeof(int));

        initialize_matrix(n, A);
        initialize_matrix(n, B);

        printf("Matrix A:\n");
        print_matrix(n, A);
        printf("Matrix B:\n");
        print_matrix(n, B);
    }

    int rows_per_process = n / size;

    local_A = (int*)malloc(rows_per_process * n * sizeof(int));
    local_C = (int*)malloc(rows_per_process * n * sizeof(int));

    MPI_Scatter(A, rows_per_process * n, MPI_INT, local_A, rows_per_process * n, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Bcast(B, n * n, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < rows_per_process; i++) {
        for (int j = 0; j < n; j++) {
            local_C[i * n + j] = 0.0;
            for (int k = 0; k < n; k++) {
                local_C[i * n + j] += local_A[i * n + k] * B[k * n + j];
            }
        }
    }

    std::cout << "process " << rank << " computed local_C" << std::endl;

    // —бор матрицы C на процессе 0
    MPI_Gather(local_C, rows_per_process * n, MPI_INT, C, rows_per_process * n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Matrix C (Result):\n");
        print_matrix(n, C);
    }

    free(local_A);
    free(local_C);

    free(A);
    free(B);
    free(C);

    MPI_Finalize();
}
