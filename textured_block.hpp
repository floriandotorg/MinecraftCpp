#pragma once

#include <string>

#include <glm/vec3.hpp>

#include "abstract_block.hpp"
#include "texture.hpp"

class textured_block : public abstract_block
{
public:
    textured_block(const std::string &texture);

    virtual void draw(const glm::vec3 &pos) const;

    virtual void draw_top() const;
    virtual void draw_bottom() const;
    virtual void draw_north() const;
    virtual void draw_west() const;
    virtual void draw_south() const;
    virtual void draw_east() const;

    texture texture_top;
    texture texture_bottom;
    texture texture_north;
    texture texture_west;
    texture texture_south;
    texture texture_east;
};
