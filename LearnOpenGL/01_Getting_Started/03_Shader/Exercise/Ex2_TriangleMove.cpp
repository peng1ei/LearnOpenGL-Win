#include "Ex2_TriangleMove.h"
#include "CommonDefine.h"
#include "Utils/ShaderProgram.h"

namespace mogl {

	namespace ch13ex2 {
		void TriangleMove::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		}

		void TriangleMove::ProcessInput(GLFWwindow *window) {
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, true);
			}
		}

		int TriangleMove::Run(int argc, char *argv[]) {
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
			ShaderProgram shader_program("./Shader/0103Ex02_TriangleMove.vs",
				"./Shader/0103Ex02_TriangleMove.fs");
			if (!shader_program.CompileAndLink()) {
				return -1;
			}

			shader_program.Use();
			shader_program.SetVec4("u_color", 0.0f, 0.5f, 0.0f, 1.0f);
			shader_program.UnUse();

			///![1]

			///![2] 准备顶点数据
			float vertices[] = {
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.0f, 0.5f, 0.0f,
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

				shader_program.Use();

				float time = glfwGetTime();
				float offset = sin(time) / 2.0 + 0.5;
				shader_program.SetFloat("u_offset", offset);

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