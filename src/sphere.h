#ifndef SPHERE
#define SPHERE

#include "objloader.h"

#include <vector>
#include <string>
#include <cassert>

#include <glm/common.hpp>

#include "util.h"

using namespace std;
using namespace glm;

// this class will store some information
// about obj models
class sphere {
private:
    // vertex information
    vector<vec3> vertices;
    // uv information
    vector<vec2> uvs;
    // normal vector information
    vector<vec3> normals;
    // tangent vector information
    vector<vec3> tangents;
    // bitangent vector information
    vector<vec3> bitangents;

    // uv buffer id
    GLuint *uvBuffer;
    // vertex buffer id
    GLuint *vertexBuffer;
    // normal buffer id
    GLuint *normalBuffer;
    // tangent buffer id
    GLuint *tangentBuffer;
    // bitangent buffer id
    GLuint *bitangentBuffer;

public:
    // constructor
	sphere(string filePath, bool fuckingmagic = false);

    // get vertex buffer id
    GLuint *getVertexBuffer();

    // get uv buffer id
    GLuint *getUvBuffer();

    // get normal buffer id
    GLuint *getNormalBuffer();

    // get tangent buffer id
    GLuint *getTangentBuffer();

    // get bitangent buffer id
    GLuint *getBitangentBuffer();

    // get the size of vertex buffer
    unsigned getVerticesSize();
};

// load all obj models in variable objs
void loadSphere();

#endif // SPHERE
