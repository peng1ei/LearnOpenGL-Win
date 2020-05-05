// mogl -- My OpenGL
#include "CommonDefine.h"
#include "01_Getting_Started/02_Hello_Triangle/HelloTriangle.h"
#include "01_Getting_Started/02_Hello_Triangle/HelloTriangleIndexed.h"
#include "01_Getting_Started/02_Hello_Triangle/Exercise/Ex1_TwoTriangles.h"
#include "01_Getting_Started/02_Hello_Triangle/Exercise/Ex2_TwoTriangles2.h"
#include "01_Getting_Started/02_Hello_Triangle/Exercise/Ex3_TwoTriangles3.h"

#include "01_Getting_Started/03_Shader/ShaderUniform.h"
#include "01_Getting_Started/03_Shader/ShaderInterpolation.h"
#include "01_Getting_Started/03_Shader/Exercise/Ex1_Triangle.h"
#include "01_Getting_Started/03_Shader/Exercise/Ex2_TriangleMove.h"
#include "01_Getting_Started/03_Shader/Exercise/Ex3_Triangle.h"

#include "01_Getting_Started/04_Textures/Texture.h"

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
	//ret = mogl::ch12ex3::TwoTriangles3::Run(argc, argv);
	//ret = mogl::ch132::ShaderUniform::Run(argc, argv);
	//ret = mogl::ch132::ShaderInterpolation::Run(argc, argv);
	//ret = mogl::ch13ex1::Triangle::Run(argc, argv);
	//ret = mogl::ch13ex2::TriangleMove::Run(argc, argv);
	//ret = mogl::ch13ex3::Triangle::Run(argc, argv);

	ret = mogl::ch0104::Textures::Run(argc, argv);

	return ret;
}


