#include "HardDisk.h"
#include "Node.h"


void HardDisk::readSectors(HDD)
{
    std::string fileName = "freeSectors" + std::to_string(HDD) + ".dat";
    std::ifstream binaryFile;
    int size = 0;

    binaryFile.open(fileName, std::ios::in | std::ios::binary);
    binaryFile.seekg(0, std::ios::end);
    size = (int)binaryFile.tellg();
    binaryFile.seekg(0, std::ios::beg);

    while(binaryFile.tellg() < size)
    {
        int sector = -1;
        binaryFile.read((char*)&sector, sizeof(sector));
        this->sectors[i].push_back(sector);
    }
    binaryFile.close();
}

void HardDisk::initializeSectors()
{
    for(int i = 0; i < NUMBER_DISKS; i++)
    {
        this->sectors.push_back(std::vector<int>());
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
    int block = this->sectors[HDD].pop_front();
}

void HardDisk::writeBlock(char* data)
{
    int HDD = getEmptyHdd();
    int block = getBlock();

    //Escribimos ahi
    std::string fileName = "disk" + std::to_string(HDD) + ".dat";
    std::ifstream binaryFile;
    int size = 0;

    binaryFile.open(fileName, std::ios::out | std::ios::binary);
    binaryFile.seekg(0, BLOCK_SIZE*block);
    binaryFile.write((char*)data, sizeof(char)*BLOCK_SIZE);
}

/*Subir*/
void HardDisk::writeFile(Node* fileNode)
{
    //dividir el archivo en bloques (restante a cero)
    off_t fileSize = fileNode->getByteSize();
    int numberOfBlocks = (fileSize % static_cast<off_t>(BLOCK_SIZE)) + 1;

    //en un for, por cada bloque leer esa parte, mirar que disco está vacio, escribir
    for (int i = 0; i < numberOfBlocks; i++)
    {
        std::ofstream fs;
        char* binaryData = (char*)malloc(sizeof(char)*BLOCK_SIZE);
        //Open File and Check size
        fs.open(string_cwd, std::ios::in | std::ios::binary);
        if (!fs.is_open()) std::cout << "Cannot open file." << std::endl;

        fs.read((char*)&binaryData, sizeof(binaryData));

        writeBlock(data);
        //Escribir en nodo

        fs.close();
        free(binaryData);
    }
    //Actualizar el fichero de sectores

}

void HardDisk::readBlock()
{

}

void HardDisk::readFile()
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
