#include "block_factory.hpp"

#include <memory>

#include "texture_manager.hpp"
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
    if (block_name == "grass")
    {
        std::shared_ptr<textured_block> block(new textured_block("grass"));
        block->texture_top = texture_manager::instance().get_texture("grass.top");
        block->texture_bottom = texture_manager::instance().get_texture("grass.bottom");
        return block;
    }
    else
    {
        return abstract_block::ptr(new textured_block(block_name));
    }
}
