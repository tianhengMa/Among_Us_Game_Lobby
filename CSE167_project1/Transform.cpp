//
//  Transform.cpp
//  CSE167_project1
//
//  Created by Matthew Ma on 11/18/20.
//

#include "Transform.h"
Transform::Transform(glm::mat4 M){
    this->M = M;
}

void Transform::addChild(Node* node){
    childNodes.push_back(node);
}

void Transform::draw(GLuint shader, glm::mat4 C, bool isRoot=false, glm::mat4 view=glm::mat4(1), glm::mat4 projection=glm::mat4(1)){
    glm::mat4 newC = C * M;
    
    if (isRoot){
        newC = projection * view * M;
    }
    for (int i = 0; i < childNodes.size(); i++){
        childNodes[i]->draw(shader, newC, false, glm::mat4(1), glm::mat4(1));
    }
}

void Transform::update(glm::mat4 C){
    M = C * M;
}
