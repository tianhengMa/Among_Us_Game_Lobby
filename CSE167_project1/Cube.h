#ifndef _CUBE_H_
#define _CUBE_H_

#include "Object.h"

#include <vector>
class Cube : public Object
{
private:
	GLuint VAO;
	GLuint VBO, EBO;
    unsigned int cubemapTexture;

public:
	Cube(float size);
	~Cube();

	void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader);
	void update();

	void spin(float deg);
    
    //Skybox
    unsigned int loadCubemap(std::vector<std::string> faces);
    
    void ballRotate(glm::vec3 rotAxis, float rotAngle);
    
    unsigned int getSkyboxTexture();
    
};

#endif
