#include "textured_block.hpp"

#include <cstdio>

#include <glm/vec3.hpp>

#include "OpenGL.h"
#include "texture_manager.hpp"

textured_block::textured_block(const std::string &texture)
    : texture_top(texture_manager::instance().get_texture(texture))
    , texture_bottom(texture_manager::instance().get_texture(texture))
    , texture_north(texture_manager::instance().get_texture(texture))
    , texture_west(texture_manager::instance().get_texture(texture))
    , texture_south(texture_manager::instance().get_texture(texture))
    , texture_east(texture_manager::instance().get_texture(texture))
{ }

void textured_block::draw_top() const
{
    glBindTexture(GL_TEXTURE_2D, texture_top.id);

    glBegin(GL_POLYGON);
    glTexCoord2f(texture_top.coords[0].x, texture_top.coords[0].y);
    glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(texture_top.coords[1].x, texture_top.coords[1].y);
    glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(texture_top.coords[2].x, texture_top.coords[2].y);
    glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(texture_top.coords[3].x, texture_top.coords[3].y);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
}

void textured_block::draw_bottom() const
{
    glBindTexture(GL_TEXTURE_2D, texture_bottom.id);

    glBegin(GL_POLYGON);
    glTexCoord2f(texture_bottom.coords[0].x, texture_bottom.coords[0].y);
    glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(texture_bottom.coords[1].x, texture_bottom.coords[1].y);
    glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(texture_bottom.coords[2].x, texture_bottom.coords[2].y);
    glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(texture_bottom.coords[3].x, texture_bottom.coords[3].y);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
}

void textured_block::draw_north() const
{
    glBindTexture(GL_TEXTURE_2D, texture_north.id);

    glBegin(GL_POLYGON);
    glTexCoord2f(texture_north.coords[0].x, texture_north.coords[0].y);
    glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(texture_north.coords[1].x, texture_north.coords[1].y);
    glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(texture_north.coords[2].x, texture_north.coords[2].y);
    glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(texture_north.coords[3].x, texture_north.coords[3].y);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
}

void textured_block::draw_west() const
{
    glBindTexture(GL_TEXTURE_2D, texture_west.id);

    glBegin(GL_POLYGON);
    glTexCoord2f(texture_west.coords[0].x, texture_west.coords[0].y);
    glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(texture_west.coords[1].x, texture_west.coords[1].y);
    glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(texture_west.coords[2].x, texture_west.coords[2].y);
    glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(texture_west.coords[3].x, texture_west.coords[3].y);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
}

void textured_block::draw_south() const
{ 
    glBindTexture(GL_TEXTURE_2D, texture_south.id);

    glBegin(GL_POLYGON);
    glTexCoord2f(texture_south.coords[0].x, texture_south.coords[0].y);
    glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(texture_south.coords[1].x, texture_south.coords[1].y);
    glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(texture_south.coords[2].x, texture_south.coords[2].y);
    glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(texture_south.coords[3].x, texture_south.coords[3].y);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();
}

void textured_block::draw_east() const
{
    glBindTexture(GL_TEXTURE_2D, texture_east.id);

    glBegin(GL_POLYGON);
    glTexCoord2f(texture_east.coords[0].x, texture_east.coords[0].y);
    glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(texture_east.coords[1].x, texture_east.coords[1].y);
    glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(texture_east.coords[2].x, texture_east.coords[2].y);
    glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(texture_east.coords[3].x, texture_east.coords[3].y);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();
}

void textured_block::draw(const glm::vec3 &pos) const
{
	glPushMatrix();

    glTranslatef(pos.x, pos.y, pos.z);

    draw_top();
    draw_bottom();
    draw_north();
    draw_west();
    draw_south();
    draw_east();

	glPopMatrix();
}
