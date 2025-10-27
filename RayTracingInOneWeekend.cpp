
#include <iostream>
//#include <string>
#include <filesystem>

#include "Raytracing/Image.h"

void MakeImage()
{
	constexpr int image_width{ 256 };
	constexpr int image_height{ 256 };
	constexpr int channels{ 4 };

	Image ImageObject{ image_width, image_height, Color{0.2,0.5,0.5} };
	//Image ImageObject{};

	//i=row, j=col k=layer
	for (int j{ 0 }; j < image_height; j++)
	{
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i{ 0 }; i < image_width; i++) 
		{
			double red = static_cast<double>(i) / (image_width - 1);
			double green = static_cast<double>(j) / (image_height - 1);

			ImageObject.SetPixelAt(i, j, Color(red, green, 0));
			//ImageObject.SetPixelAt(0, 0, Color(1.0, 1.0, 1.0));
		}
	}
	std::clog << "\rDone.                      \n\n";
	std::string RelativeFilePath{ "Render/Image.png" };
	
	WriteImage(ImageObject, RelativeFilePath);

	std::filesystem::path absolutePath = std::filesystem::absolute(RelativeFilePath);
	std::clog << "Image saved to: " << absolutePath << '\n';

	//std::clog << "\n\n" << ImageObject.GetPixelAt(0, 0);
}

int main()
{
	MakeImage();
}

