#pragma once
#include "Crisp_common.hpp"

namespace Crisp::Core {
    struct ShaderImport {
        BinaryDataImport vertexShader;
        BinaryDataImport fragmentShader;

        ShaderImport(std::string vertexPath, std::string fragmentPath) {
            vertexShader.path = vertexPath;
            fragmentShader.path = fragmentPath;
        }
    };
}