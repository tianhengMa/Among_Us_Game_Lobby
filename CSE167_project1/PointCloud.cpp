#include "PointCloud.h"
#include <limits>
#include <stdio.h>
#include <float.h>
#include <math.h>


PointCloud::PointCloud(std::string objFilename, GLfloat pointSize) : pointSize(pointSize)
{
	/* 
	 * TODO: Section 2: Currently, all the points are hard coded below. 
	 * Modify this to read points from an obj file.
	 */

    // Initialize materials
    //materials = in_materials;
    
    // Initialize pointlight
    //pointLight = in_pointLight;
    
    // Intialize model switch to be 1 (1: normal, 0: phong)
    modelSwitch = 1;
    
    ifstream objFile(objFilename); // The obj file we are reading.
    //std::vector<glm::vec3> points;

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
                
                ss >> color.x >> color.y >> color.z;

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
                
                ss>>v2;
                triangle.y = stoi(v2.substr(0, v2.find("//")))-1;
                
                ss>>v3;
                triangle.z = stoi(v3.substr(0, v3.find("//")))-1;
                triangles.push_back(triangle);

            }
            
            else if (label == "vn"){
                glm::vec3 rgb;
                ss >>rgb.x >> rgb.y >> rgb.z;
        
                rgbs.push_back(rgb);
            }
        }
    }
    else
    {
        std::cerr << "Can't open the file " << objFilename << std::endl;
    }

    objFile.close();
    
	/*
	 * TODO: Section 4, you will need to normalize the object to fit in the
	 * screen. 
	 */
    
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
    model = glm::scale(model, glm::vec3(10 /max_dist));

	// Set the color. 
    color = glm::vec3(1, 0, 0);

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rgbs.size(), rgbs.data(), GL_STATIC_DRAW);
    
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

PointCloud::~PointCloud() 
{
	// Delete the VBO EBO and the VAO.
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
}

void PointCloud::draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader)
{
	// Actiavte the shader program 
	glUseProgram(shader);

	// Get the shader variable locations and send the uniform data to the shader 
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));
    
    // Send materials information to shader
    materials->sendMatToShader(shader);
    
    // Send point light info to shader
    pointLight->sendLightToShader(shader);
    
    // Send model and light switch to shader
    glUniform1i(glGetUniformLocation(shader, "modelSwitch"), modelSwitch);
    //glUniform1i(glGetUniformLocation(shader, "lightSwitch"), lightSwitch);
    
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

void PointCloud::update()
{
	// Spin the cube by 1 degree
	spin(0.1f);
}

void PointCloud::updatePointSize(GLfloat size) 
{
    pointSize = size;
}

void PointCloud::increasePointSize()
{
    pointSize += 1;
}

void PointCloud::decreasePointSize()
{
    pointSize -= 1;
}

void PointCloud::spin(float deg)
{
	// Update the model matrix by multiplying a rotation matrix
	model = model * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
}

void PointCloud::scale(double scale){
    if (scale > 0){
        model = glm::scale(glm::mat4(1.0f), glm::vec3(scale))*model;
        //model = glm::scale(model, glm::vec3(scale));
    }
}

void PointCloud::translate(glm::vec3 translation){
    model = glm::translate(model, translation);

}

void PointCloud::ballRotate(glm::vec3 rotAxis, float rotAngle){
    model = glm::rotate(glm::mat4(1.0f), rotAngle, rotAxis) * model;
    //model = glm::rotate(model, rotAngle, rotAxis);
}

void PointCloud::toggleModelSwitch(){
    modelSwitch = 1 - modelSwitch;
}
