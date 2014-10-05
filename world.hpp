#pragma once

#include <list>
#include <memory>

class block;

class world
{
public:
	typedef std::list<block> block_container;

	world();
	~world();

	const block_container& shown_blocks();

private:
	class impl;
	std::unique_ptr<impl> m;

};
