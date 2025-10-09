
#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION
//$(SolutionDir)Source;%(AdditionalIncludeDirectories) An additional root for the compiler to in for the correct files
#include "ThirdParty/stb_image_write.h"

#include <iostream>
#include <vector>
//#include <string>
//#include <cmath>



int main() 
{

	// Image woot woot

	int image_width = 1920;
	int image_height = 1080;
	int comp = 3;
	int stride = image_width * comp;

	//Buffer
	std::vector<unsigned char> pixels(image_width * image_height * comp);

	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";


	//this goes from left to right first, then top to bottom
	for (int pixelY = 0; pixelY < image_height; pixelY++)
	{
		for (int pixelX = 0; pixelX < image_width; pixelX++)
		{
			auto coordX = double(pixelX) / (image_width - 1);//gives normalized - to 1 repeating by heights times
			auto coordY = double(pixelY) / (image_height - 1);
			auto coordZ = 0.0; //a decimal makes it a double automatially

			int red = int(255.999 * coordX);
			int green = int(255.999 * coordY);
			int blue = int(255.999 * coordZ);

			//std::cout << red << ' ' << green << ' ' << blue << "\n";

			int idx = (pixelY * image_width + pixelX) * comp;
			pixels[idx + 0] = (unsigned char)red;
			pixels[idx + 1] = (unsigned char)green;
			pixels[idx + 2] = (unsigned char)blue;

		}
	}
	stbi_write_png("Render/Image.png", image_width, image_height, comp, pixels.data(), stride);

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
