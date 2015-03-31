#include <vector>

class VertexGenerator {
public:
	static std::vector<GLfloat> generateMesh(float size, int amount){
		std::vector<GLfloat> v;
		for(int i = 0; i < amount; i++) {
			for(int j = 0; j < amount; j++) {
				v.push_back(i * size);			v.push_back(j * size + size);  
				v.push_back(i * size);			v.push_back(j * size);  
				v.push_back(i * size + size);	v.push_back(j * size);  
				v.push_back(i * size); 			v.push_back(j * size + size);  
				v.push_back(i * size + size);	v.push_back(j * size);  
				v.push_back(i * size + size);	v.push_back(j * size + size);  
			}
		}
		return v;
	}
	
	
	static std::vector<GLfloat> generateBox(float size, int amount){
		std::vector<GLfloat> v;
		for(int i = 0; i < amount; i++) {
			for(int j = 0; j < amount; j++) {
				//BACK
				v.push_back(i * size);			v.push_back(j * size + size);	v.push_back(0);  
				v.push_back(i * size);			v.push_back(j * size);  		v.push_back(0);
				v.push_back(i * size + size);	v.push_back(j * size);  		v.push_back(0);
				v.push_back(i * size); 			v.push_back(j * size + size);  	v.push_back(0);
				v.push_back(i * size + size);	v.push_back(j * size);  		v.push_back(0);
				v.push_back(i * size + size);	v.push_back(j * size + size);  	v.push_back(0);
				
				//FRONT
				v.push_back(i * size);			v.push_back(j * size + size);	v.push_back(size * amount);  
				v.push_back(i * size);			v.push_back(j * size);  		v.push_back(size * amount);
				v.push_back(i * size + size);	v.push_back(j * size);  		v.push_back(size * amount);
				v.push_back(i * size); 			v.push_back(j * size + size);  	v.push_back(size * amount);
				v.push_back(i * size + size);	v.push_back(j * size);  		v.push_back(size * amount);
				v.push_back(i * size + size);	v.push_back(j * size + size);  	v.push_back(size * amount);
				
				//LEFT
				v.push_back(0);					v.push_back(i * size);			v.push_back(j * size + size);	  
				v.push_back(0);					v.push_back(i * size);			v.push_back(j * size);  		
				v.push_back(0);					v.push_back(i * size + size);	v.push_back(j * size);  		
				v.push_back(0);					v.push_back(i * size); 			v.push_back(j * size + size);  	
				v.push_back(0);					v.push_back(i * size + size);	v.push_back(j * size);  		
				v.push_back(0);					v.push_back(i * size + size);	v.push_back(j * size + size);  	
				
				//RIGHT
				v.push_back(size * amount);		v.push_back(i * size);			v.push_back(j * size + size);	  
				v.push_back(size * amount);		v.push_back(i * size);			v.push_back(j * size);  		
				v.push_back(size * amount);		v.push_back(i * size + size);	v.push_back(j * size);  		
				v.push_back(size * amount);		v.push_back(i * size); 			v.push_back(j * size + size);  	
				v.push_back(size * amount);		v.push_back(i * size + size);	v.push_back(j * size);  		
				v.push_back(size * amount);		v.push_back(i * size + size);	v.push_back(j * size + size);  	
				
				//BOTTOM
				v.push_back(i * size);			v.push_back(0);					v.push_back(j * size + size);  
				v.push_back(i * size);			v.push_back(0);  				v.push_back(j * size); 
				v.push_back(i * size + size);	v.push_back(0); 				v.push_back(j * size);
				v.push_back(i * size); 			v.push_back(0);  				v.push_back(j * size + size);
				v.push_back(i * size + size);	v.push_back(0);  				v.push_back(j * size);
				v.push_back(i * size + size);	v.push_back(0);  				v.push_back(j * size + size);
				
				//TOP
				v.push_back(i * size);			v.push_back(size * amount);		v.push_back(j * size + size);  
				v.push_back(i * size);			v.push_back(size * amount);		v.push_back(j * size); 
				v.push_back(i * size + size);	v.push_back(size * amount);		v.push_back(j * size);
				v.push_back(i * size); 			v.push_back(size * amount);		v.push_back(j * size + size);
				v.push_back(i * size + size);	v.push_back(size * amount);		v.push_back(j * size);
				v.push_back(i * size + size);	v.push_back(size * amount);		v.push_back(j * size + size);
			}
		}
		return v;
	}			
};
