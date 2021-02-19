#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Image
{
public:
	Image();
	~Image();

public:
	unsigned char* LoadImage(char const* filename, int* width, int* height, int* nrChannels, int req_comp)
	{
		return stbi_load(filename, width, height, nrChannels, 0);
	}

	void DeleteImage(unsigned char* imageData)
	{
		stbi_image_free(imageData);
	}
};

Image::Image()
{
}

Image::~Image()
{
}

#endif