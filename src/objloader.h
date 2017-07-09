#ifndef OBJLOADER
#define OBJLOADER

#include <vector>
#include <string>
#include <cstring>
#include <glm/glm.hpp>
#include <stdio.h>
#include <iostream>

// load the .obj file and store the information 
// in three vectors
bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> &out_vertices, 
	std::vector<glm::vec2> &out_uvs, 
	std::vector<glm::vec3> &out_normals
);

// a magic OBJ loader that works FUCKING well
bool loadOBJ_fuckingmagic(
	const char * path, 
	std::vector<glm::vec3> &out_vertices, 
	std::vector<glm::vec2> &out_uvs, 
	std::vector<glm::vec3> &out_normals
);

#endif
