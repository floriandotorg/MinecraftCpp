#include "world.hpp"

#include <list>

#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/for_each.hpp>

#include "world_block.hpp"
#include "world_generator.hpp"

class world::impl
{
public:
    impl();

    void init();

    void update(double dt);
    void draw() const;

private:
    typedef std::list<world_block> block_container;

    void place_block(const world_block &&world_block);
	void remove_block(const abstract_block &block);
	
	block_container _blocks;
    world_generator _world_generator;
};

world::impl::impl()
    : _world_generator(42)
{ }

void world::impl::init()
{
    boost::for_each(_world_generator.generate(glm::vec2(-5, -5), glm::vec2(10, 10)), [this](world_block world_block) {
        this->place_block(std::move(world_block));
    });
}

void world::impl::place_block(const world_block &&world_block)
{
    _blocks.push_back(std::move(world_block));
}

void world::impl::remove_block(const abstract_block &block)
{
    const abstract_block *block_addr = &block;
    _blocks.erase(boost::range::find_if(_blocks, [block_addr](const world_block &world_block){ return &*world_block.block == block_addr; }));
}

void world::impl::update(double dt)
{
    boost::for_each(_blocks, [dt](const world_block &world_block) { world_block.block->update(dt); } );
}

void world::impl::draw() const
{
    boost::for_each(_blocks, [](const world_block &world_block) {
        world_block.block->draw(world_block.pos);
    });
}

///

world::world()
	: _m(new impl())
{ }

world::~world()
{ }

void world::update(double dt)
{ _m->update(dt); }

void world::draw() const
{ _m->draw(); }

void world::init() 
{ _m->init(); }
