#include "HardDisk.h"
#include "Node.h"

HardDisk::HardDisk()
{
    getcwd(this->cwd, sizeof(cwd));
    if (FILE *file = fopen("disk0.dat", "r"))
    {
        std::cout << "Loading Hard Drives..." << std::endl;
    }
    else
    {
        format(DISK_SIZE);
    }
}


void HardDisk::writeBlock(char* data)
{

}

void HardDisk::writeFile(Node* fileNode)
{
    //dividir el archivo en bloques (restante a cero)
    off_t fileSize = fileNode->getByteSize();
    int numberOfBlocks = (fileSize % static_cast<off_t>(1024)) + 1;

    //en un for, por cada bloque leer esa parte, mirar que disco está vacio, escribir
    for (int i = 0; i < numberOfBlocks; i++)
    {
        std::ofstream fs;
        char* binaryData = (char*)malloc(sizeof(char)*1024);
        //Open File and Check size
        fs.open(string_cwd, std::ios::in | std::ios::binary);
        if (!fs.is_open()) std::cout << "Cannot open file." << std::endl;

        fs.read((char*)&binaryData, sizeof(binaryData));

        writeBlock(data);


        fs.close();
        free(binaryData);
    }


}




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
