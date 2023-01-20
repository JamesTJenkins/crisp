#pragma once
#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <iostream>

namespace Crisp::Core {
    static void PrintProgramLog(GLuint program) {
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

    static void PrintShaderLog(GLuint shader) {
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
}