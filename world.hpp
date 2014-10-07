#pragma once

#include <memory>

class world
{
public:
	world();
	~world();

    void init();

    void update(double dt);
    void draw() const;

private:
	class impl;
	std::unique_ptr<impl> _m;

};
