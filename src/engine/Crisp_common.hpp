#include <string>

namespace Crisp::Core {
    struct BinaryDataImport {
        std::string path;
        
        const char* ReadBinaryData();
    };
}