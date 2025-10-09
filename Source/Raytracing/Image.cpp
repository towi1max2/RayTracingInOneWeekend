/*#define _CRT_SECURE_NO_WARNINGS
#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
//$(SolutionDir)Source;%(AdditionalIncludeDirectories) An additional root for the compiler to in for the correct files woot 
#include "ThirdParty/stb_image_write.h"

Image::Image(int Width, int Height, const Color& DefaultValue) : m_Width(Width), m_Height(Height)
{
	m_Pixels = std::vector<Color>(Width * Height, DefaultValue);
}

void Image::SetPixelAt(int x, int y, const Color& pixel)
{
	m_Pixels.at(x + y * m_Width) = pixel;
}

const Color& Image::GetPixelAt(int x, int y) const
{
	return m_Pixels.at(x + y * m_Width);
}

const std::vector<Color>& Image::GetPixels() const
{
	return m_Pixels;
}

void WriteImage(const Image& InputImage, const std::string& FilePath)
{
	std::vector<unsigned char> data;
	constexpr int channels = 4;
	int size = InputImage.GetHeight() * InputImage.GetWidth() * channels;
	data.reserve(size);
	for (const Color& px : InputImage.GetPixels())
	{
		data.push_back(static_cast<int>(255.999 * px.x));
		data.push_back(static_cast<int>(255.999 * px.y));
		data.push_back(static_cast<int>(255.999 * px.z));
		data.push_back(static_cast<int>(255.999 * px.w));
	}
	stbi_write_png(FilePath.c_str(), InputImage.GetWidth(), InputImage.GetHeight(), channels, data.data(), channels * InputImage.GetWidth());
}*/