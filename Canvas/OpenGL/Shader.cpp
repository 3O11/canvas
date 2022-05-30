#include "Shader.h"

#include "Matrix.h"

#include <glad/glad.h>
#include <vector>

namespace cc
{
    Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
        : m_shaderID(0)
    {
        m_shaderID = glCreateProgram();
        uint32_t vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        uint32_t fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(m_shaderID, vs);
        glAttachShader(m_shaderID, fs);
        glLinkProgram(m_shaderID);
        glValidateProgram(m_shaderID);

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    Shader::~Shader()
    {
        if (m_shaderID != 0)
        {
            glDeleteProgram(m_shaderID);
        }
    }

    Shader::Shader(Shader&& sh)
    {
        m_shaderID = sh.m_shaderID;
        m_locationCache = std::move(sh.m_locationCache);
        sh.m_shaderID = 0;
    }

    Shader& Shader::operator=(Shader&& sh)
    {
        m_shaderID = sh.m_shaderID;
        m_locationCache = std::move(sh.m_locationCache);
        sh.m_shaderID = 0;
        return *this;
    }

    void Shader::Bind() const
    {
        glUseProgram(m_shaderID);
    }

    void Shader::SetUniform1i(const std::string& name, int32_t value)
    {
        glUniform1i(getLocation(name), value);
    }

    void Shader::SetUniformMatrix4(const std::string& name, const Matrix4& matrix)
    {
        glUniformMatrix4fv(getLocation(name), 1, true, &matrix[0][0]);
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
            glGetShaderInfoLog(id, length, &length, &message[0]);
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
            int32_t location = glGetUniformLocation(m_shaderID, name.c_str());
            m_locationCache[name] = location;
            return location;
        }

        return m_locationCache[name];
    }
}
