#ifndef DISPLAY
#define DISPLAY

//include strandred libraries
#include <iostream>
#include <vector>
#include <cassert>
#include <string>

//include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

//include sth wrote by me
#include "shader.h"
#include "texture.h"
#include "controls.h"
#include "objloader.h"
#include "text2D.h"
#include "space.h"

// this function will render the galaxy system on the screen
void display(space &evm);

#endif
