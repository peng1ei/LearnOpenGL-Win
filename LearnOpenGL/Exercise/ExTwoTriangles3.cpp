#include "ExTwoTriangles3.h"
#include "../CommonDefine.h"
#include "../ShaderProgram.h"

namespace mogl {

	namespace ch12ex3 {
		void TwoTriangles3::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		}

		void TwoTriangles3::ProcessInput(GLFWwindow *window) {
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, true);
			}
		}

		int TwoTriangles3::Run(int argc, char *argv[]) {
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
			// 绿色三角形
			ShaderProgram shader_program("./Shader/HelloTriangle.vs","./Shader/HelloTriangle.fs");
			if (!shader_program.CompileAndLink()) {
				return -1;
			}

			// 黄色三角形
			ShaderProgram shader_program_yellow("./Shader/HelloTriangle.vs", "./Shader/HelloTriangleYellow.fs");
			if (!shader_program_yellow.CompileAndLink()) {
				return -1;
			}

			///![1]

			///![2] 准备顶点数据
			float triangle1[] = {
				-0.5f, 0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
				0.0f, -0.5f, 0.0f,
			};

			float triangle2[] = {
				0.0f, 0.5f, 0.0f,
				0.0f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f
			};

			GLuint VBO[2], VAO[2];
			glGenVertexArrays(2, VAO);
			glGenBuffers(2, VBO);

			// 对于VAO和VBO，需要先绑定VAO，然后再绑定VBO
			// 这样就会将对应VBO相关信息存储在VAO中

			// 绘制第一个三角形
			glBindVertexArray(VAO[0]);

			glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			// 绘制第二个三角形
			glBindVertexArray(VAO[1]);

			glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			///![2]

			// 不停的渲染
			while (!glfwWindowShouldClose(window)) {
				// 输入
				ProcessInput(window);

				// 渲染
				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				glUseProgram(shader_program.GetProgram());
				glBindVertexArray(VAO[0]);
				glDrawArrays(GL_TRIANGLES, 0, 3);

				glUseProgram(shader_program_yellow.GetProgram());
				glBindVertexArray(VAO[1]);
				glDrawArrays(GL_TRIANGLES, 0, 3);

				// 检查并调用事件，交换缓冲
				glfwPollEvents();
				glfwSwapBuffers(window);
			}

			glDeleteVertexArrays(2, VAO);
			glDeleteBuffers(2, VBO);

			glfwTerminate();
			return 0;
		}

	}
}