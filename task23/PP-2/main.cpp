#include <mpi.h>
#include <iostream>
//23
 
int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    const int MAX_LENGTH = 100;
    char str[MAX_LENGTH];
    int string_size = 0;

    if (rank == 0) {
        std::cin >> string_size;
        std::cin >> str;
    }

    MPI_Bcast(&string_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(str, string_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    int local_count[256] = { 0 };
    for (int i = rank; i < string_size; i += world_size) {
        local_count[(unsigned char)str[i]]++;
    }

    int global_count[256] = { 0 };
    MPI_Reduce(local_count, global_count, 256, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < 256; i++) {
            if (global_count[i] > 0) {
                std::cout << "'" << static_cast<char>(i) << "' = " << global_count[i] << std::endl;
            }
        }
    }

    MPI_Finalize();
    return 0;
}
