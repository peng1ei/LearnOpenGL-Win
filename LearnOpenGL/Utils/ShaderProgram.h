#pragma once
#include <string>
#include "../CommonDefine.h"

namespace mogl {
	class ShaderProgram
	{
	public:
		static void UnUse();

	public:
		ShaderProgram(const std::string &vs_file, const std::string &fs_file);
		
		bool CompileAndLink();

		GLuint GetProgram() {
			return program_;
		}

		void Use();

		// set uniform value by name
		void SetBool(const std::string &name, bool value);
		void SetInt(const std::string &name, int value);
		void SetFloat(const std::string &name, float value);
		void SetVec2(const std::string &name, float v1, float v2);
		void SetVec3(const std::string &name, float v1, float v2, float v3);
		void SetVec4(const std::string &name, float v1, float v2, float v3, float v4);

	protected:
		GLint GetCompileStatus(GLenum shader_type, GLuint shader);
		GLint GetLinkStatus(GLuint shader);
		
	private:
		std::string vs_file_;
		std::string fs_file_;
		GLuint program_;
	};
}



