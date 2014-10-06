#pragma once

#include <memory>

#include <boost/range/any_range.hpp>

class block;

class world
{
public:
	typedef boost::any_range<block, boost::forward_traversal_tag> block_range;

	world();
	~world();

	const block_range shown_blocks();

private:
	class impl;
	std::unique_ptr<impl> _m;

};
