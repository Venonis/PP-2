#include <iostream>
#include <mpi.h>
#include <cstring>
//18
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

    int received_message;

    if (processRank == 0) {
        MPI_Send(&processRank, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&received_message, 1, MPI_INT, worldSize - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "[" << processRank << "] receive message: '" << received_message << "'" << std::endl;
        MPI_Finalize();
        return 0;
    }

    MPI_Recv(&received_message, 1, MPI_INT, processRank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "[" << processRank << "] receive message: '" << received_message << "'" << std::endl;
    MPI_Send(&processRank, 1, MPI_INT, processRank + 1 < worldSize ? processRank + 1 : 0, 0, MPI_COMM_WORLD);

    MPI_Finalize();

    return 0;
}