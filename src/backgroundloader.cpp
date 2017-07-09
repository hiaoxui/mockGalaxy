#include "backgroundloader.h"
#include "space.h"

backgroundLoader::backgroundLoader()
{
    bufferID = nullptr;
}

GLuint* backgroundLoader::genBuffer(const space &evm)
{
    if(bufferID == nullptr)
    {
        lastZoneX = evm.zone_x;
        lastZoneY = evm.zone_y;
        lastZoneZ = evm.zone_z;
        return _genBuffer(evm);
    }

    int deltaX = evm.zone_x - lastZoneX;
    int deltaY = evm.zone_y - lastZoneY;
    int deltaZ = evm.zone_z - lastZoneZ;

    int distance = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;
    if(distance > 10000)
    {
        deleteBuffer();
        lastZoneX = evm.zone_x;
        lastZoneY = evm.zone_y;
        lastZoneZ = evm.zone_z;
        return _genBuffer(evm);
    }

    return bufferID;
}

GLuint* backgroundLoader::_genBuffer(const space &evm)
{
	
    byte *data = getBg(evm.zone_x, evm.zone_y, evm.zone_z, factor1, factor2);

	bufferID = new GLuint;// *bufferID = loadBMP("DDS\\normal.bmp"); return bufferID;
    glGenTextures(1, bufferID);
    glBindTexture(GL_TEXTURE_2D,
                  *bufferID);
    glTexImage2D(GL_TEXTURE_2D,
                  0,
                  GL_RGB,
                  CONVAS,
                  CONVAS,
                  0,
                  GL_BGR,
                  GL_UNSIGNED_BYTE,
                  data);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);
    delete[] data;
    return bufferID;
}

void backgroundLoader::deleteBuffer()
{
    if( bufferID != nullptr)
    {
        glDeleteTextures(1, bufferID);
        delete bufferID;
    }
}
