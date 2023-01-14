#pragma once
#include "Feature.hpp"

namespace Crisp::Core {
    class WindowManager : public Feature {
    public:
        WindowManager();
        ~WindowManager();

        void CreateWindow();
        void Cleanup();
        int GetFeatureID();
    };
}