#pragma once

#include <string>

#include <glm/vec3.hpp>

#include "OpenGL.h"
#include "texture.hpp"
#include "face.hpp"

class texture_manager
{
public:
    static texture_manager& instance();

    virtual texture get_texture_for_face(const std::string &name, face face) const = 0;

    virtual ~texture_manager() {};

};