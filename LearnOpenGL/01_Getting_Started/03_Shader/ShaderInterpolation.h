#pragma once
class GLFWwindow;
namespace mogl {

	namespace ch132 {

		class ShaderInterpolation {
		public:
			static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
			static void ProcessInput(GLFWwindow *window);
			static int Run(int argc, char *argv[]);
		};

	}


}

