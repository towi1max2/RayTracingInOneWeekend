
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

double hit_sphere(const Vector3d& center, double radius, const Ray& r)
{
	Vector3d oc = center - r.GetOrigin();
	auto a = r.GetDirection().length_squared();
	auto h = dot(r.GetDirection(), oc);
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = h * h - a * c;

	//no intersection with sphere if < 0
	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (h - std::sqrt(discriminant)) / a;
	}
}

Color RayColor(const Ray& r)
{
	auto t = hit_sphere(Vector3d(0, 0, -1), 0.4, r);
	if (t > 0.0) {
		Vector3d N = unit_vector(r.at(t) - Vector3d(0, 0, -1));
		return 0.5 * Color(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	
	return Color(0, 0, 1);

	Vector3d UnitDirection = unit_vector(r.GetDirection());//normalize incoming ray direction
	double a = 0.5 * (UnitDirection.y() + 1.0);//
	return (1.0 - a) * Color { 1.0, 1.0, 1.0 } + a * Color{ 0.5, 0.7, 1.0 };
}

int main()
{
	/*
	Actual Image Resolution settings
	*/
	double Aspect_Ratio = 16.0 / 9.0; // 1.7777~ The ideal ratio for following things to match proportions
	int ImageWdith = 1920;//you can change the width and the height automatically adapts
	int ImageHeight = int(ImageWdith / Aspect_Ratio);
	//Image_Height = (Image_Height < 1) ? 1 : Image_Height;

	Image ImageObject{ ImageWdith, ImageHeight, Color{} };


	/*
	Virtual plane/camera/viewport Settings : our 2D Window into 3D Space where the image is projected
	*/

	double FocalLength = 1.0;//Distance the virtual viewport is from the eyepoint/camera position

	//Arbitrary Viewport Size
	double ViewportHeight = 1.0;//arbitrary number, size of viewport effects look of image
	double ViewportWidth = ViewportHeight * (static_cast<double>(ImageWdith)/ImageHeight); //Viewport_Height * Aspect_Ratio
	Vector3d CameraPosition { 0, 0, 0 };//eye point is at 0,0,0

	//Vector across the horizontal right & vector down the vertical virtual viewport
	Vector3d ViewportU{ ViewportWidth, 0, 0 };
	Vector3d ViewportV{0, -ViewportHeight, 0};

	//horizontal and vertical delta vectors from pixel to pixel, THE Vector between PIXELS, good for getting pixel step sizes
	Vector3d PixelDeltaU = ViewportU / ImageWdith;
	Vector3d PixelDeltaV = ViewportV / ImageHeight;

	//Get upper left pixel location of the virtual viewport : -Z is conventionally forward in camera space
	Vector3d ViewportUpperLeft = CameraPosition - Vector3d{ 0,0,FocalLength } - ViewportU / 2 - ViewportV / 2;//eyepoint -> forward -> left -> up
	Vector3d PixelUpperLeftPos = ViewportUpperLeft + 0.5 * (PixelDeltaU + PixelDeltaV);//shift a half step to reposition in the center of the top left virtual viewport pixel, 


	/*
	Render
	*/

	//i=row, j=col k=layer  right down
	for (int j{ 0 }; j < ImageHeight; j++)
	{
		std::clog << "\rScanlines remaining: " << (ImageHeight - j) << ' ' << std::flush;
		for (int i{ 0 }; i < ImageWdith; i++)
		{
			/* 
			* eyepoint is at (0,0,0)
			* shifts in pixel steps, from -x to +x and +y to -y
			* The pixel position is in -z from the eye point
			*/
			Vector3d PixelPosition = PixelUpperLeftPos + (i * PixelDeltaU) + (j * PixelDeltaV);
			Vector3d RayDirection = PixelPosition - CameraPosition;

			Ray r{CameraPosition, RayDirection};//Returns a Color from vector data

			ImageObject.SetPixelAt(i, j, RayColor(r));
		}
	}
	std::clog << "\rDone.                      \n\n";
	std::string RelativeFilePath{ "Render/Image.png" };

	WriteImage(ImageObject, RelativeFilePath);

}

