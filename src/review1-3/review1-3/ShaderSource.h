#pragma once
#include <iostream>
#include <string>

std::string vertexShaderSource =
R"(
	#version 460 core
	layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec3 aColor;
	layout(location = 2) in vec2 aTexCoord;

	out vec3 ourColor;
	out vec2 TexCoord;

	void main()
	{
		gl_Position = vec4(aPos, 1.0);
		ourColor = aColor;
		TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	}
)";

std::string fragmentShaderSource =
R"(
	#version 460 core
	out vec4 FragColor;

	in vec3 ourColor;
	in vec2 TexCoord;

	// texture samplers
	uniform sampler2D texture1;
	uniform sampler2D texture2;

	void main()
	{
		FragColor = mix(texture2D(texture1, TexCoord), texture2D(texture2, TexCoord), 0.2);
	}
)";