#include "HardDisk.h"


HardDisk::HardDisk()
{
    getcwd(this->cwd, sizeof(cwd));
    if (FILE *file = fopen("disk0.dat", "r"))
    {
        std::cout << "Loading Hard Drives..." << std::endl;
    }
    else
    {
        format(32000);
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
