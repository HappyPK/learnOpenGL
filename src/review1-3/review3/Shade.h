#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace
{
	void getShaderSourceCode(const std::string &shaderPath, std::string &sourceCode)
	{
		std::ifstream sourceFile;
		sourceFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			sourceFile.open(shaderPath);
			std::stringstream sourceStream;
			sourceStream << sourceFile.rdbuf();
			sourceFile.close();
			sourceCode = sourceStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
	}

	void checkCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}

	void createShader(const char* shaderCode, unsigned int &shaderIndex, const GLenum &type)
	{
		shaderIndex = glCreateShader(type);
		glShaderSource(shaderIndex, 1, &shaderCode, NULL);
		glCompileShader(shaderIndex);
		checkCompileErrors(shaderIndex, "VERTEX");
	}
}

class Shader
{
public:
	Shader(const std::string &vertexCode,const std::string &fragmentCode)
	{
		unsigned int vertexshaderIndex, fragmentShaderIndex;
		createShader(vertexCode.c_str(), vertexshaderIndex, GL_VERTEX_SHADER);
		createShader(fragmentCode.c_str(), fragmentShaderIndex, GL_FRAGMENT_SHADER);

		m_shaderId = glCreateProgram();
		glAttachShader(m_shaderId, vertexshaderIndex);
		glAttachShader(m_shaderId, fragmentShaderIndex);

		glLinkProgram(m_shaderId);
		checkCompileErrors(m_shaderId, "PROGRAM");
		glDeleteShader(vertexshaderIndex);
		glDeleteShader(fragmentShaderIndex);
	}

public:
	void use()
	{
		glUseProgram(m_shaderId);
	}

	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_shaderId, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_shaderId, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_shaderId, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(m_shaderId, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(m_shaderId, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(m_shaderId, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_shaderId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	GLuint getId() { return m_shaderId; }

private:
	uint32_t m_shaderId;
};
typedef std::shared_ptr<Shader> ShaderPtr;