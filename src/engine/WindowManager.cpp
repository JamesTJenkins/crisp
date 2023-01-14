#include "WindowManager.hpp"
#include "Helper.hpp"

namespace Crisp::Core {
    WindowManager::WindowManager() {}
    WindowManager::~WindowManager() {}

    void WindowManager::CreateWindow() {

    }

    void WindowManager::Cleanup() {

    }

    int WindowManager::GetFeatureID() {
        return GetStringHash("WindowManager");
    }
}