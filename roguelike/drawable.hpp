#include "glm/glm.hpp"

class Drawable {
protected:
	std::vector<GLfloat> vertices;
	GLint uniColor;
	GLint uniMvp;
	GLuint shaderProgram;
	GLuint fragmentShader;
	GLuint vertexShader;
	GLuint vbo;
	GLuint vao;
	glm::mat4 model = glm::mat4(1.0f);
	GLfloat r = 0.5, g = 0.5, b = 0.5;
	std::string vertexSource;
	std::string fragmentSource;

	virtual void fillVertices() = 0;
	virtual void translate(glm::vec3 t) = 0;
	virtual void initShaders() = 0;
		
	void initGLData() {
		GLfloat* v = &vertices[0];
		// Create Vertex Array Object
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Create a Vertex Buffer Object and copy the vertex data to it
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), v, GL_STATIC_DRAW);

		// Create and compile the vertex shader
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* vs = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &vs, NULL);
		glCompileShader(vertexShader);

		// Create and compile the fragment shader
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fs = fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &fs, NULL);
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
		uniMvp = glGetUniformLocation(shaderProgram, "mvp");
	}

public:	
	void draw(float delta) {
		glm::mat4 view = Cam::getInstance().getView();
		glm::mat4 projection = Cam::getInstance().getProjection();
		glm::mat4 mvp = projection * view * model;
		glUniformMatrix4fv(uniMvp, 1, false, &mvp[0][0]);
		//glUniform3f(uniColor, (sin(timer.getTime()) + 1.0f) / 2.0f, 0.0f, 0.0f);
		glDrawArrays(GL_LINES, 0, vertices.size() * sizeof(GLfloat));
	}
	
	virtual ~Drawable() {
		glDeleteProgram(shaderProgram);
		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}
};
