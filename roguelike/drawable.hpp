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

	Drawable() { }
};
