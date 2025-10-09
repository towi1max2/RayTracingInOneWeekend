//idk why we need to define these for the stb image write header to not bug out?
#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION

//$(SolutionDir)Source;%(AdditionalIncludeDirectories) An additional root for the compiler to look in to find the correct files
#include "ThirdParty/stb_image_write.h"

#include <iostream>
#include <vector>
//#include <string>
//#include <cmath>



int main() 
{

	// Image
	int image_width = 1920;
	int image_height = 1080;
	int ColorChannels = 4;
	int stride = image_width * ColorChannels;

	//Buffer
	/*
	std::vector has nothing to do with the 3 component "vector" from math. std:vector should be seen as a more advance version of a regular array, by being resizable and smart.
	
	ClassTemplate -> std::vector<> = is a dynamic vector array that can change size easily, knows its size, manages its own memory etc easy to use.
	SpecificClassType -> typename -> unsigned char = is a data type that stores numbers between 0 - 255
	Object/Instance of the Class -> Pixels
	pixel(...) <- The integer going in is simply setting the intial size in memory bytes for the vector object to hold.
	*/
	std::vector<unsigned char> pixels(image_width * image_height * ColorChannels);

	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";


	//this goes from left to right first, then top to bottom
	for (int pixelY = 0; pixelY < image_height; pixelY++)
	{
		for (int pixelX = 0; pixelX < image_width; pixelX++)
		{
			auto coordX = double(pixelX) / (image_width - 1);//gives normalized - to 1 repeating by heights times
			auto coordY = double(pixelY) / (image_height - 1);

			unsigned char red = int(255 * coordX);
			unsigned char green = int(255 * coordY);
			unsigned char blue = 0;
			unsigned char alpha = 255;

			/* RootPixelIndex -> its the first array index of the current pixel
			* pixelY * image_width -> this part is the next row line
			* + pixelX -> this moves the selection to the right
			* (...) * comp -> this leaves gaps for the distinct color channels to fill inbetween
			*/
			int RootPixelIndex = (pixelY * image_width + pixelX) * ColorChannels;
			pixels[RootPixelIndex + 0] = red;
			pixels[RootPixelIndex + 1] = green;
			pixels[RootPixelIndex + 2] = blue;
			pixels[RootPixelIndex + 3] = alpha;

		}
	}
	/* stbi_write_png function usage
	filename -> Output path for the PNG File
	x -> width of the image in pixels
	y -> height of the image in pixels
	comp -> number of color channels
	*data -> pointer to a 1D array(organized correctly) that holds pixel data
	stride_bytes -> the number of bytes per row in the image... + optionally some more for padding to do more advanced memory layouts.
	*/
	stbi_write_png("Render/Image.png", image_width, image_height, ColorChannels, pixels.data(), stride);

}