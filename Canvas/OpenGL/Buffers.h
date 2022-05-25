#ifndef _CC_BUFFERS_H
#define _CC_BUFFERS_H

#include "Types.h"
#include <vector>

namespace cc
{
    class VertexBuffer
    {
    public:
        struct Layout
        {
            struct Element
            {
                uint32_t Type;
                uint32_t Count;
                uint32_t Size;
                uint32_t Normalize;
            };

            template<typename T>
            void AddElement(uint32_t count);

            std::vector<Element> Elements;
            int32_t Stride = 0;
        };

        VertexBuffer(const void* data, uint32_t count, uint32_t vertexSize);
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        VertexBuffer(VertexBuffer&& vb);
        VertexBuffer& operator=(VertexBuffer&& vb);

        void Bind() const;
        Layout& GetLayout();
        const Layout& GetLayout() const;
    private:
        uint32_t m_vboID;
        Layout m_layout;
    };

    class ElementBuffer
    {
    public:
        ElementBuffer(const void* data, uint32_t count, uint32_t elementSize = sizeof(uint32_t));
        ~ElementBuffer();

        ElementBuffer(const ElementBuffer&) = delete;
        ElementBuffer& operator=(const ElementBuffer&) = delete;

        ElementBuffer(ElementBuffer&& eb);
        ElementBuffer& operator=(ElementBuffer&& eb);

        void Bind() const;
        uint32_t GetCount() const;
    private:
        uint32_t m_eboID;
        uint32_t m_indexCount;
    };

    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;

        VertexArray(VertexArray&& va);
        VertexArray& operator=(VertexArray&& va);

        void Bind() const;
        void AddBuffer(const VertexBuffer& vb);
    private:
        uint32_t m_vaoID;
    };
}

#endif //_CC_BUFFERS_H
