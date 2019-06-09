#pragma once
#include "Texture.h"
class ImageTexture :
	public Texture
{
private:
	unsigned char* data;
	int width;
	int height;

public:
	ImageTexture(unsigned char* d_, int w_, int h_)
		: data(d_), width(w_), height(h_) {}

	virtual rgb value(float u, float v, const vec3& p) const {
		int i = 10*u * width;
		int j = 10*((1-v) * height - 0.001);
		if (i < 0) i = 0;
		if (j < 0) j = 0;
		if (i > width - 1) {
			i = i % width;
		};
		if (j > height - 1) j = j % height;
		float r = int(data[3 * i + 3 * width * j]) / 255.0f;
		float g = int(data[3 * i + 3 * width * j + 1]) / 255.0f;
		float b = int(data[3 * i + 3 * width * j + 2]) / 255.0f;
		return vec3(r, g, b);
	}
};
