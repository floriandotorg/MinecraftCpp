#include "block_factory.hpp"

#include "textured_block.hpp"

class block_factory_impl : public block_factory
{
public:
    abstract_block::ptr create(const std::string &block_name) const;
};

const block_factory& block_factory::instance()
{
    static std::unique_ptr<block_factory> instance(new block_factory_impl());
    return *instance;
}

//////

abstract_block::ptr block_factory_impl::create(const std::string &block_name) const
{
    return abstract_block::ptr(new textured_block(block_name));
}
