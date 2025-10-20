
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
//#include <cmath>

#include "Raytracing/Image.h"
//#include "Raytracing/Vector.h"
//#include "Raytracing/ClassTest.h"

//int main()
//{
//	//vec3 TestVector{ 0,2.2,0.1 };
//
//	//std::clog << TestVector;
//
//	Player Mario{};
//
//	std::clog << Mario.returnHealth();
//
//	
//	//vec3 TestVector = vec3(1, 2, 3);
//	vec3 TestVector(1, 2, 3);
//
//	double x = TestVector.x();
//	double y = TestVector.y();
//	double z = TestVector.z();
//	
//	std::clog << x << " : " << y << " : " << z << "\n\n";
//
//	//auto length = TestVector.length();
//
//	std::clog << "length " << TestVector.length() << "\n\n";
//
//	vec3 V1(1, 2, 3);
//	vec3 V2(1, 2, 3);
//
//	vec3 Output = V1 * V2;
//
//	std::clog << Output << "\n\n";
//
//	vec3 V3(1, 0, 0);
//	vec3 V4(-1, 0, 0);
//
//	double Product = dot(V3, V4);
//
//	std::clog << Product << "\n\n";
//
//	std::clog << "\n\nDone.                      \n\n";
//	
//}

void MakeImage()
{
	int image_width{ 256 };
	int image_height{ 256 };
	//int channels{ 4 };

	Image ImageObject{ image_width, image_height, Color{0,0,0} };

	//i=row, j=col k=layer
	for (int j{ 0 }; j < image_height; j++)
	{
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i{ 0 }; i < image_width; i++) 
		{
			double red = double(i) / (image_width - 1);
			double green = double(j) / (image_height - 1);

			ImageObject.SetPixelAt(i, j, Color(red, green, 0));
		}
	}
	std::clog << "\rDone.                      \n\n";
	std::string RelativeFilePath{ "Render/Image.png" };
	
	WriteImage(ImageObject, RelativeFilePath);

	std::filesystem::path absolutePath = std::filesystem::absolute(RelativeFilePath);
	std::clog << "Image saved to: " << absolutePath << '\n';
}

int main()
{
	MakeImage();
}

