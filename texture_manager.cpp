#include "texture_manager.hpp"

#include <memory>
#include <map>

class texture_manager_impl : public texture_manager
{
public:
    texture_manager_impl();

    virtual texture get_texture(const std::string &name) const;

private:
    typedef std::map< std::string, texture > texture_map;

    GLuint loadBMP_custom(const char * imagepath);

    texture_map _texture_map;
};

texture_manager& texture_manager::instance()
{
    static std::unique_ptr<texture_manager> instance(new texture_manager_impl());
    return *instance;
}

texture_manager_impl::texture_manager_impl()
{
    GLuint texture_id = loadBMP_custom("texture.bmp");

    _texture_map.insert(texture_map::value_type("grass.top", { texture_id, { glm::vec2(0.5, 0.0), glm::vec2(0.5, 0.25), glm::vec2(0.25, 0.25), glm::vec2(0.25, 0.0) } }));
    _texture_map.insert(texture_map::value_type("grass.bottom", { texture_id, { glm::vec2(0.25, 0.25), glm::vec2(0.25, 0.5), glm::vec2(0.0, 0.5), glm::vec2(0.0, 0.25) } }));
    _texture_map.insert(texture_map::value_type("grass", { texture_id, { glm::vec2(0.25, 0.0), glm::vec2(0.25, 0.25), glm::vec2(0.0, 0.25), glm::vec2(0.0, 0.0) } }));

    _texture_map.insert(texture_map::value_type("smooth_stone_bricks", { texture_id, { glm::vec2(0.75, 0.25), glm::vec2(0.75, 0.5), glm::vec2(0.5, 0.5), glm::vec2(0.5, 0.25) } }));
    
    _texture_map.insert(texture_map::value_type("sand", { texture_id, { glm::vec2(0.5, 0.25), glm::vec2(0.5, 0.5), glm::vec2(0.25, 0.5), glm::vec2(0.25, 0.25) } }));
    
    _texture_map.insert(texture_map::value_type("bricks", { texture_id, { glm::vec2(0.75, 0.0), glm::vec2(0.75, 0.25), glm::vec2(0.5, 0.25), glm::vec2(0.5, 0.0) } }));

}

GLuint texture_manager_impl::loadBMP_custom(const char * imagepath)
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
    GLuint textureID = 0;
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

texture texture_manager_impl::get_texture(const std::string &name) const
{
    return _texture_map.at(name);
}