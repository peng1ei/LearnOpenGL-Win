#include "HelloTriangle.h"
#include "CommonDefine.h"
#include "Utils/ReadShaderFile.h"

using namespace mogl::utils;

namespace mogl {

	namespace ch121 {
		void HelloTriangle::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		}

		void HelloTriangle::ProcessInput(GLFWwindow *window) {
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, true);
			}
		}

		int HelloTriangle::Run(int argc, char *argv[]) {
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac OS X系统可能需要

			GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
			if (window == NULL) {
				std::cout << "Failed to create GLFW window." << std::endl;
				glfwTerminate();
				return -1;
			}

			glfwMakeContextCurrent(window);
			glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				std::cout << "Failed to initialize GLAD." << std::endl;
				return -1;
			}			

			///![1] 构建GPU程序
			// vertex shader
			GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
			auto vertex_shader_str = ReadShaderFile::ReadShaderFromFile("./Shader/HelloTriangle.vs");
			auto vertex_shader_content = vertex_shader_str.c_str();
			std::cout << "Vertex shader:\n " << vertex_shader_content << std::endl;
			glShaderSource(vertex_shader, 1, &vertex_shader_content, NULL);
			glCompileShader(vertex_shader);

			GLint ret = 0;
			char info_log[512];
			glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &ret);
			if (!ret) {
				glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
				return -1;
			}

			// fragment shader
			GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
			auto fragment_shader_str = ReadShaderFile::ReadShaderFromFile("./Shader/HelloTriangle.fs");
			auto fragment_shader_content = fragment_shader_str.c_str();
			std::cout << "Fragment shader:\n " << fragment_shader_content << std::endl;
			glShaderSource(fragment_shader, 1, &fragment_shader_content, NULL);
			glCompileShader(fragment_shader);

			glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &ret);
			if (!ret) {
				glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
				return -1;
			}

			// link shaders
			GLuint shader_program = glCreateProgram();
			glAttachShader(shader_program, vertex_shader);
			glAttachShader(shader_program, fragment_shader);
			glLinkProgram(shader_program);

			glGetProgramiv(shader_program, GL_LINK_STATUS, &ret);
			if (!ret) {
				glGetProgramInfoLog(shader_program, 512, NULL, info_log);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
				return -1;
			}

			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);
			///![1]

			///![2] 准备顶点数据
			float vertices[] = {
				-0.5f, -0.5f, 0.0f, // left
				 0.5f, -0.5f, 0.0f, // right
				 0.0f,  0.5f, 0.0f  // top
			};

			GLuint VBO, VAO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);

			// 对于VAO和VBO，需要先绑定VAO，然后再绑定VBO
			// 这样就会将对应VBO相关信息存储在VAO中
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindVertexArray(0);

			///![2]

			// 不停的渲染
			while (!glfwWindowShouldClose(window)) {
				// 输入
				ProcessInput(window);

				// 渲染
				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				glUseProgram(shader_program);
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 3);

				// 检查并调用事件，交换缓冲
				glfwPollEvents();
				glfwSwapBuffers(window);
			}

			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);

			glfwTerminate();
			return 0;
		}

	}
}
