#pragma once

#include <string>

#include <glm/vec3.hpp>

#include "OpenGL.h"
#include "texture.hpp"

class texture_manager
{
public:
    static texture_manager& instance();

    virtual texture get_texture(const std::string &name) const = 0;

    virtual ~texture_manager() {};

};