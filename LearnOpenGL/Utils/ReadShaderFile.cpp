#include "ReadShaderFile.h"
#include <iostream>
#include <fstream>
#include <memory>

namespace mogl {
	namespace utils {

		std::string ReadShaderFile::ReadShaderFromFile(const std::string &shader_file) {
			std::ifstream fs(shader_file);

			std::string line, content;
			while (std::getline(fs, line).good()) {
				if (line.empty()) continue;
				line.append("\n");
				content.append(line);
			}

			// TODO use std:move(content) ???
			return content;
		}
	}
}
