#include <iostream>
#include <mpi.h>
//16
int main(int argc, char** argv) {
    int processRank, worldSize;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

    if (processRank == 0)
    {
        std::cout << worldSize << " processes" << std::endl;
        MPI_Finalize();
        return 0;
    }
    std::cout << "I am " << processRank << " process: ";

    if (processRank % 2)
        std::cout << "FIRST";
    else
        std::cout << "SECOND";

    std::cout << std::endl;

    MPI_Finalize();

    return 0;
}