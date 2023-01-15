#pragma once
#include "../IGraphicsApi.hpp"

namespace Crisp::Core {
    class OpenGLApi : public IGraphicsApi {
    public:
        OpenGLApi();

        void Initialize();
        void ClearScreen();
        void Draw();

        void Cleanup();
        int GetFeatureID();
    };
}