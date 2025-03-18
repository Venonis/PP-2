#include <mpi.h>
#include <cstring>
#include <iostream>
//20
int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int TAG = 0;
    MPI_Request request;
    MPI_Status status;

    if (rank == 0) {
        const char message[] = "Hello, MPI!";
        MPI_Isend(message, strlen(message) + 1, MPI_CHAR, 1, TAG, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);

    }
    else if (rank == 1) {
        char received_message[100];
        MPI_Irecv(received_message, 100, MPI_CHAR, 0, TAG, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        std::cout << "receive message: '" << received_message << "'" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
