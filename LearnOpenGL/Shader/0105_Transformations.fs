#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float u_mixValue;

void main() {
	// linearly interpolate between boath textures (80% container, 20% awesomeface)
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1-TexCoord.x, TexCoord.y)), u_mixValue);
}


