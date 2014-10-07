#pragma once

#include <memory>

#include <glm/vec3.hpp>

class abstract_block
{
public:
    typedef std::shared_ptr<abstract_block> ptr;

    virtual ~abstract_block() {}

    virtual void update(double dt) {}
    virtual void draw(const glm::vec3 &pos) const = 0;
};
