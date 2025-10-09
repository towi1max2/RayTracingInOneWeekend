/*#pragma once

#include <vector>
//#include "Vector.h"

class Image
{
private:
	int m_Width = 0;
	int m_Height = 0;
	std::vector<Color> m_Pixels;

public:
	Image() = default;
	Image(int Width, int Height, const Color& DefaultValue);
	~Image() = default;

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }

	void SetPixelAt(int x, int y, const Color& pixel);
	const Color& GetPixelAt(int x, int y) const;

	const std::vector<Color>& GetPixels() const;

};

void WriteImage(const Image& InputImage, const std::string& FilePath);*/