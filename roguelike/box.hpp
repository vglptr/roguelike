#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "cam.hpp"
#include "drawable.hpp"

class Box : public Drawable {
public:
	Box(){
		fillVertices();
		initShaders();
		initGLData();
	}
	
	void fillVertices() {
		vertices = VertexGenerator::generateBox(0.1, 2);
		coordinatesPerVertex = 3;
		r = 1.0f; g = 0.3f; b = 0.3f; 		
	}
	
	void initShaders() {
		vertexSource =
			"#version 150 core\n"
			"in vec3 position;"
			"uniform mat4 mvp;"
			"void main() {"
			"   gl_Position = mvp * vec4(position, 1.0);"
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

	~Box() { 
	}
};
