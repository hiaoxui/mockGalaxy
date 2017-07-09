#include "ddsvec.h"
#include "sphere.h"
#include "ship.h"

GLFWwindow *window;

void ddsvec::init()
{
	ship::init();

    // Initialise GLFW
    assert(glfwInit());

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(800, 600, "Galaxy", nullptr, nullptr);
    assert(window != nullptr);
	glfwSetWindowPos(window, 200, 100);

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    assert(glewInit() == GLEW_OK);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    loadSphere();
}

ddsvec::ddsvec()
{
    init();

    string path = "0.DDS";
	for (int idx = 0; idx < 10; ++idx)
	{
        path[0] = '0' + idx;
		texbuffer.push_back(loadDDS(path.c_str()));
	}
    path = "10.DDS";
	for (int idx = 0; idx < 10; ++idx)
	{
        path[1] = '0' + idx;
		texbuffer.push_back(loadDDS(path.c_str()));
	}
    texbuffer.push_back(loadDDS("20.DDS"));
}

GLuint *ddsvec::operator[](int textureID)
{
    return texbuffer[textureID];
}
