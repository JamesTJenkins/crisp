#pragma once
#include "Feature.hpp"

namespace Crisp::Core {
    class SDL2 : public Feature {
    public:
        SDL2();
        ~SDL2();

        void Initialize();
        void Cleanup();
        int GetFeatureID();
    };
}