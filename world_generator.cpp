#include "world_generator.hpp"

#include <vector>

#include "block_factory.hpp"

class world_generator::impl
{
public:
    impl(int seed);

    world_block_range generate(glm::vec2 origin, glm::vec2 size);
};

world_generator::world_generator(int seed)
    : _m(new impl(seed))
{ }

world_generator::~world_generator()
{ }

world_generator::world_block_range world_generator::generate(glm::vec2 origin, glm::vec2 size)
{ return _m->generate(origin, size); }

////

world_generator::impl::impl(int seed)
{ }

world_generator::world_block_range world_generator::impl::generate(glm::vec2 origin, glm::vec2 size)
{
    const block_factory &block_factory = block_factory::instance();
    static std::vector<world_block> result;
    result.reserve((static_cast<unsigned int>(size.x*size.y)));

    for (int x = static_cast<int>(origin.x); x < origin.x + size.x; ++x)
    {
        for (int z = static_cast<int>(origin.y); z < origin.y + size.y; ++z)
        {
            result.push_back({ block_factory.create("sand"), glm::vec3(x, 0, z) });
        }
    }

    return result;
}
