/*
disco1.dat
Cada vez que se haga upload o cp se pone en el disco duro también.
Tener en cuenta borrar.

*/

class HardDisk
{

    //Los sectores libres se guardan en "freeSectors1.dat".

public:
    HardDisk();

    //función que escribe un bloque de datos en formato binario en un sector libre del disco.
    void writeBlock();

    //función que lee un bloque de datos de un sector del disco duro.
    void readBlock();

    //función que escribe todos los bloques de un fichero y su bloque índice en sectores libres del disco usando para cada uno de ellos writeBlock.
    void writeFile();

    //readFile: función que lee con readBlock todos los bloques de un fichero mediante su bloque índice y lo reconstruye en el orden adecuado.
    void readFile();

};



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
