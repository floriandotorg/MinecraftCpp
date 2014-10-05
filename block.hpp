#pragma once

#include <glm/vec3.hpp>

class block
{
public:
	enum material_t
	{
		grass = 1
	};

	glm::vec3 pos;
	material_t material;

	block(const glm::vec3 &&pos, material_t material);

	void draw() const;
};
