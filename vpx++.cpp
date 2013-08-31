#include "vpx++.h"

#include <iostream>

using std::cout;
using std::endl;

namespace vpx
{

double clip(double n, double lower, double upper)
{
	return std::max(lower, std::min(n, upper));
}

Planes SeperateRGB(const Frame& rgb_frame)
{
	Planes rgb_planes;

	for (size_t i = 0; i < rgb_frame.size(); ++i)
	{
		if (i % 3 == 0)			// R
		{
			rgb_planes[0].push_back(rgb_frame[i]);
		}
		else if ((i - 1) % 3 == 0)	// G
		{
			rgb_planes[1].push_back(rgb_frame[i]);
		}
		else				// B
		{
			rgb_planes[2].push_back(rgb_frame[i]);
		}
	}

	unsigned width = rgb_frame.GetWidth();
	unsigned height = rgb_frame.GetHeight();

	rgb_planes.SetWidth(width);
	rgb_planes.SetHeight(height);

	return rgb_planes;
}

/*Planes RGB2YUV420(const Frame& rgb_frame)
{
	int row, col, j;
	int width = rgb_frame.GetWidth();
	int height = rgb_frame.GetHeight();

	Planes yuv420;	
	yuv420.SetWidth(width);
	yuv420.SetHeight(height);

	for (size_t i = 0; i < rgb_frame.size() / 3; i += 3)
	{
		row = i / width;
		col = i % width;

		yuv420[0][i] = 0.299 * rgb_frame[i] +
				0.587 * rgb_frame[i + 1] + 
				0.114 * rgb_frame[i + 2];

		if (row % 2 == 0 && col % 2 == 0)
		{
			// Reduced width + 1 for the width of odd no.
			j = row / 2 * (width / 2 + width % 2) + col / 2;

			yuv420[1][j] = -0.169 * rgb_frame[i] -
					0.331 * rgb_frame[i + 1] +
					0.5 * rgb_frame[i + 2] +
					128;
			yuv420[2][j] = 0.5 * rgb_frame[i] -
					0.419 * rgb_frame[i + 1] -
					0.081 * rgb_frame[i + 2] +
					128;
		}
	}

	return yuv420;
}*/

Planes RGB2YUV420(const Planes& rgb)
{
	int row, col;
	int width = rgb.GetWidth();
	int height = rgb.GetHeight();
	size_t size = rgb[0].size();

	Planes yuv420;	
	yuv420.SetWidth(width);
	yuv420.SetHeight(height);

	double r, g, b;
	for (size_t i = 0; i < size; ++i)
	{
		r = rgb[0][i];
		g = rgb[1][i];
		b = rgb[2][i];

		yuv420[0].push_back( 0.299 * r
				    +0.587 * g
				    +0.114 * b);

		row = i / width;
		col = i % width;

		if (row % 2 == 0 && col % 2 == 0)
		{
			yuv420[1].push_back(-0.169 * r
					    -0.331 * g
					    +0.500 * b
					    +128);
			yuv420[2].push_back( 0.500 * r
					    -0.419 * g
					    -0.0813 * b
					    +128);

			// NTSC standard
			/*yuv420[1].push_back(-0.147 * r
					    -0.289 * g
					    +0.436 * b);
			yuv420[2].push_back( 0.615 * r
					    -0.515 * g
					    -0.100 * b);*/
		}
	}

	return yuv420;
}

Planes YUV4202RGB(const Planes& yuv420)
{
	unsigned width = yuv420.GetWidth();
	unsigned height = yuv420.GetHeight();
	size_t size = yuv420[0].size();

	Planes rgb;
	rgb.SetWidth(width);
	rgb.SetHeight(height);

	size_t row, col;
	double y, u, v;
	size_t j;

	for (size_t i = 0; i < size; ++i)
	{
		y = yuv420[0][i];

		row = i / width;
		col = i % width;
		
		if (col % 2 == 0)
		{
			// Reduced width + 1 for the width of odd no.
			j = row / 2 * (width / 2 + width % 2) + col / 2;

			u = yuv420[1][j];
			v = yuv420[2][j];
		}

		rgb[0].push_back(clip(y + (1.4075 * (v - 128)), 0, 255));
		rgb[1].push_back(clip(y - (0.3455 * (u - 128) + (0.7169 * (v - 128))), 0, 255));
		rgb[2].push_back(clip(y + (1.7790 * (u - 128)), 0, 255));

	}

	return rgb;
}

}

