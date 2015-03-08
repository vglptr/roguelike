class GlObject{
private:
	
		
public:
	GlObject(const GLchar& vertexSource, const GLchar& fragmentSource, const std::vector<GLfloat>& vertices) {
		// Create Vertex Array Object
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Create a Vertex Buffer Object and copy the vertex data to it
		GLuint vbo;
		glGenBuffers(1, &vbo);

		std::vector<GLfloat> vertices = VertexGenerator::generateMesh(0.1, 2);
		GLfloat* v = &vertices[0];

		std::cout<<"size of vertices: "<<vertices.size()<<std::endl;
	
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, v, GL_STATIC_DRAW);

		// Create and compile the vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);

		// Create and compile the fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);

		// Link the vertex and fragment shader into a shader program
		GLuint shaderProgram = glCreateProgram();
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
		GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");				
	}
	virtual void draw(float delta)=0;
	virtual ~GLObject() {};
};
