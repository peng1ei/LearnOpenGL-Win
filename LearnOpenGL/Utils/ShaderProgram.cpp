#include "ShaderProgram.h"
#include "ReadShaderFile.h"

namespace mogl {

	ShaderProgram::ShaderProgram(const std::string &vs_file, const std::string &fs_file)
		: vs_file_(vs_file),
		fs_file_(fs_file),
		program_(-1) {
	}

	bool ShaderProgram::CompileAndLink() {
		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		auto vs_str = utils::ReadShaderFile::ReadShaderFromFile(vs_file_);
		auto vs_content = vs_str.c_str();
		glShaderSource(vertex_shader, 1, &vs_content, NULL);

		glCompileShader(vertex_shader);
		if (!GetCompileStatus(GL_VERTEX_SHADER, vertex_shader)) {
			return false;
		}

		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		auto fs_str = utils::ReadShaderFile::ReadShaderFromFile(fs_file_);
		auto fs_content = fs_str.c_str();
		glShaderSource(fragment_shader, 1, &fs_content, NULL);

		glCompileShader(fragment_shader);
		if (!GetCompileStatus(GL_FRAGMENT_SHADER, fragment_shader)) {
			return false;
		}

		GLuint program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);

		glLinkProgram(program);
		if (!GetLinkStatus(program)) {
			return false;
		}		

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		program_ = program;
		return true;
	}

	GLint ShaderProgram::GetCompileStatus(GLenum shader_type, GLuint shader) {
		GLint ret = 0;
		char info_log[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
		if (!ret) {
			glGetShaderInfoLog(shader, 512, NULL, info_log);

			if (shader_type == GL_VERTEX_SHADER) {
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
			}
			else if (shader_type == GL_FRAGMENT_SHADER) {
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
			}
			
			return ret;
		}

		if (shader_type == GL_VERTEX_SHADER) {
			std::cout << "INFO::SHADER::VERTEX::COMPILATION_SUCCEED\n" << std::endl;
		}
		else if (shader_type == GL_FRAGMENT_SHADER) {
			std::cout << "INFO::SHADER::FRAGMENT::COMPILATION_SUCCEED\n" << std::endl;
		}

		return ret;
	}

	GLint ShaderProgram::GetLinkStatus(GLuint shader) {
		GLint ret = 0;
		char info_log[512];
		glGetProgramiv(shader, GL_LINK_STATUS, &ret);
		if (!ret) {
			glGetProgramInfoLog(shader, 512, NULL, info_log);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
			return ret;
		}

		std::cout << "INFO::SHADER::PROGRAM::LINKING_SUCCEED\n" << std::endl;
		return ret;
	}
}
