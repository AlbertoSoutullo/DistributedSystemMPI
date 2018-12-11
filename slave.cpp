#include <iostream>
#include <fstream>
#include <mpi.h>


void writeBlock(int rank, MPI_Comm parent, MPI_Status status)
{
    int block = -1;
    int size = -1;
    char* binaryData = NULL;

    MPI_Recv(&block, 1, MPI_INT, 0, 0, parent, &status);
    MPI_Recv(&size, 1, MPI_INT, 0, 0, parent, &status);

    binaryData = (char*)malloc(sizeof(char)*size);

    MPI_Recv(binaryData, size, MPI_CHAR, 0, 0, parent, &status);

    std::string fileName = "disk" + std::to_string(rank) + ".dat";
    std::ofstream binaryFile;

    binaryFile.open(fileName, std::ios::out | std::ios::binary | std::ios::in);
    binaryFile.seekp(size*block);
    binaryFile.write((char*)binaryData, sizeof(char)*size);

    binaryFile.close();
}

void readBlock(int rank, MPI_Comm parent, MPI_Status status)
{
    int block = -1;
    int size = -1;
    char* binaryData = NULL;

    std::string fileName = "disk" + std::to_string(rank) + ".dat";
    std::ifstream disk;
    disk.open(fileName, std::ios::out | std::ios::binary | std::ios::in);

    MPI_Recv(&block, 1, MPI_INT, 0, 0, parent, &status);
    MPI_Recv(&size, 1, MPI_INT, 0, 0, parent, &status);
    //lee disco
    disk.seekg(block*size);
    disk.read((char*)binaryData, sizeof(char)*size);
    //manda data
    MPI_Send(&binaryData, size, MPI_CHAR, 0, 0, parent);
}

int recv_ID()
{
    int id = -1;
    MPI_Comm parent;
    MPI_Status status;
    MPI_Comm_get_parent(&parent);

    MPI_Recv(&id, 1, MPI_INT, 0, MPI_ANY_TAG, parent, &status);
    return id;
}


int main(int argc, char** argv)
{
    int rank = -1;
    int quit = 0;
    int option = -1;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    rank = recv_ID();

    MPI_Comm parent;
    MPI_Comm_get_parent(&parent);
    MPI_Status status;

    while(!quit)
    {
        MPI_Recv(&option, 1, MPI_INT, 0, MPI_ANY_TAG, parent, &status);
        if (option==10) //write
        {
            writeBlock(rank, parent, status);
        }
        else if (option == 11) //read
        {
            readBlock(rank, parent, status);
        }
        else if (option == 12) //quit
        {
            quit = 1;
        }
        else
        {
            std::cout << "Option not found" << std::endl;
        }
    }

    std::cout << "Closing slave " << std::to_string(rank) << "..." << std::endl;

}
