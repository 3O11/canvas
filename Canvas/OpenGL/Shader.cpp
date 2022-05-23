#include "Shader.h"

#include <glad/glad.h>
#include <vector>

namespace cc
{
    Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
        : m_shaderId(0)
    {
        m_shaderId = glCreateProgram();
        uint32_t vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        uint32_t fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(m_shaderId, vs);
        glAttachShader(m_shaderId, fs);
        glLinkProgram(m_shaderId);
        glValidateProgram(m_shaderId);

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    Shader::~Shader()
    {
        if (m_shaderId != 0)
        {
            glDeleteProgram(m_shaderId);
        }
    }

    void Shader::Use() const
    {
        glUseProgram(m_shaderId);
    }

    void Shader::SetUniform1i(const std::string& name, int32_t value)
    {
        glUniform1i(getLocation(name), value);
    }

    uint32_t Shader::compileShader(uint32_t shaderType, const std::string& source)
    {
        uint32_t id = glCreateShader(shaderType);
        const char * rawSource = source.c_str();
        glShaderSource(id, 1, &rawSource, nullptr);
        glCompileShader(id);

        int32_t result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (!result)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> message;
            message.resize(length);
            printf("%s", message.data());
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    int32_t Shader::getLocation(const std::string& name)
    {
        if (!m_locationCache.contains(name))
        {
            int32_t location = glGetUniformLocation(m_shaderId, name.c_str());
            m_locationCache[name] = location;
            return location;
        }

        return m_locationCache[name];
    }
}
