//
// Created by John Brewer on 10/11/19.
//

#ifndef COM_JERA_MARCHING_CUBES_H
#define COM_JERA_MARCHING_CUBES_H

#include <vector>

namespace com::jera {
    struct vertex {
        float x,y,z;
    };

    inline void marching_cubes(const std::vector<uint8_t>& pixelData,
            uint16_t rows, uint16_t columns, uint16_t layers,
            float threshold, std::vector<com::jera::vertex>& vertices, std::vector<uint32_t>& triangleIndices) {
    }

} // namespace com::jera

#endif // COM_JERA_MARCHING_CUBES_H
