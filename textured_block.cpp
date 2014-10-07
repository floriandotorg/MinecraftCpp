#include "textured_block.hpp"

#include <cstdio>

#include <glm/vec3.hpp>

#include "OpenGL.h"
#include "texture_manager.hpp"

textured_block::textured_block(const std::string &texture)
    : texture_top(texture_manager::instance().get_texture_for_face(texture, face::top))
    , texture_bottom(texture_manager::instance().get_texture_for_face(texture, face::bottom))
    , texture_north(texture_manager::instance().get_texture_for_face(texture, face::north))
    , texture_west(texture_manager::instance().get_texture_for_face(texture, face::west))
    , texture_south(texture_manager::instance().get_texture_for_face(texture, face::south))
    , texture_east(texture_manager::instance().get_texture_for_face(texture, face::east))
{ }

void textured_block::draw_top() const
{
    glBindTexture(GL_TEXTURE_2D, texture_top.id);

    glBegin(GL_POLYGON);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.5, 0.25);
    glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.25, 0.25);
    glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(0.25, 0.0);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
}

void textured_block::draw_bottom() const
{
    glBindTexture(GL_TEXTURE_2D, texture_bottom.id);

    glBegin(GL_POLYGON);
    glTexCoord2f(0.25, 0.25);
    glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(0.25, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(0.0, 0.25);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
}

void textured_block::draw_north() const
{
    glBindTexture(GL_TEXTURE_2D, texture_north.id);

    glBegin(GL_POLYGON);
    glTexCoord2f(0.25, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(0.25, 0.25);
    glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 0.25);
    glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
}

void textured_block::draw_west() const
{
    glBindTexture(GL_TEXTURE_2D, texture_west.id);

    glBegin(GL_POLYGON);
    glTexCoord2f(0.25, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(0.25, 0.25);
    glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 0.25);
    glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
}

void textured_block::draw_south() const
{ 
    glBindTexture(GL_TEXTURE_2D, texture_south.id);

    glBegin(GL_POLYGON);
    glTexCoord2f(0.25, 0.0);
    glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(0.25, 0.25);
    glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 0.25);
    glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();
}

void textured_block::draw_east() const
{
    glBindTexture(GL_TEXTURE_2D, texture_east.id);

    glBegin(GL_POLYGON);
    glTexCoord2f(0.25, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(0.25, 0.25);
    glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0.0, 0.25);
    glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 0.0);
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
