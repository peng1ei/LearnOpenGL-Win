#pragma once
class GLFWwindow;
namespace mogl {

	namespace ch12ex3 {

		class TwoTriangles3 {
		public:
			static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
			static void ProcessInput(GLFWwindow *window);
			static int Run(int argc, char *argv[]);
		};

	}


}

