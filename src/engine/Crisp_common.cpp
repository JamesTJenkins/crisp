#include "Crisp_common.hpp"
#include <fstream>

namespace Crisp::Core {
    const char* BinaryDataImport::ReadBinaryData() {
        std::ifstream file(path, std::ios::ate | std::ios::binary);

		if (!file.is_open())
			throw std::runtime_error("Failed to read file.");

		size_t fileSize = (size_t)file.tellg();
		char* buffer = new char[fileSize];

		file.seekg(0);
		file.read(buffer, fileSize);

		file.close();

		return buffer;
	}
}