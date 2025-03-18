#include <mpi.h>
#include <iostream>
//21
int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int send_message = rank;
    int recv_message;

    int next = (rank + 1) % world_size;
    int prev = (rank - 1 + world_size) % world_size;

    MPI_Status status;
    MPI_Send(&send_message, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    MPI_Recv(&recv_message, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);

    std::cout << "[" << rank << "] received message: " << recv_message << std::endl;

    MPI_Finalize();
    return 0;
}
