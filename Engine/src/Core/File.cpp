#include "pch.h"
#include "File.h"

#include <fstream>
#include <sstream>

namespace Engine {

	std::string File::Read(const std::string& filepath)
	{
		std::fstream fileStream;
		fileStream.open(filepath, std::ios::in);
		GE_CORE_ASSERT(fileStream.is_open(), "Failed to open file");

		std::string content;
		if (fileStream.is_open()) {
			std::ostringstream ss;
			ss << fileStream.rdbuf();

			content = ss.str();

			fileStream.close();
		}

		return content;
	}

}
