#pragma once

#include <string>

#include "abstract_block.hpp"

class block_factory
{
public:
    static const block_factory& instance();

    virtual ~block_factory() {}

    virtual abstract_block::ptr create(const std::string &block_name) const = 0;

};
