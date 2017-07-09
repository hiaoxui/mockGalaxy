#include "body.h"

body::body(int identity, float mass, float radius, float x, float y, float z)
{
    this->identity = identity;
    this->radius = radius;
    this->mass = mass;
    this->x = x;
    this->y = y;
    this->z = z;
}

void body::bindBuffer(int rank, int textureID) {
	assert(vertexBuffer == nullptr);
	assert(uvBuffer == nullptr);
	assert(normalBuffer == nullptr);
	assert(tangentBuffer == nullptr);
	assert(bitangentBuffer == nullptr);
	assert(textureBuffer == nullptr);
	vertexBuffer = objs[rank].getVertexBuffer();
	uvBuffer = objs[rank].getUvBuffer();
	normalBuffer = objs[rank].getNormalBuffer();
	tangentBuffer = objs[rank].getTangentBuffer();
	bitangentBuffer = objs[rank].getBitangentBuffer();
	textureBuffer = textures[textureID];
	verticesSize = objs[rank].getVerticesSize();
}

/*void body::bindBuffer(int rank, GLuint *bufferID)
{
	assert(vertexBuffer == nullptr);
	assert(uvBuffer == nullptr);
	assert(normalBuffer == nullptr);
	assert(textureBuffer == nullptr);
	uvBuffer = objs[rank].getUvBuffer();
	normalBuffer = objs[rank].getNormalBuffer();
	vertexBuffer = objs[rank].getVertexBuffer();
	verticesSize = objs[rank].getVerticesSize();
	textureBuffer = bufferID;
}*/

void body::bindBuffer(int rank)
{
    assert(uvBuffer == nullptr);
    vertexBuffer = objs[rank].getVertexBuffer();
    uvBuffer = objs[rank].getUvBuffer();
    normalBuffer = objs[rank].getNormalBuffer();
    tangentBuffer = objs[rank].getTangentBuffer();
    bitangentBuffer = objs[rank].getBitangentBuffer();
    verticesSize = objs[rank].getVerticesSize();
}
