//
//  Geometry.hpp
//  CSE167_project1
//
//  Created by Matthew Ma on 11/18/20.
//

#ifndef Geometry_h
#define Geometry_h

#include <stdio.h>
#include "Node.h"

class Geometry : public Node{
private:
    std::vector<glm::vec3> points;
    std::vector<glm::ivec3> triangles;
    // Normal colors of eacg vertices
    std::vector<glm::vec3> normals;
    glm::vec3 color;
    
    GLuint VAO, VBO, EBO;
    GLuint nVBO;
    glm::mat4 model;
    
    // Material of each object
    Materials * materials;
    
    // Point light
    PointLight * pointLight;
    
    // Cameras Position
    //glm::vec3 viewPos;

public:
    Geometry(std::string objFilename, Materials* in_materials, PointLight * in_pointLight, bool isSeat);
    //Geometry(std::string objFilename, Materials* in_materials, PointLight * in_pointLight, glm::vec3 eyePos);
    //Geometry(std::string objFilename);
    ~Geometry();
        
    void draw(GLuint shader, glm::mat4 C, bool isRoot, glm::mat4 view, glm::mat4 projection);
    void update(glm::mat4 C);
    void ballRotate(glm::vec3 rotAxis, float rotAngle);
    void adjust(float amount);
    void translate(float x, float y, float z);


};
#endif /* Geometry_hpp */
