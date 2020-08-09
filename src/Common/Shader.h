#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class MyShader
{
public:
	MyShader(const char* VertexPath, const char* FramentPath)
	{
		std::string vShaderCode; ReadShaderCode(VertexPath, vShaderCode);
		std::string fShaderCode; ReadShaderCode(FramentPath, fShaderCode);

		const char* vCode = vShaderCode.c_str();
		const char* fCode = fShaderCode.c_str();

		unsigned int vertex, fragment;
		// vertex shader
		CreateShader(vertex, GL_VERTEX_SHADER, &vCode);

		// fragment Shader
		CreateShader(fragment, GL_FRAGMENT_SHADER, &fCode);

		//Link Shader
		LinkShader(m_ID, vertex, fragment);
	}
public:
	void use()
	{
		glUseProgram(m_ID);
	}

	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
	}

	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	const unsigned int GetProgramID() { return m_ID; }

private:
	bool ReadShaderCode(const char* CodePath,std::string& Code)
	{
		std::ifstream ShaderFile;
		ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			ShaderFile.open(CodePath);
			std::stringstream ShaderStream;
			ShaderStream << ShaderFile.rdbuf();
			ShaderFile.close();
			Code = ShaderStream.str();
			return true;
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			return false;
		}
		return true;
	}

	bool CreateShader(unsigned int& shader, const GLenum& type, const GLchar* const* string)
	{
		shader = glCreateShader(type);
		glShaderSource(shader, 1, string, NULL);
		glCompileShader(shader);
		if (!CheckShader(shader))
			return false;
		return true;
	}

	bool LinkShader(unsigned int& Linkshader, const int& shader1, const int& shader2)
	{
		Linkshader = glCreateProgram();
		glAttachShader(Linkshader, shader1);
		glAttachShader(Linkshader, shader2);
		glLinkProgram(Linkshader);

		if (!CheckShader(Linkshader))
			return false;
		return true;

		glDeleteShader(shader1);
		glDeleteShader(shader2);
	}

	bool CheckShader(const int& shader)
	{
		// check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}

private:
	unsigned int m_ID{};
};


#endif // !SHADER_H
