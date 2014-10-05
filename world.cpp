#include "world.hpp"

#include <utility>

#include <boost/range/algorithm/find_if.hpp>

#include "block.hpp"

class world::impl
{
public:
	impl();

	const world::block_container& shown_blocks();

private:
	void generate();
	void place_block(const block &&block);
	void remove_block(const glm::vec3 &pos);
	
	block_container blocks;
};

world::impl::impl()
{
	generate();
}

void world::impl::place_block(const block &&block)
{
	blocks.push_back(std::move(block));
}

void world::impl::remove_block(const glm::vec3 &pos)
{
	blocks.erase(boost::range::find_if(blocks, [pos](const block &block){ return block.pos == pos; }));
}

const world::block_container& world::impl::shown_blocks()
{
	return blocks;
}

void world::impl::generate()
{
	for (int x = -5; x < 5; ++x)
	{
		for (int z = -5; z < 5; ++z)
		{
			place_block(block(glm::vec3(x, 0, z), block::grass));
		}
	}

	remove_block(glm::vec3(1, 0, 1));
}

///

world::world()
	: m(new impl())
{ }

world::~world()
{ }

const world::block_container& world::shown_blocks()
{
	return m->shown_blocks();
}
