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
        ~Shader();

        Shader(const Shader& shader) = delete;
        Shader& operator=(const Shader& shader) = delete;

        Shader(Shader&& sh);
        Shader& operator=(Shader&& sh);

        void Bind() const;

        void SetUniform1i(const std::string& name, int32_t value);
    private:
        uint32_t compileShader(uint32_t shaderType, const std::string& source);
        int32_t getLocation(const std::string& name);

        uint32_t m_shaderID;
        std::unordered_map<std::string, int32_t> m_locationCache;
    };
}

#endif //_CC_SHADER_H
