#ifndef _CC_SHADER_H
#define _CC_SHADER_H

#include "Types.h"

#include <string>
#include <unordered_map>

namespace cc
{
    class Shader
    {
    public:
        Shader(const std::string& vertexShader, const std::string& fragmentShader);

        Shader(const Shader& shader) = delete;
        Shader& operator=(const Shader& shader) = delete;
        
        ~Shader();

        void Use() const;

        void SetUniform1i(const std::string& name, int32_t value);
    private:
        uint32_t compileShader(uint32_t shaderType, const std::string& source);
        int32_t getLocation(const std::string& name);

        uint32_t m_shaderId;
        std::unordered_map<std::string, int32_t> m_locationCache;
    };
}

#endif //_CC_SHADER_H
