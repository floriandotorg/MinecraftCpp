#pragma once

#include <memory>

#include <glm/vec3.hpp>

class block
{
public:
	enum material_t
	{
		grass = 1,
		stone,
		bricks,
		sand
	};

	block(const glm::vec3 &&pos, material_t material);
    block(block &&block);
    ~block();

    const glm::vec3& pos() const;

	void draw() const;

private:
	class impl;
	std::unique_ptr<impl> _m;
};
