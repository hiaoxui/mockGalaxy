#ifndef SHADER
#define SHADER

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>

// shader loader
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif
