//
//  Transform.h
//  CSE167_project1
//
//  Created by Matthew Ma on 11/18/20.
//

#ifndef Transform_h
#define Transform_h

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Node.h"
using namespace std;

class Transform : public Node{
public:
    glm::mat4 M;
    std::vector<Node*> childNodes;
    
    Transform(glm::mat4 M);
    void addChild(Node* node);
    void draw(GLuint shader, glm::mat4 C, bool isRoot, glm::mat4 view, glm::mat4 projection);
    void update(glm::mat4 C);
    
};
#endif /* Transform_h */
