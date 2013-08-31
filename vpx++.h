#ifndef CPPVPX_H
#define CPPVPX_H

#include "vpx++_exception.h"

#include <vector>
#include <array>

namespace vpx
{

class Frame;
class Planes;

// Make Frame and Planes a final class which cannot be interited, because no virtual
// destructor is provided in STL containers. It would be dangerous if
// users inherit it.
class MakeFinal
{
private:
	MakeFinal() {}

	friend class Frame;
	friend class Planes;
};

class Frame : public std::vector<unsigned char>, public virtual MakeFinal
{
public:
	void SetWidth(unsigned width)
	{
		this->width = width;
	}

	void SetHeight(unsigned height)
	{
		this->height = height;
	}

	unsigned GetWidth() const
	{
		return width;
	}

	unsigned GetHeight() const
	{
		return height;
	}

private:
	unsigned width;
	unsigned height;

	friend class Planes;
};

typedef Frame Plane;

class Planes : public std::array<Plane, 3>, public virtual MakeFinal
{
public:
	Planes() {}

	Planes(unsigned width, unsigned height)
	{
		SetWidth(width);
		SetHeight(height);
	}

	void SetWidth(unsigned width)
	{
		for (int i = 0; i < 3; ++i)
		{
			this->operator[](i).width = width;
		}
	}

	void SetHeight(unsigned height)
	{
		for (int i = 0; i < 3; ++i)
		{
			this->operator[](i).height = height;
		}
	}

	unsigned GetWidth() const
	{
		// Assume all planes have the same width
		return this->operator[](0).width; 
	}

	unsigned GetHeight() const
	{
		// Assume all planes have the same height
		return this->operator[](0).height; 
	}

	unsigned GetWidth(int n) const
	{
		return this->operator[](n).width; 
	}

	unsigned GetHeight(int n) const
	{
		return this->operator[](n).height; 
	}
};

// Free utility functions

Planes SeperateRGB(const Frame& rgb_frame);

//Planes RGB2YUV420(const Frame& rgb_frame);

Planes RGB2YUV420(const Planes& rgb);

Planes YUV4202RGB(const Planes& yuv420);

}

#endif

