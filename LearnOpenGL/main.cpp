// mogl -- My OpenGL
#include "CommonDefine.h"
#include "01_Getting_Started/02_Hello_Triangle/HelloTriangle.h"
#include "01_Getting_Started/02_Hello_Triangle/HelloTriangleIndexed.h"
#include "01_Getting_Started/02_Hello_Triangle/Exercise/Ex1_TwoTriangles.h"
#include "01_Getting_Started/02_Hello_Triangle/Exercise/Ex2_TwoTriangles2.h"
#include "01_Getting_Started/02_Hello_Triangle/Exercise/Ex3_TwoTriangles3.h"

void GetOpenGLInformation() {
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}

int main(int argc, char **argv) {

	

	int ret = 0;

	//ret = mogl::ch121::HelloTriangle::Run(argc, argv);
	//ret = mogl::ch122::HelloTriangleIndexed::Run(argc, argv);
	//ret = mogl::ch12ex1::TwoTriangles::Run(argc, argv);
	//ret = mogl::ch12ex2::TwoTriangles2::Run(argc, argv);
	ret = mogl::ch12ex3::TwoTriangles3::Run(argc, argv);

	return ret;
}


