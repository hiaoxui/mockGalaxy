#ifndef TEXT2D
#define TEXT2D

#include <vector>
#include <cstring>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "texture.h"

// initiate the loaded
void initText2D(const char * texturePath);

// print the text on the screen
void printText2D(const char * text, int x, int y, int size);

// clean up the text
void cleanupText2D();

#endif
