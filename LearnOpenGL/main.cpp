// mogl -- My OpenGL
#include "HelloTriangle.h"
#include "HelloTriangleIndexed.h"

int main(int argc, char **argv) {
	int ret = 0;

	//ret = mogl::ch121::HelloTriangle::Run(argc, argv);
	ret = mogl::ch122::HelloTriangleIndexed::Run(argc, argv);
	
	return ret;
}


