#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <unistd.h>
#include <list>
#include <tuple>
#include <mpi.h>

#define BLOCK_SIZE 1024

class Node;
class HardDisk
{
    char cwd[PATH_MAX];
    int numberDisks;
    int diskSize;
    //Los sectores libres se guardan en "freeSectors1.dat".
    std::vector<int> sectors;
    std::vector<MPI_Comm*> comm;

public:
    HardDisk();
    ~HardDisk();

    //función que escribe todos los bloques de un fichero y su bloque índice en sectores libres del disco usando para cada uno de ellos writeBlock.
    bool writeFile(Node* fileNode);

    //readFile: función que lee con readBlock todos los bloques de un fichero mediante su bloque índice y lo reconstruye en el orden adecuado.
    void readFile(Node* fileNode);

    void format();

    bool checkIfFits();

    int getNumberOfDisks();

    void deleteNode(Node* fileNode);

    void overrideSectors();

private:
    void readSectors();
    void initializeSectors();
    int getHddInCharge(int block);

    void formatDisk();
    void formatSectors();
    bool checkIfExistsHDD();
    int checkHDDEmpy();
};
