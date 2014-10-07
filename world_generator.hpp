#pragma once

#include <memory>

#include <boost/range/any_range.hpp>

#include <glm/vec2.hpp>

#include "world_block.hpp"

class world_generator
{
public:
    typedef boost::any_range<world_block, boost::single_pass_traversal_tag> world_block_range;

    world_generator(int seed);
    ~world_generator();

    world_block_range generate(glm::vec2 origin, glm::vec2 size);

private:
    class impl;
    std::unique_ptr<impl> _m;
};
