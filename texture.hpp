#pragma once

#include "OpenGL.h"

#include <glm/vec2.hpp>

struct texture
{
    GLuint id;
    glm::vec2 coords[4];
};
