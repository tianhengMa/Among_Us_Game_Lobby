#ifndef _POINT_CLOUD_H_
#define _POINT_CLOUD_H_

#include "Object.h"
#include "Materials.h"
#include "PointLight.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class PointCloud : public Object
{
private:
	std::vector<glm::vec3> points;
    std::vector<glm::ivec3> triangles;
    // Normal colors of eacg vertices
    std::vector<glm::vec3> rgbs;
    
    // Material of each object
    Materials * materials;
    
    // Point light
    PointLight * pointLight;
    
    // Switch between rendering models
    int modelSwitch;
    
	GLuint VAO, VBO, EBO;
    GLuint nVBO;
	GLfloat pointSize;

public:
    //PointCloud(std::string objFilename, GLfloat pointSize, Materials* in_materials, PointLight * in_pointLight);
    PointCloud(std::string objFilename, GLfloat pointSize);
	~PointCloud();
	
	void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader);
	void update();

	void updatePointSize(GLfloat size);
	void spin(float deg);
    
    void increasePointSize();
    void decreasePointSize();
    
    void scale(double scale);
    void translate(glm::vec3 translation);
    
    void ballRotate(glm::vec3 rotAxis, float rotAngle);
    void toggleModelSwitch();
};

#endif
