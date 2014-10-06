#include "world.hpp"

#include <list>
#include <utility>

#include <boost/range/algorithm/find_if.hpp>

#include "block.hpp"

class world::impl
{
public:
	impl();

	const world::block_range shown_blocks();

private:
	typedef std::list<block> block_container;

	void generate();
	void place_block(block &&block);
	void remove_block(const glm::vec3 &pos);
	
	block_container _blocks;
};

world::impl::impl()
{
	generate();
}

void world::impl::place_block(block &&block)
{
    _blocks.push_back(std::move(block));
}

void world::impl::remove_block(const glm::vec3 &pos)
{
    _blocks.erase(boost::range::find_if(_blocks, [pos](const block &block){ return block.pos() == pos; }));
}

const world::block_range world::impl::shown_blocks()
{
    return _blocks;
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
	place_block(block(glm::vec3(1, 0, 1), block::stone));

	place_block(block(glm::vec3(2, 1, 2), block::bricks));

	place_block(block(glm::vec3(-3, 1, -1), block::sand));
}

///

world::world()
	: _m(new impl())
{ }

world::~world()
{ }

const world::block_range world::shown_blocks()
{ return _m->shown_blocks(); }
