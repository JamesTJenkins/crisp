#pragma once
#include "Import.hpp"

namespace Crisp::Core {
    class IGraphicsApi {
    public:
        virtual ~IGraphicsApi() {};

        virtual void Initialize() = 0;
        virtual bool NewWindow(const char* title, int x, int y, int width, int height) = 0;

        virtual void ClearScreen() = 0;
        virtual void Draw() = 0;

        virtual void Cleanup() = 0;
    };
}