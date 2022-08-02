#include "Texture.h"

#include <glad/glad.h>

namespace cc
{
    Texture::Texture(const Image& image)
    {
        if (image.Width() == 0 || image.Height() == 0)
        {
            m_textureID = 0;
            return;
        }

        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, image.Width(), image.Height(), 0, GL_RGBA, GL_FLOAT, &image[0]);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_textureID);
    }

    Texture::Texture(Texture&& tx) noexcept
    {
        m_textureID = tx.m_textureID;
        tx.m_textureID = 0;
    }

    Texture& Texture::operator=(Texture&& tx) noexcept
    {
        if (m_textureID)
        {
            glDeleteTextures(1, &m_textureID);
        }

        m_textureID = tx.m_textureID;
        tx.m_textureID = 0;
        return *this;
    }

    void Texture::Bind(uint32_t slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
	    glBindTexture(GL_TEXTURE_2D, m_textureID);
    }
}
