#ifndef CAM_HPP
#define CAM_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Cam {
private:
    Cam(Cam const&) = delete;
    void operator= (Cam const&) = delete;

	glm::vec3 pos;
	glm::vec3 lookAt;
	glm::vec3 head;

	glm::mat4 view;
	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	
    Cam() { };

public:
    static Cam& getInstance() {
        static Cam instance;
        return instance;
    }

	void setPos(glm::vec3 pos) {
		this->pos = pos;	
		updateView();	
	}

	void setLookAt(glm::vec3 lookAt) {
		this->lookAt = lookAt;
		updateView();
	}

	void setHead(glm::vec3 head) {
		this->head = head;
		updateView();
	}
	
	void translate(glm::vec3 t) {
		pos += t;
		lookAt += t;
		updateView();
	}
	
	void setProjection(glm::mat4 projection) {
		this->projection = projection;
	}

	void updateView() {
		view = glm::lookAt(pos, lookAt, head);
	}
	
	glm::vec3 getPosition() {
		return pos;
	}

	glm::mat4 getView() {
		//return glm::lookAt(pos, lookAt, head);
		return view;
	}

	glm::mat4 getProjection() {
		return projection;
	}
};

#endif //CAM_HPP
