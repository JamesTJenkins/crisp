#pragma once
#include "Material.hpp"

namespace Crisp::Core {
    class IGraphicsApi {
    public:
        virtual void Initialize() = 0;
        virtual bool NewWindow(const char* title, int x, int y, int width, int height) = 0;

        virtual void ClearScreen() = 0;
        virtual void Draw() = 0;

        virtual void AddShader(ShaderImport& shader) = 0;
        virtual void Cleanup() = 0;
    };
}