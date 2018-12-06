/*
disco1.dat
Cada vez que se haga upload o cp se pone en el disco duro también.
Tener en cuenta borrar.
*/

#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <unistd.h>
#include <list>
#include <tuple>

#define NUMBER_DISKS 4
#define DISK_SIZE 320000
#define BLOCK_SIZE 1024

class Node;
class HardDisk
{
    char cwd[PATH_MAX];
    //Los sectores libres se guardan en "freeSectors1.dat".
    std::vector<std::list<int>> sectors;
    //std::vector<std::tuple<int, int>> sectors;

public:
    HardDisk();

    //función que escribe todos los bloques de un fichero y su bloque índice en sectores libres del disco usando para cada uno de ellos writeBlock.
    void writeFile(Node* fileNode);

    //readFile: función que lee con readBlock todos los bloques de un fichero mediante su bloque índice y lo reconstruye en el orden adecuado.
    void readFile(Node* fileNode);

private:
    void readSectors(int HDD);
    void initializeSectors();
    int getEmptyHdd();
    int getBlock(int HDD);
    void overrideSectors();

    //función que escribe un bloque de datos en formato binario en un sector libre del disco.
    void writeBlock(char* data, int HDD, int block);

    //función que lee un bloque de datos de un sector del disco duro.
    void readBlock();

    void formatDisk();
    void formatSectors(int size);
    bool checkIfExistsHDD();
    void format(int size);
    int checkHDDEmpy();
};


/*
/**
 * Los nodos tienen un array de indices que guardan los sectores del disco.
 *
 * Disco duro de Capacidad de 32 megas
 *
 * Sectores de 1Kb. Identificador único (posición). Tamaño de bloques de fichero 1 Kb también.
 *
 * El disco duro solo almacena bloques de datos.
 *
 * Los indices de los bloques se incorporan a los nodos.
 * /
*/
