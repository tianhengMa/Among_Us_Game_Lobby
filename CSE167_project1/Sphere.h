#ifndef _SPHERE_H_
#define _SPHERE_H_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object.h"

class Sphere
{
    public:
        GLuint shader;
        glm::mat4 model;
    
        GLuint vao = 0, vbo = 0, vbo_n = 0, ebo = 0;
        glm::vec3 _minVal, _maxVal, _center;

        int stackCount = 40;
        int sectorCount = 40;
        int numsToDraw;
        Sphere();
        void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader, unsigned int skyboxTexture);
};

#endif
