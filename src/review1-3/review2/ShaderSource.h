#pragma once
#include <iostream>
#include <string>

std::string vertexShaderSource =
R"(
	#version 460 core
	layout(location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aNormal;
	layout (location = 2) in vec2 aTexCoords;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;
	
	out vec3 FragPos;
	out vec3 Normal;
	out vec2 TexCoords;

	void main()
	{
		gl_Position =projection * view * model * vec4(aPos, 1.0);
		Normal = mat3(transpose(inverse(model))) * aNormal;
		FragPos = vec3(model * vec4(aPos, 1.0));
		TexCoords = aTexCoords;
	}
)";

std::string fragmentShaderSource =
R"(
	#version 460 core
	out vec4 FragColor;

	in vec3 Normal;
	in vec3 FragPos; 
	in vec2 TexCoords;

	uniform vec3 viewPos;

	struct Material 
	{
		sampler2D diffuse;
		sampler2D specular;
		float shininess;
	}; 
	uniform Material material;

	struct Light 
	{
		//vec3 position;
		vec3 direction;

		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
	};	
	uniform Light light;

	void main()
	{
		// ambient
		vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords)).rgb;
  	
		// diffuse 
		vec3 norm = normalize(Normal);
		//vec3 lightDir = normalize(light.position - FragPos);
		vec3 lightDir = normalize(-light.direction); 
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, TexCoords)).rgb;

        // specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular =  vec3(texture(material.specular, TexCoords)) * spec * light.specular; 

		vec3 result = ambient + diffuse + specular;
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
