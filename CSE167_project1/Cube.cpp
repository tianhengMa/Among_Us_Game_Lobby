#include "Cube.h"
#include <iostream>
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//unsigned int Cube::cubemapTexture;

Cube::Cube(float size) 
{
	// Model matrix. Since the original size of the cube is 2, in order to
	// have a cube of some size, we need to scale the cube by size / 2.
	model = glm::scale(glm::vec3(size / 2.f)); 

	// The color of the cube. Try setting it to something else!
	color = glm::vec3(1.0f, 0.95f, 0.1f); 

	/*
	 * Cube indices used below.
	 *    4----7
     *   /|   /|
     *  0-+--3 |
     *  | 5--+-6
     *  |/   |/
     *  1----2
	 *
	 */

	// The 8 vertices of a cube.
    /*
	std::vector<glm::vec3> vertices
	{
		glm::vec3(-700, 700, 700),
		glm::vec3(-700, -700, 700),
		glm::vec3(700, -700, 700),
		glm::vec3(700, 700, 700),
		glm::vec3(-700, 700, -700),
		glm::vec3(-700, -700, -700),
		glm::vec3(700, -700, -700),
		glm::vec3(700, 700, -700)
	}; */
    std::vector<glm::vec3> vertices = {
        // positions
        glm::vec3(-128.0f,  128.0f, -128.0f),
        glm::vec3(-128.0f, -128.0f, -128.0f),
        glm::vec3(128.0f, -128.0f, -128.0f),
        glm::vec3(128.0f, -128.0f, -128.0f),
        glm::vec3(128.0f,  128.0f, -128.0f),
        glm::vec3(-128.0f,  128.0f, -128.0f),

        glm::vec3(-128.0f, -128.0f,  128.0f),
        glm::vec3(-128.0f, -128.0f, -128.0f),
        glm::vec3(-128.0f,  128.0f, -128.0f),
        glm::vec3(-128.0f,  128.0f, -128.0f),
        glm::vec3(-128.0f,  128.0f,  128.0f),
        glm::vec3(-128.0f, -128.0f,  128.0f),

        glm::vec3(128.0f, -128.0f, -128.0f),
        glm::vec3(128.0f, -128.0f,  128.0f),
        glm::vec3(128.0f,  128.0f,  128.0f),
        glm::vec3(128.0f,  128.0f,  128.0f),
        glm::vec3(128.0f,  128.0f, -128.0f),
        glm::vec3(128.0f, -128.0f, -128.0f),

        glm::vec3(-128.0f, -128.0f,  128.0f),
        glm::vec3(-128.0f,  128.0f,  128.0f),
        glm::vec3(128.0f,  128.0f,  128.0f),
        glm::vec3(128.0f,  128.0f,  128.0f),
        glm::vec3(128.0f, -128.0f,  128.0f),
        glm::vec3(-128.0f, -128.0f,  128.0f),

        glm::vec3(-128.0f,  128.0f, -128.0f),
        glm::vec3(128.0f,  128.0f, -128.0f),
        glm::vec3(128.0f,  128.0f,  128.0f),
        glm::vec3(128.0f,  128.0f,  128.0f),
        glm::vec3(-128.0f,  128.0f,  128.0f),
        glm::vec3(-128.0f,  128.0f, -128.0f),

        glm::vec3(-128.0f, -128.0f, -128.0f),
        glm::vec3(-128.0f, -128.0f,  128.0f),
        glm::vec3(128.0f, -128.0f, -128.0f),
        glm::vec3(128.0f, -128.0f, -128.0f),
        glm::vec3(-128.0f, -128.0f,  128.0f),
        glm::vec3(128.0f, -128.0f,  128.0f)
    };

	// Each ivec3(v1, v2, v3) define a triangle consists of vertices v1, v2 
	// and v3 in counter-clockwise order.
    /*
	std::vector<glm::ivec3> indices
	{
		// Front face.
		glm::ivec3(0, 1, 2),
		glm::ivec3(2, 3, 0),
		// Back face.
		glm::ivec3(7, 6, 5),
		glm::ivec3(5, 4, 7),
		// Right face.
		glm::ivec3(3, 2, 6),
		glm::ivec3(6, 7, 3),
		// Left face.
		glm::ivec3(4, 5, 1),
		glm::ivec3(1, 0, 4),
		// Top face.
		glm::ivec3(4, 0, 3),
		glm::ivec3(3, 7, 4),
		// Bottom face.
		glm::ivec3(1, 5, 6),
		glm::ivec3(6, 2, 1),
	}; */
    
    std::vector<glm::ivec3> indices
    {
        // Front face.
        glm::ivec3(0, 1, 2),
        glm::ivec3(3, 4, 5),
        // Back face.
        glm::ivec3(6, 7, 8),
        glm::ivec3(9, 10,11),
        // Right face.
        glm::ivec3(12, 13,14),
        glm::ivec3(15, 16, 17),
        // Left face.
        glm::ivec3(18, 19, 20),
        glm::ivec3(21, 22, 23),
        // Top face.
        glm::ivec3(24, 25, 26),
        glm::ivec3(27, 28, 29),
        // Bottom face.
        glm::ivec3(30, 31, 32),
        glm::ivec3(33, 34, 35),
    };

	// Generate a vertex array (VAO) and vertex buffer object (VBO).
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind to the VAO.
	glBindVertexArray(VAO);

	// Bind VBO to the bound VAO, and store the vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	// Enable Vertex Attribute 0 to pass the vertex data through to the shader
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	// Generate EBO, bind the EBO to the bound VAO, and send the index data
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * indices.size(), indices.data(), GL_STATIC_DRAW);
    
    // Initialize Skybox faces
    vector<string> skyBoxFaces
    {
        "/Users/tma2017/Senior/Q1/CSE167/project/CSE167_project1/CSE167_project1/skybox/right.jpg",
        "/Users/tma2017/Senior/Q1/CSE167/project/CSE167_project1/CSE167_project1/skybox/left.jpg",
        "/Users/tma2017/Senior/Q1/CSE167/project/CSE167_project1/CSE167_project1/skybox/top.jpg",
        "/Users/tma2017/Senior/Q1/CSE167/project/CSE167_project1/CSE167_project1/skybox/bottom.jpg",
        "/Users/tma2017/Senior/Q1/CSE167/project/CSE167_project1/CSE167_project1/skybox/front.jpg",
        "/Users/tma2017/Senior/Q1/CSE167/project/CSE167_project1/CSE167_project1/skybox/back.jpg"
    };
    
    cubemapTexture = loadCubemap(skyBoxFaces);
    
	// Unbind the VBO/VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Cube::~Cube()
{
	// Delete the VBO/EBO and the VAO.
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

unsigned int Cube::loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    // Bind the texture with cube map
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            cout << "Cubemap tex failed to load at path: " << faces[i] << endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void Cube::draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader)
{
	// Actiavte the shader program 
	glUseProgram(shader);
    glDepthMask(GL_FALSE);

	// Get the shader variable locations and send the uniform data to the shader 
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));

	// Bind the VAO
	glBindVertexArray(VAO);

    // Culling backface
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CW);
    glDisable(GL_CULL_FACE);
    
    // Bind the texture with cube map
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    
	// Draw the points using triangles, indexed with the EBO
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
    
    // Culling back to front face
    //glCullFace(GL_FRONT);
    
	// Unbind the VAO and shader program
	glBindVertexArray(0);
	glUseProgram(0);
}

void Cube::update()
{
	// Spin the cube by 1 degree.
	spin(0.1f);
}

void Cube::spin(float deg)
{
	// Update the model matrix by multiplying a rotation matrix
	//model = model * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Cube::ballRotate(glm::vec3 rotAxis, float rotAngle){
    model = glm::rotate(glm::mat4(1.0f), rotAngle, rotAxis) * model;
    //model = glm::rotate(model, rotAngle, rotAxis);
}

unsigned int Cube::getSkyboxTexture(){
    return cubemapTexture;
}


