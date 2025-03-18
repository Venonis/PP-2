#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    int processRank, worldSize;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

    std::cout << "I am " << processRank << " process from " << worldSize << " processes" << std::endl;

    MPI_Finalize();

    return 0;
}