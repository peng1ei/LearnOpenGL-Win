// mogl -- My OpenGL
#include "HelloTriangle.h"
#include "HelloTriangleIndexed.h"
#include "Exercise/ExTwoTriangles.h"
#include "Exercise/ExTwoTriangles2.h"
#include "Exercise/ExTwoTriangles3.h"

int main(int argc, char **argv) {
	int ret = 0;

	//ret = mogl::ch121::HelloTriangle::Run(argc, argv);
	//ret = mogl::ch122::HelloTriangleIndexed::Run(argc, argv);
	//ret = mogl::ch12ex1::TwoTriangles::Run(argc, argv);
	//ret = mogl::ch12ex2::TwoTriangles2::Run(argc, argv);
	ret = mogl::ch12ex3::TwoTriangles3::Run(argc, argv);
	
	return ret;
}


