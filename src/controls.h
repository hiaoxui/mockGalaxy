#ifndef CONTROLS
#define CONTROLS

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

extern GLFWwindow* window;

// this function will set projection matrix by
// the input of the keyboard and mouse
void computeMatricesFromInputs();

// return the ViewMatrix
glm::mat4 getViewMatrix();

// return the ProjectionMatrix
glm::mat4 getProjectionMatrix();

#endif
