#pragma once
#include "Feature.hpp"
#include "Material.hpp"

namespace Crisp::Core {
    class IGraphicsApi : public Feature {
    public:
        virtual void Initialize() = 0;
        virtual bool NewWindow(const char* title, int x, int y, int width, int height) = 0;

        virtual void ClearScreen() = 0;
        virtual void Draw() = 0;

        virtual bool InitializeShader(ShaderImport& shader) = 0;

        virtual void Cleanup() = 0;
        virtual int GetFeatureID() = 0;
    };
}