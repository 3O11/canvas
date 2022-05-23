#include "Texture.h"

#include <glad/glad.h>

namespace cc
{
    Texture::Texture(const Image& image)
    {
        glGenTextures(1, &m_textureId);
        glBindTexture(GL_TEXTURE_2D, m_textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, image.Width(), image.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_textureId);
    }

    void Texture::Use(uint32_t slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
	    glBindTexture(GL_TEXTURE_2D, m_textureId);
    }
}
