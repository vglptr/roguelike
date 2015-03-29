#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "cam.hpp"
#include "drawable.hpp"

class Tile : public Drawable {
public:
	Tile(){
		fillVertices();
		initShaders();
		initGLData();
	}
	
	void fillVertices() {
		vertices = VertexGenerator::generateMesh(0.1, 2);		
	}
	
	void initShaders() {
		vertexSource =
			"#version 150 core\n"
			"in vec2 position;"
			"uniform mat4 mvp;"
			"void main() {"
			"   gl_Position = mvp * vec4(position, 0.0, 1.0);"
			"}";

		fragmentSource =
			"#version 150 core\n"
			"out vec4 outColor;"
			"uniform vec3 color;"
			"void main() {"
			"   outColor = vec4(color, 1.0);"
			"}";
	}

	void translate(glm::vec3 t) {
		model = glm::translate(model, t);
	}	

	virtual ~Tile() { }
};
