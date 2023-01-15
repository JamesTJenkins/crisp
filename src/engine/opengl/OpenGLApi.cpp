#include "OpenGLApi.hpp"
#include "../Helper.hpp"

namespace Crisp::Core {
    OpenGLApi::OpenGLApi() {
        Initialize();
    }

    void OpenGLApi::Initialize() {
        std::cout << "Initialized opengl" << std::endl;
    }

    void OpenGLApi::ClearScreen() {

    }

    void OpenGLApi::Draw() {

    }

    void OpenGLApi::Cleanup() {
        std::cout << "Opengl cleaned up" << std::endl;
    }

    int OpenGLApi::GetFeatureID() {
        return GetStringHash("OpenGLApi");
    }
}