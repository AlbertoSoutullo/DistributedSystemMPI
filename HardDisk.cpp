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
    for(int i = 0; i < this->numberDisks; i++)
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
        format();
        initializeSectors();
    }    
}

int HardDisk::getEmptyHdd()
{
    //We assume that the first one is the first empty
    int emptyHDD = 0;
    int emptyHDDSize = this->sectors[emptyHDD].size();
    bool full = false;

    for (int i = 0; i < this->sectors.size(); i++)
    {
        int actualHDDSize = this->sectors[i].size();

        if(actualHDDSize == 0)
        {
            full = true;
        }
        else
        {
            full = false;

            if (actualHDDSize > emptyHDDSize)
            {
                emptyHDD = i;
                emptyHDDSize = this->sectors[emptyHDD].size();
            }
        }
    }
    if (full) return -1;
    else return emptyHDD;
}

int HardDisk::getBlock(int HDD)
{
    int block = this->sectors[HDD].front();
    this->sectors[HDD].erase(this->sectors[HDD].begin());
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
    for (int i = 0; i < this->numberDisks; i++)
    {
        std::string string_cwd = std::string(this->cwd);
        string_cwd += "/freeSectors";
        string_cwd += std::to_string(i);
        string_cwd += ".dat";
        sectorsFile.open(string_cwd, std::ios::in | std::ios::binary | std::ios::trunc);
        for (std::vector<int>::iterator it = this->sectors[i].begin(); it != this->sectors[i].end(); it++)
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
    std::string string_cwd = std::string(this->cwd);

    //dividir el archivo en bloques (restante a cero)
    off_t fileSize = fileNode->getByteSize();
    const off_t blockSize = BLOCK_SIZE;
    int numberOfBlocks = (fileSize / blockSize) + 1;
    int pos = 0; //Last position of reader

    //en un for, por cada bloque leer esa parte, mirar que disco está vacio, escribir
    for (int i = 0; i < numberOfBlocks; i++)
    {
        std::ifstream fs;
        char* binaryData = (char*)malloc(sizeof(char)*BLOCK_SIZE);
        //Open File and Check size
        fs.open(string_cwd + "/" + fileNode->getName(), std::ios::in | std::ios::binary);
        if (!fs.is_open()) std::cout << "Cannot open file." << std::endl;
        fs.seekg(pos, fs.beg);
        fs.read((char*)binaryData, sizeof(binaryData));
        pos = fs.tellg();

        int HDD = getEmptyHdd();

        if (HDD == -1)
        {
            std::cout << "Disks ran out of space." << std::endl;
            fs.close();
            break;
        }
        else
        {
            int block = getBlock(HDD);

            writeBlock(binaryData, HDD, block);
            //Escribir en nodo
            (*fileNode).setBlock(block, HDD);

            fs.close();
            //free(binaryData);
        }
    }
    //Actualizar el fichero de sectores
    (*fileNode).setNumBlocksOccupied();
    overrideSectors();

}

void HardDisk::readBlock(std::ifstream &disk, std::ofstream &file, int position, int block)
{
    char* binaryData = (char*)malloc(sizeof(char)*BLOCK_SIZE);
    disk.seekg(block*BLOCK_SIZE);
    disk.read((char*)binaryData, sizeof(binaryData));

    file.seekp(BLOCK_SIZE*position);
    file.write((char*)binaryData, sizeof(char)*BLOCK_SIZE);
    //free(binaryData);
}

void HardDisk::readFile(Node* fileNode)
{
    std::ofstream file;
    std::ifstream disk;

    std::string string_cwd = std::string(this->cwd);
    string_cwd += "/";
    string_cwd += fileNode->getName();
    file.open(string_cwd, std::ios::in | std::ios::binary | std::ios::trunc);

    std::vector<location_t> locations = fileNode->getBlockLocations();

    for (int i = 0; i < fileNode->getNumBlocksOccupied(); i++)
    {
        //saco hdd
        int hdd = locations[i].HDD;
        //saco bloque
        int block = locations[i].block;
        //leo datos
        disk.open(string_cwd + "/disk" + std::to_string(hdd) + ".dat", std::ios::in | std::ios::binary);

        //escribo en el archivo en posicion i*blocksize
        readBlock(disk, file, i, block);
        disk.close();
    }
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
    for (int i = 0; i < this->numberDisks; i++)
    {
        std::string string_cwd = std::string(this->cwd);
        string_cwd += "/freeSectors";
        string_cwd += std::to_string(i);
        string_cwd += ".dat";
        sectorsFile.open(string_cwd, std::ios::in | std::ios::binary | std::ios::trunc);
        for (int j = 0; j < this->diskSize; j++)
        {
            sectorsFile.write((char*)&j, sizeof(j));
        }
        sectorsFile.close();
    }
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
    std::cout << "Select size for each disk: " << std::endl;
    std::cin >> this->diskSize;
    formatDisk();
    formatSectors();
}


int HardDisk::getNumberOfDisks()
{
    return this->numberDisks;
}


