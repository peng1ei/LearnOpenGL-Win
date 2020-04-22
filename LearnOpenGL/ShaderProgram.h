#pragma once
#include <string>
#include "CommonDefine.h"

namespace mogl {
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string &vs_file, const std::string &fs_file);
		
		bool CompileAndLink();

		GLuint GetProgram() {
			return program_;
		}

	protected:
		GLint GetCompileStatus(GLenum shader_type, GLuint shader);
		GLint GetLinkStatus(GLuint shader);
		
	private:
		std::string vs_file_;
		std::string fs_file_;
		GLuint program_;
	};
}



