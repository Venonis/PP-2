#include <mpi.h>
#include <iostream>
#include <vector>
//22
int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_message = rank;
    int recv_message;

    int *received_messages = new int[size];

    MPI_Status status;

    for (int i = 0; i < size; i++) {
        if (i != rank) {
            MPI_Send(&send_message, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

            MPI_Recv(&recv_message, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            received_messages[i] = recv_message;
        }
    }

    for (int i = 0; i < size; i++) {
        if (i != rank) {
            std::cout << "[" << rank << "]: received message '" << received_messages[i] << "' from " << i << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
