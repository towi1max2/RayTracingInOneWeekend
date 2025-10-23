#pragma once

#include <vector>
#include "Vector.h"


//This is a class that stores all the pixel colors in a vector array called Color
class Image
{
private:
	//Member variables = The class data
	int m_Width { 0 };
	int m_Height { 0 };
	std::vector<Color> m_Pixels; // declares an empty array of Color(Vec3) objects
	//std::vector<Color> m_Pixels{ 256 * 256, Color{0.4,2,5} };//hard coding size and values

public:
	Image() = default;//Leave the class Data alone, doesnt modify their default values.
	Image(int Width, int Height, const Color& DefaultValue);//this recieves a direct 
	~Image() = default;//default deconstructor.

	int GetWidth() const 
	{ 
		return m_Width; 
	}
	int GetHeight() const 
	{ 
		return m_Height; 
	}

	void SetPixelAt(int x, int y, const Color& pixel);//set pixel color at a coordinate

	//avoids copies(returns direct reference), adds a lock on the data returned(CONST - CANNOT MODIFY)
	const Color& GetPixelAt(int x, int y) const; // second const wont allow function to modify the member variables

	//std::vector<Color> is the data type it returns
	const std::vector<Color>& GetPixels() const;

};


//seperate thing, A outside function that writes the info in the image object to a filepath to a png
void WriteImage(const Image& InputImage, const std::string& FilePath);//stand alone function that uses an image object