#pragma once

#include <vector>
#include "glm/glm.hpp"

class TerrainGenerator
{
public:
    bool m_wireshade;

    TerrainGenerator();
    ~TerrainGenerator();
    std::vector<float> generateTerrain();
    int getResolution();

private:

    // Member variables for terrain generation, you will not need to use these
    std::vector<glm::vec2> m_randVecLookup;
    int m_resolution;
    int m_lookupSize;

    // Takes vertex x and y integer coordinate of terrain mesh
    // Returns position within 1x1 unit square with height sampled from noise functions
    glm::vec3 getPosition(int x, int y);

    // Computes the Normal of a vertex by averaging neighbors
    glm::vec3 getNormal(int x, int y);

    // Computes Color of vertex using normal and optionally position
    glm::vec3 getColor(glm::vec3 normal,glm::vec3 position);

    // Samples Infinite Random Vector Grid at integer row and col
    glm::vec2 randVec(int row, int col);

    // Computes Perlin noise at a point in the infinite vertex grid
    float computePerlin(float x, float y);
};
