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
    
    // Directional light
    DirecLight * direcLight;
    
    // Cameras Position
    //glm::vec3 viewPos;
    int isAstronaut;
    
    // Bounding Sphere
    //glm::vec3 sphere_center;
    //float sphere_radius;
    //BoundingSphere * sphere;

public:
    Geometry(std::string objFilename, Materials* in_materials, DirecLight * in_direcLight, int in_isAstronaut, glm::vec3 in_color, BoundingSphere * in_sphere);
    //Geometry(std::string objFilename, Materials* in_materials, PointLight * in_pointLight, glm::vec3 eyePos);
    //Geometry(std::string objFilename);
    ~Geometry();
        
    void draw(GLuint shader, glm::mat4 C, bool isRoot, glm::mat4 view, glm::mat4 projection);
    void update(glm::mat4 C);
    void ballRotate(glm::vec3 rotAxis, float rotAngle);
    void adjust_sphere(float radius_scale, glm::vec3 center_translate);
    void translate(glm::vec3 translation);
    void rotate(float direction);
    
    BoundingSphere * sphere;
    glm::vec3 lookAt; // facing direction
    
    // Bounding Sphere
    //glm::vec3 sphere_center;
    //float sphere_radius;


};
#endif /* Geometry_hpp */
