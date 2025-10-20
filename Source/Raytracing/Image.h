#pragma once

#include <vector>
#include "Vector.h"


//This is a class that stores all the pixel colors in a vector array called Color
class Image
{
private:
	int m_Width = 0;
	int m_Height = 0;
	std::vector<Color> m_Pixels;//This declares an array that stores vec3 objects

public:
	Image() = default;//idk?
	Image(int Width, int Height, const Color& DefaultValue);//this recieves a direct 
	~Image() = default;//deconstructor?

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }

	void SetPixelAt(int x, int y, const Color& pixel);//set pixel color at a coordinate
	const Color& GetPixelAt(int x, int y) const; //double const? returns a const color reference. second const wont modify the 

	const std::vector<Color>& GetPixels() const;

};


//seperate thing, A outside function that writes the info in the image object to a filepath to a png
void WriteImage(const Image& InputImage, const std::string& FilePath);//stand alone function that uses an image object



//#pragma once
//
//#include "Vector.h"
//#include <iostream>
//
////this gives vec3 a nickname nothing more. Literally both are interchangable anywhere.
//using color = vec3;
//
//
//void write_color(std::ostream& out, const color& pixel_color) {
//
//	auto r = pixel_color.x();
//	auto g = pixel_color.y();
//	auto b = pixel_color.z();
//
//	// Translate the [0,1] component values to the byte range [0,255].
//	int rbyte = int(255.999 * r);
//	int gbyte = int(255.999 * g);
//	int bbyte = int(255.999 * b);
//
//	// Write out the pixel color components.
//	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
//}
