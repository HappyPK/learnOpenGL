#pragma once
#include <iostream>
#include <string>

std::string vertexShaderSource =
R"(
	#version 460 core
	layout(location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aNormal;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;
	
	out vec3 FragPos;
	out vec3 Normal;

	void main()
	{
		gl_Position =projection * view * model * vec4(aPos, 1.0);
		Normal = aNormal;
		FragPos = vec3(model * vec4(aPos, 1.0));
	}
)";

std::string fragmentShaderSource =
R"(
	#version 460 core
	out vec4 FragColor;
	in vec3 Normal;
	in vec3 FragPos; 

	uniform vec3 objectColor;
	uniform vec3 lightColor;
	uniform vec3 lightPos;
	
	void main()
	{
		// ambient
		float ambientStrength = 0.1;
		vec3 ambient = ambientStrength * lightColor;
  	
		// diffuse 
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(lightPos - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColor;
            
		vec3 result = (ambient + diffuse) * objectColor;
		FragColor = vec4(result, 1.0);
	}
)";


std::string Light_vertexShaderSource =
R"(
	#version 460 core
	layout (location = 0) in vec3 aPos;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	void main()
	{
		gl_Position = projection * view * model * vec4(aPos, 1.0);
	}
)";

std::string Light_fragmentShaderSource =
R"(
	#version 460 core
	out vec4 FragColor;

	void main()
	{
		FragColor = vec4(1.0);
	}
)";
