#include <iostream>
#include <mpi.h>
#include <cstring>
//19
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
        int received_message;

        // wait for each other processes
        for (int i = 1; i < worldSize; ++i) {
            MPI_Recv(&received_message, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "receive message: '" << received_message << "'" << std::endl;
        }

        MPI_Finalize();
        return 0;
    }

    // send to master
    MPI_Send(&processRank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    MPI_Finalize();

    return 0;
}