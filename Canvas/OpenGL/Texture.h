#ifndef _CC_TEXTURE_H
#define _CC_TEXTURE_H

#include "Image.h"  

namespace cc
{
    class Texture
    {
    public:
        Texture(const Image& image);
        ~Texture();

        Texture(const Texture& texture) = delete;
        Texture& operator=(const Texture& texture) = delete;

        Texture(Texture&& tx);
        Texture& operator=(Texture&& tx);

        void Bind(uint32_t slot = 0);
    private:
        uint32_t m_textureID;
    };
}

#endif //_CC_TEXTURE_H
