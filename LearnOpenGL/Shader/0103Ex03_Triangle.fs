#version 330 core

out vec4 FragColor;

in vec3 aPosColor;

void main() {
	FragColor = vec4(aPosColor, 1.0f);
}

