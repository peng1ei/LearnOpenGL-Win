#pragma once

class GLFWwindow;

namespace mogl {

	namespace ch0105 {
		class Transformations
		{
		public:
			static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
			static void ProcessInput(GLFWwindow *window);
			static int Run(int argc, char *argv[]);

			static float mix_value_;
		};
	}
}



