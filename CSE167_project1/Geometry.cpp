//
//  Geometry.cpp
//  CSE167_project1
//
//  Created by Matthew Ma on 11/18/20.
//

#include "Geometry.h"
using namespace std;
#include <limits>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <glm/gtx/string_cast.hpp>

Geometry::Geometry(std::string objFilename, Materials* in_materials, PointLight * in_pointLight, bool isSeat)
{
    // Initialize materials
    materials = in_materials;
    
    // Initialize pointlight
    pointLight = in_pointLight;
    
    // Initialize camera position
    //viewPos = eyePos;
    
    ifstream objFile(objFilename); // The obj file we are reading.

    // Check whether the file can be opened.
    if (objFile.is_open())
    {
        std::string line; // A line in the file.

        // Read lines from the file.
        while (std::getline(objFile, line))
        {
            // Turn the line into a string stream for processing.
            std::stringstream ss;
            ss << line;
            
            // Read the first word of the line.
            std::string label;
            ss >> label;

            // If the line is about vertex (starting with a "v").
            if (label == "v")
            {
                // Read the later three float numbers and use them as the
                // coordinates.
                glm::vec3 point;
                ss >> point.x >> point.y >> point.z;
                
                //ss >> color.x >> color.y >> color.z;

                // Process the point. For example, you can save it to a.
                points.push_back(point);
            }
            
            // If the line is about triangle ("f")
            else if (label == "f"){
                glm::ivec3 triangle;
                string v1, v2, v3;
                // Read in the three vertices of triangle
                ss >> v1;
                triangle.x = stoi(v1.substr(0, v1.find("//")))-1;
                if (isSeat){
                    triangle.x = stoi(v1.substr(0, v1.find("/")))-1;
                }
                
                ss>>v2;
                triangle.y = stoi(v2.substr(0, v2.find("//")))-1;
                if (isSeat){
                    triangle.y = stoi(v2.substr(0, v2.find("/")))-1;
                }
                
                ss>>v3;
                triangle.z = stoi(v3.substr(0, v3.find("//")))-1;
                if (isSeat){
                    triangle.z = stoi(v3.substr(0, v3.find("/")))-1;
                }
                triangles.push_back(triangle);

            }
            
            else if (label == "vn"){
                glm::vec3 rgb;
                ss >>rgb.x >> rgb.y >> rgb.z;
        
                normals.push_back(rgb);
            }
        }
    }
    else
    {
        std::cerr << "Can't open the file " << objFilename << std::endl;
    }

    objFile.close();
    
    
    // Get max and min for all dimensions for all points
    GLfloat max_x,max_y,max_z = FLT_MIN;
    GLfloat min_x,min_y,min_z = FLT_MAX;
    
    for (int i = 0; i < points.size(); i++){
        glm::vec3 point = points[i];
        max_x = max(point.x, max_x);
        max_y = max(point.y, max_y);
        max_z = max(point.z, max_z);
        
        min_x = min(point.x, min_x);
        min_y = min(point.y, min_y);
        min_z = min(point.z, min_z);
    }
    
    // Get center point for all dimensions
    GLfloat center_x = (max_x + min_x)/2;
    GLfloat center_y = (max_y + min_y)/2;
    GLfloat center_z = (max_z + min_z)/2;
    glm::vec3 center = glm::vec3(center_x, center_y, center_z);
    
    // Max distance from center point
    GLfloat max_dist = 0;
    
    // Shift all model coordinates by subtracting the coordinates of the center point.
    for (int i = 0; i < points.size(); i++){
        
        GLfloat dist = glm::length(points[i]-center);
        max_dist = max(max_dist, dist);
        
        points[i].x -= center_x;
        points[i].y -= center_y;
        points[i].z -= center_z;

    }
    
    // Set the model matrix to an identity matrix.
    model = glm::mat4(1);
    
    // Uniformly scale all points by max distance
    //model = glm::scale(model, glm::vec3(10 /max_dist));

    // Set the color.
    //color = glm::vec3(1, 0, 0);

    // Generate a Vertex Array (VAO) and Vertex Buffer Object (VBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &nVBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO to the bound VAO, and store the point data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
    
    // Enable Vertex Attribute 0 to pass point data through to the shader
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    // nVBO
    glBindBuffer(GL_ARRAY_BUFFER, nVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);
    
    // Enable nVBO
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    // Generate EBO, bind the EBO to the bound VAO, and send the index data for triangles
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * triangles.size(), triangles.data(), GL_STATIC_DRAW);
    
    // Unbind the VBO/VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Geometry::~Geometry()
{
    // Delete the VBO EBO and the VAO.
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
}

void Geometry::draw(GLuint shader, glm::mat4 C, bool isRoot, glm::mat4 view, glm::mat4 projection)
{
    // Actiavte the shader program
    glUseProgram(shader);
    
    glm::mat4 toWorld = C * model;
    // Get the shader variable locations and send the uniform data to the shader
    //glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
    //glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader, "toWorld"), 1, GL_FALSE, glm::value_ptr(toWorld));
    //glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));
    //glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, glm::value_ptr(viewPos));
    
    // Send materials information to shader
    materials->sendMatToShader(shader);
    
    // Send point light info to shader
    pointLight->sendLightToShader(shader);
    
    // Bind the VAO
    glBindVertexArray(VAO);

    // Set point size
    //glPointSize(pointSize);

    // Draw the points
    //glDrawArrays(GL_POINTS, 0, points.size());
   
    // Draw the points using triangles, indexed with the EBO
    glDrawElements(GL_TRIANGLES, 3*triangles.size() , GL_UNSIGNED_INT, 0);
    
    // Unbind the VAO and shader program
    glBindVertexArray(0);
    glUseProgram(0);
}

void Geometry::update(glm::mat4 C){
    model = C * model;
}

void Geometry::ballRotate(glm::vec3 rotAxis, float rotAngle){
    model = glm::rotate(glm::mat4(1.0f), rotAngle, rotAxis) * model;
    //cout << glm::to_string(model) << std::endl;
    //model = glm::rotate(model, rotAngle, rotAxis);
}

void Geometry::adjust(float amount){
    //model = glm::scale(glm::mat4(1.0f), glm::vec3(amount))*model;
    //model = glm::rotate(glm::mat4(1.0f), amount, glm::vec3(1,0,0))*model;
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0,amount,0))*model;
}

void Geometry::translate(float x, float y, float z){
    model = glm::translate(glm::mat4(1.0f), glm::vec3(x,y,z))*model;
}
