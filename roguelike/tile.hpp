#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Tile{
private:
	std::vector<GLfloat> vertices;
	GLint uniColor;
	GLint uniMvp;
	GLuint shaderProgram;
	GLuint fragmentShader;
	GLuint vertexShader;
	GLuint vbo;
	GLuint vao;

	const GLchar* vertexSource =
		"#version 150 core\n"
		"in vec2 position;"
		"uniform mat4 mvp;"
		"void main() {"
		"   gl_Position = mvp * vec4(position, 0.0, 1.0);"
		"}";

	const GLchar* fragmentSource =
		"#version 150 core\n"
		"out vec4 outColor;"
		"uniform vec3 color;"
		"void main() {"
		"   outColor = vec4(color, 1.0);"
		"}";
		
public:
	Tile(GLfloat r, GLfloat g, GLfloat b) {
		// Create Vertex Array Object
		
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Create a Vertex Buffer Object and copy the vertex data to it
		glGenBuffers(1, &vbo);
		
		vertices = VertexGenerator::generateMesh(0.1, 2);
		GLfloat* v = &vertices[0];
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, v, GL_STATIC_DRAW);

		// Create and compile the vertex shader
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);

		// Create and compile the fragment shader
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);

		// Link the vertex and fragment shader into a shader program
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glBindFragDataLocation(shaderProgram, 0, "outColor");
		glLinkProgram(shaderProgram);
		glUseProgram(shaderProgram);

		// Specify the layout of the vertex data
		GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

		// Get the location of the color uniform
		uniColor = glGetUniformLocation(shaderProgram, "color");
		glUniform3f(uniColor, r, g, b);

		//global cam, proj singletont csinalni
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::lookAt(
			glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
			glm::vec3(0,0,0), // and looks at the origin
			glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		glm::mat4 pvm = projection * view * model;
		uniMvp = glGetUniformLocation(shaderProgram, "mvp");
		glUniformMatrix4fv(uniMvp, 1, false, &pvm[0][0]);
	}

	void draw(Timer& timer) {
		//std::cout<<timer.getTime()<<std::endl;
		// Set the color of the triangle
		//glUniform3f(uniColor, (sin(timer.getTime()) + 1.0f) / 2.0f, 0.0f, 0.0f);

		// Draw a triangle from the 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() * 4);
	}

	virtual ~Tile() {
		glDeleteProgram(shaderProgram);
		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}
};
