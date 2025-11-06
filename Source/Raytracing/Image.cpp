#define _CRT_SECURE_NO_WARNINGS
#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
//$(SolutionDir)Source;%(AdditionalIncludeDirectories) An additional root for the compiler to insidw for its search for the correct file
#include "ThirdParty/stb_image_write.h"

//Image:: this funciton belongs to the class Image, we need it because the constructor function is not a function outside, its scope is inside the Image class.
//
Image::Image(int Width, int Height, const Color& DefaultValue)
	: m_Width(Width), m_Height(Height)
{
	//Creates a temporary vector array, that is actually initialized with a size and values and assign it to the m_Pixel member variable.
	m_Pixels = std::vector<Color>(Width * Height, DefaultValue);
}

void Image::SetPixelAt(int x, int y, const Color& pixel)
{
	//.at() is a built in member function of std::vector 
	//same as m_Pixel[] -> .at() slightly slower but avoids accessing invalid data
	m_Pixels.at(x + y * m_Width) = pixel;
}

//this function returns an individual Color object in the m_Pixel vector array
const Color& Image::GetPixelAt(int x, int y) const
{
	//returns the direct Color object at a certain index m_Pixel[]
	return m_Pixels.at(x + y * m_Width);
}

//this function returns the whole vector array that holds Color objects
const std::vector<Color>& Image::GetPixels() const
{
	//our member variable vector array that holds Color Objects
	return m_Pixels;
}


//seperate thing
void WriteImage(const Image& InputImage, const std::string& FilePath)
{
	std::vector<unsigned char> data;//declare an empty array of char
	constexpr int channels = 4;//hard coded value for RGBA channels
	int size = InputImage.GetHeight() * InputImage.GetWidth() * channels;//Height * Width * 4
	data.reserve(size);//reserves memory capcity to == size, filled with uninitialized data.

	//px holds the current object being iterated, in this case it cannot be modified and is not being unnecessarily copied
	for (const Color& px : InputImage.GetPixels())
	{
		//stbi_write_png wraps values if not clamped
		data.push_back(static_cast<int>(255.999 * std::clamp(px.x(), 0.0, 1.0)));
		data.push_back(static_cast<int>(255.999 * std::clamp(px.y(), 0.0, 1.0)));
		data.push_back(static_cast<int>(255.999 * std::clamp(px.z(), 0.0, 1.0)));
		//data.push_back(static_cast<int>(255.999 * px.w));
		data.push_back(255);
	}
	/* stbi_write_png function usage
	filename -> Output path for the PNG File
	x -> width of the image in pixels
	y -> height of the image in pixels
	comp -> number of color channels
	*data -> pointer to a 1D array(organized correctly) that holds pixel data
	stride_bytes -> the number of bytes per row in the image... + optionally some more for padding to do more advanced memory layouts.*/
	stbi_write_png(FilePath.c_str(), InputImage.GetWidth(), InputImage.GetHeight(), channels, data.data(), channels * InputImage.GetWidth());
}