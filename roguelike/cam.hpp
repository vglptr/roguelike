#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Cam {
private:
    Cam(Cam const&) = delete;
    void operator= (Cam const&) = delete;

	glm::vec3 pos;
	glm::vec3 lookAt;
	glm::vec3 head;
	
    Cam(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 head) {
		this.pos = pos;
		this.lookAt = lookAt;
		this.head = head;
	};

public:
    static Cam& getInstance() {
        static Cam instance;
        return instance;
    }

	void setPos(glm::vec3 pos) {
		this.pos = pos;		
	}

	void setLookAt(glm::vec3 lookAt) {
		this.lookAt = lookAt;
	}

	void setHead(glm::vec3 head) {
		this.head = head;
	}

	glm::mat4 getView() {
		return glm::lookAt(pos, lookAt, head);
	}
};


