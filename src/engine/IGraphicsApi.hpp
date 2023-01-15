#pragma once
#include "Feature.hpp"

namespace Crisp::Core {
    class IGraphicsApi : public Feature {
    public:
        virtual void Initialize() = 0;
        virtual void ClearScreen() = 0;
        virtual void Draw() = 0;

        virtual void Cleanup() = 0;
        virtual int GetFeatureID() = 0;
    };
}