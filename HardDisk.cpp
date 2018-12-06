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
        //std::tuple<int,int> tupleData (HDD,sector);
        this->sectors[HDD].push_back(sector);
    }
    binaryFile.close();
}

void HardDisk::initializeSectors()
{
    for(int i = 0; i < NUMBER_DISKS; i++)
    {
        this->sectors.push_back(std::list<int>());
        readSectors(i);
    }
}

HardDisk::HardDisk()
{
    getcwd(this->cwd, sizeof(cwd));
    if (FILE *file = fopen("disk0.dat", "r"))
    {
        std::cout << "Loading Hard Drives..." << std::endl;
        initializeSectors();
    }
    else
    {
        std::cout << "Creating Hard Drives..." << std::endl;
        format(DISK_SIZE);
        initializeSectors();
    }    
}

int HardDisk::getEmptyHdd()
{
    //We assume that the first one is the first empty
    int emptyHDD = 0;

    for (int i = 0; i < this->sectors.size(); i++)
    {
        int actualHDD = this->sectors[i].size();
        if (actualHDD < emptyHDD)
        {
            emptyHDD = actualHDD;
        }
    }
    return emptyHDD;
}

int HardDisk::getBlock(int HDD)
{
    int block = this->sectors[HDD].front();
    this->sectors[HDD].pop_front();
    return block;
}

void HardDisk::writeBlock(char* data, int HDD, int block)
{
    //Escribimos ahi
    std::string fileName = "disk" + std::to_string(HDD) + ".dat";
    std::ofstream binaryFile;

    binaryFile.open(fileName, std::ios::out | std::ios::binary);
    binaryFile.seekp(BLOCK_SIZE*block);
    binaryFile.write((char*)data, sizeof(char)*BLOCK_SIZE);
    binaryFile.close();
}

void HardDisk::overrideSectors()
{
    std::ofstream sectorsFile;
    for (int i = 0; i < NUMBER_DISKS; i++)
    {
        std::string string_cwd = std::string(this->cwd);
        string_cwd += "/freeSectors";
        string_cwd += std::to_string(i);
        string_cwd += ".dat";
        sectorsFile.open(string_cwd, std::ios::in | std::ios::binary | std::ios::trunc);
        for (std::list<int>::iterator it = this->sectors[i].begin(); it != this->sectors[i].end(); it++)
        {
            int number = *it;
            sectorsFile.write((char*)&number, sizeof(int));
        }
        sectorsFile.close();
    }
}

/*Subir*/
void HardDisk::writeFile(Node* fileNode)
{
    //dividir el archivo en bloques (restante a cero)
    off_t fileSize = fileNode->getByteSize();
    std::cout << BLOCK_SIZE << std::endl;
    int numberOfBlocks = (fileSize % BLOCK_SIZE) + 1;
    int pos = 0; //Last position of reader

    //en un for, por cada bloque leer esa parte, mirar que disco está vacio, escribir
    for (int i = 0; i < numberOfBlocks; i++)
    {
        std::ifstream fs;
        char* binaryData = (char*)malloc(sizeof(char)*BLOCK_SIZE);
        //Open File and Check size
        fs.open(fileNode->getName(), std::ios::in | std::ios::binary);
        if (!fs.is_open()) std::cout << "Cannot open file." << std::endl;
        fs.seekg(pos, fs.beg);
        fs.read((char*)&binaryData, sizeof(binaryData));
        pos = fs.tellg();

        int HDD = getEmptyHdd();
        int block = getBlock(HDD);

        writeBlock(binaryData, HDD, block);
        //Escribir en nodo
        fileNode->setBlocksOccupied(block, HDD);

        fs.close();
        free(binaryData);
    }
    //Actualizar el fichero de sectores
    overrideSectors();

}

void HardDisk::readBlock()
{

}

void HardDisk::readFile(Node* fileNode)
{}


void HardDisk::formatDisk()
{
    std::ofstream diskFile;
    for (int i = 0; i < NUMBER_DISKS; i++)
    {
        std::string string_cwd = std::string(this->cwd);
        string_cwd += "/disk";
        string_cwd += std::to_string(i);
        string_cwd += ".dat";
        diskFile.open(string_cwd, std::ios::in | std::ios::binary | std::ios::trunc);
        diskFile.close();
    }
}

void HardDisk::formatSectors(int size)
{
    std::ofstream sectorsFile;
    for (int i = 0; i < NUMBER_DISKS; i++)
    {
        std::string string_cwd = std::string(this->cwd);
        string_cwd += "/freeSectors";
        string_cwd += std::to_string(i);
        string_cwd += ".dat";
        sectorsFile.open(string_cwd, std::ios::in | std::ios::binary | std::ios::trunc);
        for (int j = 0; j < size; j++)
        {
            sectorsFile.write((char*)&j, sizeof(j));
        }
        sectorsFile.close();
    }
}

bool HardDisk::checkIfExistsHDD()
{
    for(int i = 0; i < NUMBER_DISKS; i++)
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

void HardDisk::format(int size)
{
    std::cout << "Formatting Hard Drives..." << std::endl;
    formatDisk();
    formatSectors(size);
}
