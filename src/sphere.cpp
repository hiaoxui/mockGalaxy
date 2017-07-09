#include "sphere.h"
#include "tangentspace.h"

sphere::sphere(string filePath, bool fuckingmagic)
{
	if (fuckingmagic)loadOBJ_fuckingmagic(filePath.c_str(), vertices, uvs, normals);
	else loadOBJ(filePath.c_str(), vertices, uvs, normals);
	computeTangentBasis(vertices, uvs, normals, tangents, bitangents);
    uvBuffer = new GLuint;
    vertexBuffer = new GLuint;
    normalBuffer = new GLuint;
    tangentBuffer = new GLuint;
    bitangentBuffer = new GLuint;

    glGenBuffers(1, vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(vec3),
                 &vertices[0],
            GL_STATIC_DRAW
            );

    glGenBuffers(1, uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, *uvBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 uvs.size() * sizeof(vec2),
                 &uvs[0],
            GL_STATIC_DRAW
            );

	glGenBuffers(1, normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, *normalBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		normals.size() * sizeof(vec3),
		&normals[0],
		GL_STATIC_DRAW
	);

	glGenBuffers(1, tangentBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, *tangentBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		tangents.size() * sizeof(vec3),
		&tangents[0],
		GL_STATIC_DRAW
	);

	glGenBuffers(1, bitangentBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, *bitangentBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		bitangents.size() * sizeof(vec3),
		&bitangents[0],
		GL_STATIC_DRAW
	);
}

GLuint *sphere::getVertexBuffer()
{
    return vertexBuffer;
}

GLuint *sphere::getUvBuffer()
{
    return uvBuffer;
}

GLuint *sphere::getNormalBuffer()
{
    return normalBuffer;
}

GLuint * sphere::getTangentBuffer()
{
	return tangentBuffer;
}

GLuint * sphere::getBitangentBuffer()
{
	return bitangentBuffer;
}

unsigned sphere::getVerticesSize()
{
    return vertices.size();
}

void loadSphere() {
    assert(objs.empty());
    objs.push_back(sphere("sphere0.obj"));
    objs.push_back(sphere("sphere1.obj"));
    objs.push_back(sphere("sphere2.obj"));
    objs.push_back(sphere("sphere3.obj"));
    objs.push_back(sphere("sphere4.obj"));
	objs.push_back(sphere("sphere4.obj", true));
    cout << "all objects have been loaded" << endl;
}
