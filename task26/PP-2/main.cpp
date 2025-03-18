#include <stdio.h>
#include <mpi.h>
#include <iostream>
//26
int main(int argc, char* argv[]) {
    int rank, size, new_rank, new_size;
    MPI_Comm even_comm;
    char message[11] = "";
    int color;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    color = (rank % 2 == 0) ? 1 : MPI_UNDEFINED;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &even_comm);

    if (color == 1) {
        MPI_Comm_rank(even_comm, &new_rank);
        MPI_Comm_size(even_comm, &new_size);

        if (new_rank == 0) {
            std::cout << "Enter a message (up to 10 characters): " << std::endl;
            std::cin >> message;
        }

        MPI_Bcast(message, 11, MPI_CHAR, 0, even_comm);
        printf("MPI_COMM_WORLD: %d from %d. New comm: %d from %d. Message = %s\n",
            rank, size, new_rank, new_size, message);
    }
    else {
        printf("MPI_COMM_WORLD: %d from %d. Not part of the new communicator.\n", rank, size);
    }

    if (color == 1) {
        MPI_Comm_free(&even_comm);
    }

    MPI_Finalize();
    return 0;
}
