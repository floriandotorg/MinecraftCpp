#pragma once

#include <glm/vec3.hpp>

#include "abstract_block.hpp"

struct world_block
{
    abstract_block::ptr block;
    glm::vec3 pos;
};
