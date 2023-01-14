#pragma once
#include <iostream>

namespace Crisp::Core {
    static int GetStringHash(std::string value) {
        return std::hash<std::string>{}(value);
    }
}