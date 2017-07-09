#ifndef UTIL
#define UTIL

#include <vector>
#include <cmath>
#include <string>
#include <cstring>

#include <glm/common.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>

#define WIDTH 100000
#define HEIGHT 1000
#define FINE 105
#define CONVAS 2048
#define GM 0.0031622777

using namespace std;
using namespace glm;

using byte = unsigned char;

class body;
class sphere;
class ddsvec;
class space;

// all obj models
extern vector<sphere> objs;

// all textures
extern ddsvec textures;

// main window
extern GLFWwindow *window;

// current position
extern dvec3 position;
// fixed time
extern double tao;

// rotate a vector
void rotateTheta(float &x, float &y, float theta);

#endif // UTIL

