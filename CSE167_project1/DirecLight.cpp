//
//  DirecLight.cpp
//  CSE167_project1
//
//  Created by Matthew Ma on 12/2/20.
//

#include "DirecLight.h"
DirecLight::DirecLight(glm::vec3 in_direction, glm::vec3 in_ambient, glm::vec3 in_diffuse, glm::vec3 in_specular){
    this->direction = in_direction;
    this->ambient = in_ambient;
    this->diffuse = in_diffuse;
    this->specular = in_specular;
}

void DirecLight::sendLightToShader(const int shaderID){
    glUniform3fv(glGetUniformLocation(shaderID, "lightDirection"), 1, glm::value_ptr(direction));
    glUniform3fv(glGetUniformLocation(shaderID, "lightAmbient"), 1, glm::value_ptr(ambient));
    glUniform3fv(glGetUniformLocation(shaderID, "lightDiffuse"), 1, glm::value_ptr(diffuse));
    glUniform3fv(glGetUniformLocation(shaderID, "lightSpecular"), 1, glm::value_ptr(specular));

}
