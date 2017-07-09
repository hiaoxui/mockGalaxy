#ifndef DDSVEC
#define DDSVEC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "util.h"
#include "texture.h"

// store the dds textures
class ddsvec
{
public:
    // the function will init glfw, glew and then load all
    // dds resources
    void init();

    // the buffer IDs of textures
    vector<GLuint*> texbuffer;

    // the default constructor
    ddsvec();

    // given id ,it will return the texture buffer ID
    GLuint *operator[](int textureID);
};

#endif // DDSVEC

