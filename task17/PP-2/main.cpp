#include <iostream>
#include <mpi.h>
#include <cstring>
//17
int main(int argc, char** argv) {
    int processRank, worldSize;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

    if (worldSize < 2) {
        std::cout << "Need at least 2 processes in world" << std::endl;
        MPI_Finalize();
        return 1;
    }

    if (processRank == 0) {
        const char* msg = "45";
        // strlen(msg) + 1 because of terminating \0
        MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Finalize();
        return 0;
    }

    char received_message[100];
    MPI_Recv(received_message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "receive message: '" << received_message << "'" << std::endl;

    MPI_Finalize();

    return 0;
}