#pragma once
#include <iostream>
#include <string>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct ImageData
{
	unsigned char* m_imageData;
	int m_width;
	int m_height;
	int m_nrChannels;
	ImageData()
	{
		m_imageData = nullptr;
		m_width = 0;
		m_height = 0;
		m_nrChannels = 0;
	}
};
typedef std::shared_ptr<ImageData> ImageDataPtr;

class Image
{
public:
	Image(const std::string &imagePath);

public:
	const ImageDataPtr getImageData()
	{
		return m_imageDataPtr;
	}

	bool genGLTexture(unsigned int &textureIndex);

private:
	std::string m_imagePath;
	ImageDataPtr m_imageDataPtr;
};
typedef std::shared_ptr<Image> ImagePtr;

Image::Image(const std::string &imagePath):
	m_imagePath(imagePath)
{
	m_imageDataPtr = std::make_shared<ImageData>();
	stbi_set_flip_vertically_on_load(true);
	m_imageDataPtr->m_imageData = stbi_load(m_imagePath.c_str(), &m_imageDataPtr->m_width, &m_imageDataPtr->m_height, &m_imageDataPtr->m_nrChannels, 0);
}


bool Image::genGLTexture(unsigned int& textureIndex)
{
	glGenTextures(1, &textureIndex);
	glBindTexture(GL_TEXTURE_2D, textureIndex);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (!m_imageDataPtr->m_imageData)
	{
		std::cout << "Failed to load texture" << std::endl;
		return false;
	}

	GLint internalformat = m_imageDataPtr->m_nrChannels == 4 ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, internalformat, m_imageDataPtr->m_width, m_imageDataPtr->m_height, 0, internalformat, GL_UNSIGNED_BYTE, m_imageDataPtr->m_imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	return true;
}
