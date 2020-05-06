#include "TextureCombined.h"
#include "CommonDefine.h"
#include "Utils/ShaderProgram.h"
#include "stb_image.h"

namespace mogl {

	namespace ch0104 {
		void TexturesCombined::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		}

		void TexturesCombined::ProcessInput(GLFWwindow *window) {
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, true);
			}
		}

		int TexturesCombined::Run(int argc, char *argv[]) {
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

			// build and compile our shader program
			ShaderProgram shader("./Shader/0104_TextureCombined.vs", "./Shader/0104_TextureCombined.fs");
			if (!shader.CompileAndLink()) {
				return -1;
			}

			float vertices[] = {
				// postions		// colors		// texture coords
				0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
				0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
				-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
				-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
			};

			unsigned int indices[] = {
				0, 1, 3,	// first triangle
				1, 2, 3		// second triangle
			};

			unsigned int VBO, VAO, EBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			// color attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
			glEnableVertexAttribArray(1);

			// texture coord attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);

			// load and create a texture
			unsigned int texture1, texture2;
			// texture1
			glGenTextures(1, &texture1);
			glBindTexture(GL_TEXTURE_2D, texture1);// all upcoming GL_TEXTURE_2D operations now have effect on this texture object

			// set the texture wrapping parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			// set texture filtering parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// load image, create texture and generate mipmaps
			int width, height, nrChannels;
			stbi_set_flip_vertically_on_load(true);
			auto data = stbi_load("../Assets/textures/container.jpg", &width, &height, &nrChannels, 0);
			if (!data) {
				std::cout << "Failed to load texture1" << std::endl;
				return -1;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0/*历史遗留问题*/, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);

			// texture2
			glGenTextures(1, &texture2);
			glBindTexture(GL_TEXTURE_2D, texture2);

			// set the texture wrapping parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			// set texture filtering parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// load image, create texture and generate mipmaps
			data = stbi_load("../Assets/textures/awesomeface.png", &width, &height, &nrChannels, 0);
			if (!data) {
				std::cout << "Failed to load texture2" << std::endl;
				return -1;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0/*历史遗留问题*/, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);

			// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
			shader.Use();
			glUniform1i(glGetUniformLocation(shader.GetProgram(), "texture1"), 0);
			shader.SetInt("texture2", 1);

			// 不停的渲染
			while (!glfwWindowShouldClose(window)) {
				// 输入
				ProcessInput(window);

				// 渲染
				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				// bind Texture
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture1);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, texture2);

				// render container
				shader.Use();
				glBindVertexArray(VAO);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

				// 检查并调用事件，交换缓冲
				glfwPollEvents();
				glfwSwapBuffers(window);
			}

			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);

			glfwTerminate();
			return 0;
		}

	}
}
