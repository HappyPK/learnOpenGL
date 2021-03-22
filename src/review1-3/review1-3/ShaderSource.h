#pragma once
#include <iostream>
#include <string>

std::string vertexShaderSource =
R"(
	#version 460 core
	layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec2 aTexCoord;

	out vec2 TexCoord;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;
	
	void main()
	{
		gl_Position =projection * view * model * vec4(aPos, 1.0);
		TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	}
)";

std::string fragmentShaderSource =
R"(
	#version 460 core
	out vec4 FragColor;

	in vec2 TexCoord;

	uniform float fmix;	

	// texture samplers
	uniform sampler2D texture1;
	uniform sampler2D texture2;
	
	void main()
	{
		FragColor = mix(texture2D(texture1, TexCoord), texture2D(texture2, TexCoord), fmix);
	}
)";