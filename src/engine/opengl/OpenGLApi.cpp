#include "OpenGLApi.hpp"

#include <gl/glu.h>
#include <stdio.h>
#include <iostream>

#include "../FeatureManager.hpp"
#include "../WindowManager.hpp"
#include "../components/Camera.hpp"

namespace Crisp::Core {
    OpenGLApi::OpenGLApi() {}
    OpenGLApi::~OpenGLApi() {}

    // OpenGL initializes on window creation
    void OpenGLApi::Initialize() {}

    bool OpenGLApi::NewWindow(const char *title, int x, int y, int width, int height) {
        bool success = true;

        // Create window in window manager
        WindowManager *wm = FeatureManager::Get().GetFeature<WindowManager>();
        if (wm->NewWindow(title, x, y, width, height, SDL_WINDOW_OPENGL)) {
            // Get window
            SDL_Window *window = wm->GetWindow(wm->GetWindowCount() - 1);
            // Link to context
            OpenGLWindow openGLWindow(window);
            openGLWindows.push_back(openGLWindow);
        
            // OpenGL 3.1 core
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            // Init glew
            openGLWindow.gContext = SDL_GL_CreateContext(openGLWindow.window);
            if (openGLWindow.gContext == NULL) {
                std::cout << "OpenGL context cound not be created. SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            } else {
                glewExperimental = GL_TRUE;
                GLenum glewError = glewInit();
                if (glewError != GLEW_OK)
                    std::cout << "Error initializing glew. SDL Error: " << glewGetErrorString(glewError) << std::endl;

                // Vsync
                if (SDL_GL_SetSwapInterval(1) < 0)
                    std::cout << "Unable to set vsync. SDL Error: " << SDL_GetError() << std::endl;
            }

            std::cout << "Initialized opengl" << std::endl;
        } else {
            success = false;
        }

        return success;
    }

    void OpenGLApi::ClearScreen() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void OpenGLApi::Draw() {
        ClearScreen();
        
        // Get current camera rendering to screen
        Camera* mainCamera = Camera::GetMainCamera();
        // Check camera was successfully got
        if (mainCamera == nullptr) {
            //std::cout << "No camera is set to render" << std::endl;
            return;
        }

        // TEST
        glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
        glEnd();
        // ENDTEST
    }

    bool OpenGLApi::InitializeShader(ShaderImport &shader) {
        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        // Set vertex source code
        glShaderSource(vertex, 1, (char const *const *)shader.vertexShader.ReadBinaryData(), NULL);
        // Compile vertex shader
        glCompileShader(vertex);
        // Error checks
        GLint vShaderCompiled = GL_FALSE;
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &vShaderCompiled);
        if (vShaderCompiled != GL_TRUE) {
            std::cout << "Unable to compile vertex shader: " << vertex << std::endl;
            PrintShaderLog(vertex);
            return false;
        }

        // Create shader program and add to openGL shader list
        OpenGLShader openGLShader;
        openGLShaders.push_back(openGLShader);
        openGLShader.gProgramID = glCreateProgram();
        // Attach vertex shader to program
        glAttachShader(openGLShader.gProgramID, vertex);

        // Fragment
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        // Set fragment source code
        glShaderSource(fragment, 1, (char const *const *)shader.fragmentShader.ReadBinaryData(), NULL);
        // Compile fragment shader
        glCompileShader(fragment);
        // Error checks
        GLint fShaderCompiled = GL_FALSE;
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &fShaderCompiled);
        if (fShaderCompiled != GL_TRUE) {
            std::cout << "Unable to compile fragment shader: " << fragment << std::endl;
            PrintShaderLog(fragment);
            // Cleanup
            glDeleteShader(vertex);
            glDeleteProgram(openGLShader.gProgramID);
            openGLShader.gProgramID = 0;
            return false;
        }

        // Attach to program
        glAttachShader(openGLShader.gProgramID, fragment);
        // Link
        glLinkProgram(openGLShader.gProgramID);
        // Error check
        GLint programSuccess = GL_TRUE;
        glGetProgramiv(openGLShader.gProgramID, GL_LINK_STATUS, &programSuccess);
        if (programSuccess != GL_TRUE) {
            std::cout << "Error linking to program: " << openGLShader.gProgramID << std::endl;
            PrintProgramLog(openGLShader.gProgramID);
            // Cleanup
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            glDeleteProgram(openGLShader.gProgramID);
            openGLShader.gProgramID = 0;
            return false;
        }

        // Cleanup excess shader references
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return true;
    }

    void OpenGLApi::Cleanup() {
        // Clear shaders
        for (OpenGLShader shader : openGLShaders) {
            glDeleteProgram(shader.gProgramID);
        }

        // Clear gl context (windows will be cleared by window manager)
        for (OpenGLWindow window : openGLWindows) {
            SDL_GL_DeleteContext(window.gContext);
        }

        std::cout << "Opengl cleaned up" << std::endl;
    }

    // DEBUG

    void OpenGLApi::PrintProgramLog(GLuint program) {
        if (glIsProgram(program)) {
            // Log length
            int infoLogLength = 0;
            int maxLength = infoLogLength;

            // Get info string length
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // Allocate string
            char *infoLog = new char[maxLength];

            // Get info log
            glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);

            if (infoLogLength > 0)
                std::cout << infoLog << std::endl;

            // Deallocate string
            delete[] infoLog;
        } else {
            std::cout << "Name " << program << " is not a program" << std::endl;
        }
    }

    void OpenGLApi::PrintShaderLog(GLuint shader) {
        if (glIsShader(shader)) {
            // Log length
            int infoLogLength = 0;
            int maxLength = infoLogLength;

            // Get info string length
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // Allocate string
            char *infoLog = new char[maxLength];

            // Get info log
            glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);

            if (infoLogLength > 0)
                std::cout << infoLog << std::endl;

            // Deallocate string
            delete[] infoLog;
        } else {
            std::cout << "Name " << shader << " is not a shader" << std::endl;
        }
    }
}  // namespace Crisp::Core