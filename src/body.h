#ifndef BODY
#define BODY

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "util.h"
#include "sphere.h"
#include "ddsvec.h"

#define STAR 1
#define PLANET 2
#define CENTRALSTAR 3

// celestial body
class body
{
public:

    // constructor
    body(int identity, float mass, float radius, float x, float y, float z);

    // default constructor
    body() = default;

    // bind both obj model and texture
    void bindBuffer(int rank, int textureID);

    // bind obj model only
    void bindBuffer(int rank);

    // the mass of the body
    float mass;
    // the radius of the body
    float radius;
    // the relative position of the body
    float x, y, z;

    // vertex buffer ID
    GLuint *vertexBuffer = nullptr;
    // uv buffer ID
    GLuint *uvBuffer = nullptr;
    // normal buffer ID
    GLuint *normalBuffer = nullptr;
    // tangent buffer ID
    GLuint *tangentBuffer = nullptr;
    // bitangent buffer ID
    GLuint *bitangentBuffer = nullptr;
    // texture buffer ID
    GLuint *textureBuffer = nullptr;

    // the identity of the body, for instance, STAR, PLANET, CENTRALSTAR
    int identity;
    // the size of the vertex buffer
    unsigned verticesSize;
};

#endif // BODY

