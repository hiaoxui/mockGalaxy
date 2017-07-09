#include "display.h"
#include "ship.h"

void display(space &evm) {

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Dark black background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
    //glEnable(GL_CULL_FACE);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("myVertexShader.vertexshader", 
		"myFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
	GLuint bID = glGetUniformLocation(programID, "b");
	GLuint gammaID = glGetUniformLocation(programID, "gamma");
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
	GLuint ABID = glGetUniformLocation(programID, "AmbientBonus");
	GLuint TypeID = glGetUniformLocation(programID, "TYPE");

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");
	GLuint NormalTextureID = glGetUniformLocation(programID, "myNormalTextureSampler");
    GLuint NormalTexture = loadBMP("normal.bmp");

	// Holstein is a DDS of the fonts
    initText2D("Holstein.DDS");

	do {
        evm.flush();
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs();
		evm.moveSky();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 P_V_Matrix = ProjectionMatrix * ViewMatrix;
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);

        for (int i = 0; i < evm.size(); ++i) {
			glm::mat4 tmp_ModelMatrix = 
                glm::translate(glm::vec3(evm[i].x, evm[i].y, evm[i].z)) *
                glm::scale(glm::vec3(evm[i].radius, evm[i].radius, evm[i].radius));
			glm::mat4 tmp_MVP = P_V_Matrix * tmp_ModelMatrix;

			// Send transformation to the currently bound shader, 
			// in the "MVP" uniform
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tmp_MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &tmp_ModelMatrix[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
			if (ship::relative) {
				glUniform3f(bID, ship::beta.x, ship::beta.y, ship::beta.z);
				glUniform1f(gammaID, ship::gamma);
				if ((i == 0) && (ship::gamma > 30)) {
					glEnable(GL_BLEND);
					glBlendFunc(1, 1);
					glDisable(GL_DEPTH_TEST);
				} else {
					glDisable(GL_BLEND);
					glEnable(GL_DEPTH_TEST);
				}
			} else {
				glUniform3f(bID, 0, 0, 0);
				glUniform1f(gammaID, 1);
			}
			glUniform1f(ABID, 7);
			glUniform1i(TypeID, i == 0 ? 0 : STAR);
			if (evm[i].identity == CENTRALSTAR)glUniform3f(LightID, evm[i].x, evm[i].y, evm[i].z);

			// Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, *evm[i].textureBuffer);
			// Set our "myTextureSampler" sampler to user Texture Unit 0
			glUniform1i(TextureID, 0);

            // Bind our normal texture in Texture Unit 1
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, NormalTexture);
            // Set our "myNormalTextureSampler" sampler to user Texture Unit 0
            glUniform1i(NormalTextureID, 1);


			// 1rst attribute buffer : vertices
            glBindBuffer(GL_ARRAY_BUFFER, *evm[i].vertexBuffer);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// 2nd attribute buffer : UVs
            glBindBuffer(GL_ARRAY_BUFFER, *evm[i].uvBuffer);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// 3rd attribute buffer : normals
            glBindBuffer(GL_ARRAY_BUFFER, *evm[i].normalBuffer);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

            // 4th attribute buffer : tangents
            glBindBuffer(GL_ARRAY_BUFFER, *evm[i].tangentBuffer);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

            // 5th attribute buffer : bitangents
            glBindBuffer(GL_ARRAY_BUFFER, *evm[i].bitangentBuffer);
            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// Draw
             glDrawArrays(GL_TRIANGLES, 0, evm[i].verticesSize);
		}

		const vector<planet> planets = evm.getPlanets();

        for (planet p : planets)
		{
			float planetX, planetY, planetZ;
			p.getPosition(ship::t, planetX, planetY, planetZ);
			glm::mat4 tmp_ModelMatrix =
				glm::translate(glm::vec3(planetX, planetY, planetZ)) *
				glm::scale(glm::vec3(p.radius, p.radius, p.radius));
			glm::mat4 tmp_MVP = P_V_Matrix * tmp_ModelMatrix;

			// Send transformation to the currently bound shader,
			// in the "MVP" uniform
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tmp_MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &tmp_ModelMatrix[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
			if (ship::relative)
			{
				glUniform3f(bID, ship::beta.x, ship::beta.y, ship::beta.z);
				glUniform1f(gammaID, ship::gamma);
			}
			else
			{
				glUniform3f(bID, 0, 0, 0);
				glUniform1f(gammaID, 1);
			}
			glUniform1f(ABID, 0);
			glUniform1i(TypeID, PLANET);

			// Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, *p.textureBuffer);
			// Set our "myTextureSampler" sampler to user Texture Unit 0
			glUniform1i(TextureID, 0);

			// Bind our normal texture in Texture Unit 1
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, NormalTexture);
			// Set our "myNormalTextureSampler" sampler to user Texture Unit 0
			glUniform1i(NormalTextureID, 1);

			// 1rst attribute buffer : vertices
			glBindBuffer(GL_ARRAY_BUFFER, *p.vertexBuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// 2nd attribute buffer : UVs
			glBindBuffer(GL_ARRAY_BUFFER, *p.uvBuffer);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// 3rd attribute buffer : normals
			glBindBuffer(GL_ARRAY_BUFFER, *p.normalBuffer);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// 4th attribute buffer : tangents
			glBindBuffer(GL_ARRAY_BUFFER, *p.tangentBuffer);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// 5th attribute buffer : bitangents
			glBindBuffer(GL_ARRAY_BUFFER, *p.bitangentBuffer);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// Draw
			glDrawArrays(GL_TRIANGLES, 0, p.verticesSize);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);

		char a[1000], b[1000], c[1000], d[1000], e[1000];
		sprintf(a, "local:%.1fs", tao);
		sprintf(b, "t:%.1fs", ship::t);
		sprintf(c, "gamma:%.3f", ship::gamma);
		sprintf(d, "x:%.2f,y:%.2f,z:%.2f", evm.zone_x+ship::r.x, evm.zone_y+ship::r.y, evm.zone_z+ship::r.z);
		printText2D(a, 440, 550, 30);
		printText2D(b, 560, 500, 30);
		printText2D(c, 10, 50, 30);
		printText2D(d, 10, 10, 30);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}
