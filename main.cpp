#include <iostream>
#include <fstream>
#include <vector>
#include "jera_marching_cubes.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    system("pwd");
    std::ifstream pixelDataFile("pixel_data.raw");
    pixelDataFile.seekg(0, pixelDataFile.end);
    size_t length = pixelDataFile.tellg();
    pixelDataFile.seekg(0, pixelDataFile.beg);

    std::vector<uint8_t> pixelData(length);
    pixelDataFile.read(reinterpret_cast<char*>(pixelData.data()), length);

    std::vector<com::jera::vertex> vertices;
    std::vector<uint32_t> triangleIndices;

    com::jera::marching_cubes(pixelData, 146, 128, 116, 879 * 0.55f, vertices, triangleIndices);

    return 0;
}