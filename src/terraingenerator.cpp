#include "terraingenerator.h"

#include <cmath>
#include "glm/glm.hpp"


TerrainGenerator::TerrainGenerator()
{
    // Task 8: Turn of wireframe shading
    m_wireshade = true;

    // Define resolution of terrain generation
    m_resolution = 100;

    // Generate random vector lookup table
    m_lookupSize = 1024;
    m_randVecLookup.reserve(m_lookupSize);

    std::srand(1);

    for(int i = 0; i < m_lookupSize; i++)
    {
        m_randVecLookup.push_back(glm::vec2(std::rand() * 2.0 / RAND_MAX - 1.0,std::rand() * 2.0 / RAND_MAX - 1.0));
    }
}

TerrainGenerator::~TerrainGenerator()
{
    m_randVecLookup.clear();
}

// Samples the infinite grid of random vectors at specified location
glm::vec2 TerrainGenerator::randVec(int row, int col)
{
    std::hash<int> intHash;
    int index = intHash(row * 41 + col * 43) % m_lookupSize;
    return m_randVecLookup.at(index);
}

float interpolate(float A, float B, float x) {
    // Task 4: implement your eased interpolation function below!

}


float TerrainGenerator::computePerlin(float x, float y) {
    // Task 1: Get grid indicies (as int)

    // Task 2: Compute Offset Vectors

    // Task 3: Compute Dot Product between Offset and Grid Vectors

    // Task 5: Use your interpolation function to produce the final value
    return 0;
}

glm::vec3 TerrainGenerator::getPosition(int row, int col) {
    // Normalize horizontal coordinates relative to unit square
    // makes scaling independent of sampling resolution.
    float x = 1.0 * row / m_resolution;
    float y = 1.0 * col / m_resolution;
    float z;

    // Task 6: Modify this call to produce noise of a different frequency
    z = computePerlin(5*x,5*y);

    // Task 7: Combine multiple different octaves of noise to produce fractal perlin noise

    return glm::vec3(x,y,z);
}

glm::vec3 TerrainGenerator::getNormal(int row, int col) {
    // Task 9: Compute the average normal for the given input indicies

    // Return up as placeholder
    return glm::vec3(0,0,1);
}

glm::vec3 TerrainGenerator::getColor(glm::vec3 normal, glm::vec3 position) {
    // Task 10: Compute the Color as a function of the normal and position

    // Return white as placeholder
    return glm::vec3(1,1,1);
}

int TerrainGenerator::getResolution()
{
    return m_resolution;
}

void addPointToVector(glm::vec3 point, std::vector<float>& vector) {
    vector.push_back(point.x);
    vector.push_back(point.y);
    vector.push_back(point.z);
}

// Uses position normal and color information to generate geometry
std::vector<float> TerrainGenerator::generateTerrain() {
    std::vector<float> verts;
    verts.reserve(m_resolution * m_resolution * 6);

    for(int x = 0; x < m_resolution; x++) {
        for(int y = 0; y < m_resolution; y++) {
            int x1 = x;
            int y1 = y;

            int x2 = x + 1;
            int y2 = y + 1;

            glm::vec3 p1 = getPosition(x1,y1);
            glm::vec3 p2 = getPosition(x2,y1);
            glm::vec3 p3 = getPosition(x2,y2);
            glm::vec3 p4 = getPosition(x1,y2);

            glm::vec3 n1 = getNormal(x1,y1);
            glm::vec3 n2 = getNormal(x2,y1);
            glm::vec3 n3 = getNormal(x2,y2);
            glm::vec3 n4 = getNormal(x1,y2);

            // Tris 1
            // x1y1z1
            // x2y1z2
            // x2y2z3
            addPointToVector(p1, verts);
            addPointToVector(n1, verts);
            addPointToVector(getColor(n1, p1), verts);

            addPointToVector(p2, verts);
            addPointToVector(n2, verts);
            addPointToVector(getColor(n2, p2), verts);

            addPointToVector(p3, verts);
            addPointToVector(n3, verts);
            addPointToVector(getColor(n3, p3), verts);

            // Tris 2
            // x1y1z1
            // x2y2z3
            // x1y2z4
            addPointToVector(p1, verts);
            addPointToVector(n1, verts);
            addPointToVector(getColor(n1, p1), verts);

            addPointToVector(p3, verts);
            addPointToVector(n3, verts);
            addPointToVector(getColor(n3, p3), verts);

            addPointToVector(p4, verts);
            addPointToVector(n4, verts);
            addPointToVector(getColor(n4, p4), verts);
        }
    }
    return verts;
}

