#include "Buffers.h"

#include <glad/glad.h>
#include <utility>

namespace cc
{
    template <>
    void VertexBuffer::Layout::AddElement<Float>(uint32_t count)
    {
        Elements.push_back({ GL_FLOAT, count, sizeof(Float), GL_FALSE });
        Stride += count * sizeof(Float);
    }

    template <>
    void VertexBuffer::Layout::AddElement<uint32_t>(uint32_t count)
    {
        Elements.push_back({ GL_UNSIGNED_INT, count, sizeof(uint32_t), GL_FALSE });
        Stride += count * sizeof(uint32_t);
    }


    VertexBuffer::VertexBuffer(const void* data, uint32_t count, uint32_t vertexSize)
        : m_vboID(0)
    {
        glGenBuffers(1, &m_vboID);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
        glBufferData(GL_ARRAY_BUFFER, count * vertexSize, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        if (m_vboID != 0)
        {
            glDeleteBuffers(1, &m_vboID);
        }
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& vb)
    {
        m_vboID = vb.m_vboID;
        m_layout = std::move(vb.m_layout);
        vb.m_vboID = 0;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vb)
    {
        m_vboID = vb.m_vboID;
        m_layout = std::move(vb.m_layout);
        vb.m_vboID = 0;
        return *this;
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    }

    VertexBuffer::Layout& VertexBuffer::GetLayout()
    {
        return m_layout;
    }

    const VertexBuffer::Layout& VertexBuffer::GetLayout() const
    {
        return m_layout;
    }


    ElementBuffer::ElementBuffer(const void* data, uint32_t count, uint32_t elementSize)
        : m_eboID(0), m_indexCount(count)
    {
        glGenBuffers(1, &m_eboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * elementSize, data, GL_STATIC_DRAW);
    }

    ElementBuffer::~ElementBuffer()
    {
        if (m_eboID != 0)
        {
            glDeleteBuffers(1, &m_eboID);
        }
    }

    ElementBuffer::ElementBuffer(ElementBuffer&& eb)
    {
        m_eboID = eb.m_eboID;
        m_indexCount = eb.m_indexCount;
        m_eboID = 0;
    }

    ElementBuffer& ElementBuffer::operator=(ElementBuffer&& eb)
    {
        m_eboID = eb.m_eboID;
        m_indexCount = eb.m_indexCount;
        m_eboID = 0;
        return *this;
    }

    void ElementBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
    }

    uint32_t ElementBuffer::GetCount() const
    {
        return m_indexCount;
    }

    VertexArray::VertexArray()
        : m_vaoID(0)
    {
        glGenVertexArrays(1, &m_vaoID);
    }

    VertexArray::~VertexArray()
    {
        if(m_vaoID != 0)
        {
            glDeleteVertexArrays(1, &m_vaoID);
        }
    }

    VertexArray::VertexArray(VertexArray&& va)
    {
        m_vaoID = va.m_vaoID;
        va.m_vaoID = 0;
    }

    VertexArray& VertexArray::operator=(VertexArray&& va)
    {
        m_vaoID = va.m_vaoID;
        va.m_vaoID = 0;
        return *this;
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_vaoID);
    }

    void VertexArray::AddBuffer(const VertexBuffer& vb)
    {
        Bind();
        vb.Bind();
        uint32_t i = 0, offset = 0;
        for ( auto&& [ Type, Count, Size, Normalize ] : vb.GetLayout().Elements )
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, Count, Type, Normalize, vb.GetLayout().Stride, reinterpret_cast<const void *>(offset));

            ++i;
            offset += Count * Size;
        }
    }
}
