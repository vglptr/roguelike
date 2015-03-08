#include <vector>

class VertexGenerator {
public:
	static std::vector<GLfloat> generateMesh(float size, int amount){
		std::vector<GLfloat> vertices;
		for(int i = 0; i < amount; i++) {
			for(int j = 0; j < amount; j++) {
				vertices.push_back(i * size);   
				vertices.push_back(j * size + size);  
				vertices.push_back(i * size);  
				vertices.push_back(j * size);  
				vertices.push_back(i * size + size);  
				vertices.push_back(j * size);  
				vertices.push_back(i * size);  
				vertices.push_back(j * size + size);  
				vertices.push_back(i * size + size);  
				vertices.push_back(j * size);  
				vertices.push_back(i * size + size);  
				vertices.push_back(j * size + size);  
			}
		}
		return vertices;
	}		
};
