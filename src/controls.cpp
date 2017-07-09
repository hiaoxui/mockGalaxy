#include "controls.h"
#include "ship.h"
#include "stdio.h"
#ifndef M_PI
	#define M_PI 3.141592654
#endif

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix() {
    return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
    return ProjectionMatrix;
}

// Initial position : on +Z
glm::dvec3 position = glm::dvec3(0, 0, 0);
double T = 0, tao = 0;

// Initial horizontal angle : toward -Z
float horizontalAngle = M_PI;

// Initial vertical angle : none
float verticalAngle = 0.0f;

// Initial Field of View
// 45.0 has a good vision
float initialFoV = 45.0f;

// 3 units / second
float acc = 0.5f;
float rotspeed = 3.0f; 
float mouseSpeed = 0.005f;

int paused = 0, p_released = 1;

void computeMatricesFromInputs() {

    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();

    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    // Get mouse position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);


    // the function of H, L, J, K is the same as mouse move
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        xpos -= 5;

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        xpos += 5;

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        ypos += 5;

    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        ypos -= 5;

    // Reset mouse position for next frame
    glfwSetCursorPos(window, 1024 / 2, 768 / 2);

    // Compute new orientation
    horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
    verticalAngle += mouseSpeed * float(768 / 2 - ypos);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		horizontalAngle = M_PI;
		verticalAngle = 0;
	}

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
                cos(verticalAngle) * sin(horizontalAngle),
                sin(verticalAngle),
                cos(verticalAngle) * cos(horizontalAngle)
                );

    // Right vector
    glm::vec3 right = glm::vec3(
                sin(horizontalAngle - M_PI / 2.0f),
                0,
                cos(horizontalAngle - M_PI / 2.0f)
                );

    // Up vector
    glm::vec3 up = glm::cross(right, direction);

	glm::mat3 shipMat = ship::getMatrix();
	direction = shipMat*direction;
	up = shipMat*up;
	right = shipMat*right;

    // accelerate forward
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		ship::forward(deltaTime*acc);
	}
    // accelerate backward
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		ship::forward(-deltaTime*acc);
	}
    // acc right
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		ship::leftward(-deltaTime*acc);
    }
    // acc left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		ship::leftward(deltaTime*acc);
    }
	// turn up
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		ship::turn_up(deltaTime*rotspeed);
	}
	// turn down
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		ship::turn_up(-deltaTime*rotspeed);
	}
	// turn left
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		ship::turn_left(-deltaTime*rotspeed);
	}
	// turn right
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		ship::turn_left(deltaTime*rotspeed);
	}
	// stop(cheat)
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
		ship::beta = glm::vec3(0, 0, 0);
		ship::gamma = 1;
	}
	// toggle relativistic vision
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		ship::relative = 1;
	}
	// toggle relativistic vision
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		ship::relative = 0;
	}
	// into orbit
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		ship::makeOrbit();
	}

	if (!paused)T += deltaTime; else tao -= deltaTime;
	ship::r = position;
	double t0 = ship::t;
	while (tao < T)
	{
		ship::nextFrame(deltaTime / 10.0);
		tao += deltaTime / 10.0;
	}
	if (paused)ship::t = t0;
	position = ship::r;

    float FoV = initialFoV;

    // Projection matrix
    ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, .0001f, 80.0f);

    // Camera matrix
    //printf("aa %f %f %f aa",position.y,direction.z,up.z);
    ViewMatrix = glm::lookAt((glm::vec3)position, (glm::vec3)position + direction, up);

    // press Q to incline the acceleration speed
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		if (acc < 3)acc *= 1.1f;

    // press E to decline the acceleration speed
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		if (acc > 0.03)acc /= 1.1f;

    // press P to pause
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		if (p_released)paused ^= 1;
		p_released = 0;
	}
	else p_released = 1;


    lastTime = currentTime;
}
