#include "HardDisk.h"
#include "Node.h"

void HardDisk::readSectors(int HDD)
{
    std::string fileName = "freeSectors" + std::to_string(HDD) + ".dat";
    std::ifstream binaryFile;
    int size = 0;
    int sector = -1;

    binaryFile.open(fileName, std::ios::in | std::ios::binary);
    binaryFile.seekg(0, std::ios::end);
    size = (int)binaryFile.tellg();
    binaryFile.seekg(0, std::ios::beg);

    while(binaryFile.tellg() < size)
    {
        binaryFile.read((char*)&sector, sizeof(sector));
        this->sectors.push_back(sector);
    }
    binaryFile.close();
}

void HardDisk::initializeSectors()
{
    for(int i = 0; i < this->numberDisks; i++)
    {
        readSectors(i);
    }
}

HardDisk::HardDisk()
{
    getcwd(this->cwd, sizeof(cwd));
    if (FILE *file = fopen("disk0.dat", "r"))
    {
        std::cout << "Loading Hard Drives..." << std::endl;
    }
    else
    {
        format();
    }
    initializeSectors();
    this->numberDisks = 4;
    //Create slaves
    for (int i = 0; i < this->numberDisks; i++)
    {
        std::cout << "FOR" << std::endl;
        MPI_Comm* communicator = new MPI_Comm[1];
        MPI_Comm_spawn("slave", MPI_ARGV_NULL, 1, MPI_INFO_NULL, 0, MPI_COMM_SELF, communicator, MPI_ERRCODES_IGNORE);
        this->comm.push_back(communicator);
        int newID = this->comm.size();
        MPI_Send(&newID, 1, MPI_INT, 0, 0, *communicator);
        std::cout << "ID SENDED" << std::endl;
    }
}

int HardDisk::getEmptyHdd(int block)
{
    int result = block % this->numberDisks;

    return result;
}


void HardDisk::overrideSectors()
{
    std::ofstream sectorsFile;
    std::string string_cwd = std::string(this->cwd);
    string_cwd += "/freeSectors.dat";

    for (std::vector<int>::iterator it = this->sectors.begin(); it != this->sectors.end(); it++)
    {
        int number = *it;
        sectorsFile.write((char*)&number, sizeof(int));
    }
    sectorsFile.close();
}

/*Subir*/
void HardDisk::writeFile(Node* fileNode)
{
    int restSize = -1;
    bool flagRest = false;
    std::string string_cwd = std::string(this->cwd);

    //dividir el archivo en bloques (restante a cero)
    off_t fileSize = fileNode->getByteSize();
    const off_t blockSize = BLOCK_SIZE;
    int numberOfBlocks = fileSize / blockSize;

    if ((fileSize % blockSize) != 0)
    {
        restSize = fileSize - (numberOfBlocks*BLOCK_SIZE);
        flagRest = true;
    }

    int pos = 0; //Last position of reader

    //en un for, por cada bloque leer esa parte, mirar que disco está vacio, escribir
    //se puede enviar el array de blocks y el array de datos
    for (int i = 0; i < numberOfBlocks; i++)
    {
        std::ifstream fs;
        char* binaryData = (char*)malloc(sizeof(char)*BLOCK_SIZE);
        //Open File and Check size
        fs.open(string_cwd + "/" + fileNode->getName(), std::ios::in | std::ios::binary);
        if (!fs.is_open()) std::cout << "Cannot open file." << std::endl;
        fs.seekg(pos, fs.beg);
        fs.read((char*)binaryData, sizeof(char)*BLOCK_SIZE);
        pos += BLOCK_SIZE;

        int HDD = getEmptyHdd(i);
        int block = i / this->numberDisks;
        int option = 10;
        int size = sizeof(char)*BLOCK_SIZE;
        MPI_Send(&option, 1, MPI_INT, 0, 0, *this->comm[HDD]);
        MPI_Send(&block, 1, MPI_INT, 0, 0, *this->comm[HDD]);
        MPI_Send(&size, 1, MPI_INT, 0, 0, *this->comm[HDD]);
        MPI_Send(binaryData, size, MPI_CHAR, 0, 0, *this->comm[HDD]);

        (*fileNode).setBlock(block);

        fs.close();
        //free

        //out os space?
    }
    if(flagRest)
    {
        std::ifstream fs;
        char* binaryData = (char*)malloc(sizeof(char)*BLOCK_SIZE);
        //Open File and Check size
        fs.open(string_cwd + "/" + fileNode->getName(), std::ios::in | std::ios::binary);
        if (!fs.is_open()) std::cout << "Cannot open file." << std::endl;
        fs.seekg(pos, fs.beg);
        fs.read((char*)binaryData, sizeof(char)*BLOCK_SIZE);
        pos = fs.tellg();
        memset(binaryData+restSize, 0, (BLOCK_SIZE-restSize)*sizeof(char));

        int HDD = getEmptyHdd(numberOfBlocks);
        int block = numberOfBlocks / this->numberDisks;
        int option = 10;
        int size = sizeof(char)*restSize;
        MPI_Send(&option, 1, MPI_INT, 0, 0, *this->comm[HDD]);
        MPI_Send(&block, 1, MPI_INT, 0, 0, *this->comm[HDD]);
        MPI_Send(&size, 1, MPI_INT, 0, 0, *this->comm[HDD]);
        MPI_Send(binaryData, size, MPI_CHAR, 0, 0, *this->comm[HDD]);

        (*fileNode).setBlock(block);

        fs.close();
    }

    //Actualizar el fichero de sectores
    (*fileNode).setNumBlocksOccupied();
    overrideSectors();

}


void HardDisk::readFile(Node* fileNode)
{
    MPI_Status status;
    std::ofstream file;
    std::ifstream disk;

    std::string string_cwd = std::string(this->cwd);
    string_cwd += "/";
    string_cwd += fileNode->getName();
    file.open(string_cwd, std::ios::out | std::ios::binary | std::ios::trunc);

    string_cwd = std::string(this->cwd);

    std::vector<int>* blocks = fileNode->getBlockLocations();

    for (int i = 0; i < fileNode->getNumBlocksOccupied()-1; i++)
    {
        int hdd = i% this->numberDisks;
        //saco bloque
        int block = blocks->at(i);
        int size = BLOCK_SIZE;
        char* binaryData = NULL;

        //leo datos
        int option = 11;
        disk.open(string_cwd + "/disk" + std::to_string(hdd) + ".dat", std::ios::in | std::ios::binary);
        MPI_Send(&option, 1, MPI_INT, 0, 0, *this->comm[hdd]);
        MPI_Send(&block, 1, MPI_INT, 0, 0, *this->comm[hdd]);
        MPI_Send(&size, 1, MPI_INT, 0, 0, *this->comm[hdd]);

        binaryData = (char*)malloc(sizeof(char)*size);

        MPI_Recv(binaryData, size, MPI_CHAR, 0, 0, *this->comm[hdd], &status);

        file.seekp(BLOCK_SIZE*i);
        file.write((char*)binaryData, sizeof(char)*BLOCK_SIZE);
        //free
        disk.close();
    }

    int hdd = (fileNode->getNumBlocksOccupied()-1) % this->numberDisks;
    //saco bloque
    int block = blocks->at(fileNode->getNumBlocksOccupied()-1);
    int size = fileNode->getByteSize() - ((fileNode->getNumBlocksOccupied()-1)*BLOCK_SIZE);;
    char* binaryData = NULL;

    //leo datos
    disk.open(string_cwd + "/disk" + std::to_string(hdd) + ".dat", std::ios::in | std::ios::binary);
    int option = 11;
    MPI_Send(&option, 1, MPI_INT, 0, 0, *this->comm[hdd]);
    MPI_Send(&block, 1, MPI_INT, 0, 0, *this->comm[hdd]);
    MPI_Send(&size, 1, MPI_INT, 0, 0, *this->comm[hdd]);

    binaryData = (char*)malloc(sizeof(char)*size);

    MPI_Recv(binaryData, size, MPI_CHAR, 0, 0, *this->comm[hdd], &status);

    file.seekp(BLOCK_SIZE*(fileNode->getNumBlocksOccupied() - 1));
    file.write((char*)binaryData, sizeof(char)*size);
    //free
    disk.close();
    file.close();
}


void HardDisk::formatDisk()
{
    std::ofstream diskFile;
    for (int i = 0; i < this->numberDisks; i++)
    {
        std::string string_cwd = std::string(this->cwd);
        string_cwd += "/disk";
        string_cwd += std::to_string(i);
        string_cwd += ".dat";
        diskFile.open(string_cwd, std::ios::in | std::ios::binary | std::ios::trunc);
        diskFile.close();
    }
}

void HardDisk::formatSectors()
{
    std::ofstream sectorsFile;

    std::string string_cwd = std::string(this->cwd);
    string_cwd += "/freeSectors.dat";
    sectorsFile.open(string_cwd, std::ios::in | std::ios::binary | std::ios::trunc);
    for (int i = 0; i < this->diskSize; i++)
    {
        sectorsFile.write((char*)&i, sizeof(i));
    }
    sectorsFile.close();
}

bool HardDisk::checkIfExistsHDD()
{
    for(int i = 0; i < this->numberDisks; i++)
    {
        std::string string_cwd = std::string(this->cwd);
        string_cwd += "/disk";
        string_cwd += std::to_string(i);
        string_cwd += ".dat";
        if (FILE *file = fopen("disk0.dat", "r"))
        {
            std::cout << "Loading Hard Drive " << i << std::endl;
        }
        else return false;
    }
    return true;
}


void HardDisk::format()
{
    std::cout << "Creating Hard Drives..." << std::endl;
    std::cout << "How many Drives do you want?" << std::endl;
    std::cin >> this->numberDisks;
    std::cout << "Select total size: " << std::endl;
    std::cin >> this->diskSize;
    formatDisk();
    formatSectors();
}


int HardDisk::getNumberOfDisks()
{
    return this->numberDisks;
}

void HardDisk::deleteNode(Node* fileNode)
{
    std::vector<int>* locations = fileNode->getBlockLocations();

    for(int i = locations->size()-1; i >= 0; i--)
    {
        int loc = locations->at(i);
        this->sectors.insert(this->sectors.begin(), loc);
    }
}


