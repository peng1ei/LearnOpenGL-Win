#ifndef __LEARNOPENGL_READ_SHADER_FILE_H__
#define __LEARNOPENGL_READ_SHADER_FILE_H__
#include <string>

namespace mogl {
	
	namespace utils {

		class ReadShaderFile {
		public:
			static std::string ReadShaderFromFile(const std::string &shader_file);
		};
	}	
}

#endif
