//
//  ParticleSystem.cpp
//  CSE167_project1
//
//  Created by Matthew Ma on 12/9/20.
//

#include "ParticleSystem.h"
ParticleSystem::ParticleSystem(glm::vec3 origin){
    for (int i = 0; i < MAX_PARTICLES; i++){
        glm::vec3 velocity = glm::vec3(rand() % 2);
        glm::vec3 position = origin + velocity;
        particles[i] = new Particle(position,velocity, PARTICLE_LIFE);
        position_data.push_back(position);
    }
    
    // Set the model matrix to an identity matrix.
    model = glm::mat4(1);
    
    // Set the color.
    color = glm::vec3(1, 0, 0);

    // Generate a Vertex Array (VAO) and Vertex Buffer Object (VBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO to the bound VAO, and store the point data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * position_data.size(), position_data.data(), GL_STATIC_DRAW);
    // Enable Vertex Attribute 0 to pass point data through to the shader
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    // Unbind the VBO/VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

ParticleSystem::~ParticleSystem(){
    // Delete the VBO and the VAO.
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void ParticleSystem::update(float deltaTime){
    // Update particle position
    for (int i = 0; i < MAX_PARTICLES; i++){
        position_data[i] = particles[i]->update(deltaTime);
    }
}

void ParticleSystem::draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader){
    // Actiavte the shader program
    glUseProgram(shader);

    // Get the shader variable locations and send the uniform data to the shader
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));

    // Bind the VAO
    glBindVertexArray(VAO);

    // Set point size
    glPointSize(10.0f);

    // Draw the points
    glDrawArrays(GL_POINTS, 0, position_data.size());

    // Unbind the VAO and shader program
    glBindVertexArray(0);
    glUseProgram(0);
}
