#include "block.hpp"

#include <cstdio>

#include <glm/vec3.hpp>

#include "OpenGL.h"

GLuint loadBMP_custom(const char * imagepath)
{
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char * data;

    // Open the file
    FILE * file = fopen(imagepath, "rb");
    if (!file)                              { printf("Image could not be opened\n"); return 0; }

    if (fread(header, 1, 54, file) != 54){ // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return false;
    }

    if (header[0] != 'B' || header[1] != 'M'){
        printf("Not a correct BMP file\n");
        return 0;
    }

    // Read ints from the byte array
    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

    // Create a buffer
    data = new unsigned char[imageSize];

    // Read the actual data from the file into the buffer
    fread(data, 1, imageSize, file);

    //Everything is in memory now, the file can be closed
    fclose(file);

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return textureID;
}

GLuint Texture()
{
    static GLuint texture = loadBMP_custom("texture.bmp");
    return texture;
}

class block::impl
{
public:
	impl(const glm::vec3 &&pos, material_t material);

	void draw() const;

    const glm::vec3& pos() const;

private:
	glm::vec3 _pos;
	material_t _material;
};

block::block(const glm::vec3 &&pos, material_t material)
    : _m(new impl(std::move(pos), material))
{ }

block::block(block &&block)
    : _m(std::move(block._m))
{ }

block::~block()
{ }

void block::draw() const
{ _m->draw(); }

const glm::vec3& block::pos() const
{ return _m->pos(); }

//////

block::impl::impl(const glm::vec3 &&pos, material_t material)
    : _pos(pos)
    , _material(material)
{ }

const glm::vec3& block::impl::pos() const
{ return _pos; }

void block::impl::draw() const
{
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, Texture());

    glTranslatef(_pos.x, _pos.y, _pos.z);

	//Multi-colored side - FRONT
	glBegin(GL_POLYGON);
	glTexCoord2f(0.25, 0.0);
	/*glColor3f( 1.0, 0.0, 0.0 );*/     glVertex3f(0.5, -0.5, -0.5);      // P1 is red
	glTexCoord2f(0.25, 0.25);
	/*glColor3f( 0.0, 1.0, 0.0 );*/     glVertex3f(0.5, 0.5, -0.5);      // P2 is green
	glTexCoord2f(0.0, 0.25);
	/*glColor3f( 0.0, 0.0, 1.0 );*/     glVertex3f(-0.5, 0.5, -0.5);      // P3 is blue
	glTexCoord2f(0.0, 0.0);
	/*glColor3f( 1.0, 0.0, 1.0 );*/     glVertex3f(-0.5, -0.5, -0.5);      // P4 is purple
	glEnd();

	// White side - BACK
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

	// Purple side - RIGHT
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

	// Green side - LEFT
	glBegin(GL_POLYGON);
	//glColor3f(   0.0,  1.0,  0.0 );
	glTexCoord2f(0.25, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(0.25, 0.25);
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(0.0, 0.25);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	//glColor3f(   0.0,  0.0,  1.0 );
	glTexCoord2f(0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.5, 0.25);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.25, 0.25);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.25, 0.0);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// Red side - BOTTOM
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

	glPopMatrix();
}
