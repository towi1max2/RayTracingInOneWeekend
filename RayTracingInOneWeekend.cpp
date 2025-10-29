
#include <iostream>
//#include <string>
#include <filesystem>

#include "Raytracing/Image.h"
#include "Raytracing/Ray.h"

void MakeImage()
{
	constexpr int image_width{ 1920 };
	constexpr int image_height{ 1080 };
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

Color RayColor(const Ray& r)
{
	Vector3d UnitDirection = unit_vector(r.GetDirection());
	double a = 0.5 * (UnitDirection.y() + 1.0);
	return (1.0 - a) * Color { 1, 1, 1 } + a * Color{0.5, 0.7, 1.0};
}

int main()
{
	double Aspect_Ratio = 16.0 / 9.0; // 1.7777~
	int ImageWdith = 1920;

	int ImageHeight = int(ImageWdith / Aspect_Ratio);
	//Image_Height = (Image_Height < 1) ? 1 : Image_Height;
	Image ImageObject{ ImageWdith, ImageHeight, Color{} };


	//Camera Settings

	double FocalLength = 1.0;
	//Arbitrary Viewport Height value
	double ViewportHeight = 2.0;
	double ViewportWidth = ViewportHeight * (static_cast<double>(ImageWdith)/ImageHeight); //Viewport_Height * Aspect_Ratio(We calculate the actual value instead of using AspectRatio to insure we get the actual Aspect Ratio)
	Vector3d CameraPosition { 0, 0, 0 };

	//Vectors right and down acroos the viewport
	Vector3d ViewportU{ ViewportWidth, 0, 0 };
	Vector3d ViewportV{0, -ViewportHeight, 0};

	//Get normalized UVs
	Vector3d PixelDeltaU = ViewportU / ImageWdith;
	Vector3d PixelDeltaV = ViewportV / ImageHeight;

	//Get uper left pixel location
	Vector3d ViewportUpperLeft = CameraPosition - Vector3d{ 0,0,FocalLength } - ViewportU / 2 - ViewportV / 2;

	Vector3d PixelUpperLeftPos = ViewportUpperLeft + 0.5 * (PixelDeltaU + PixelDeltaV);


	//Render

	//i=row, j=col k=layer
	for (int j{ 0 }; j < ImageHeight; j++)
	{
		std::clog << "\rScanlines remaining: " << (ImageHeight - j) << ' ' << std::flush;
		for (int i{ 0 }; i < ImageWdith; i++)
		{
			Vector3d PixelPosition = PixelUpperLeftPos + (i * PixelDeltaU) + (j * PixelDeltaV);
			Vector3d RayDirection = PixelPosition - CameraPosition;
			Ray r{CameraPosition, RayDirection};

			//Color PixelColor = 
			ImageObject.SetPixelAt(i, j, RayColor(r));
			//ImageObject.SetPixelAt(0, 0, Color(1.0, 1.0, 1.0));
		}
	}
	std::clog << "\rDone.                      \n\n";
	std::string RelativeFilePath{ "Render/Image.png" };

	WriteImage(ImageObject, RelativeFilePath);

	//MakeImage();
}

