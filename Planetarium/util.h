#pragma once

struct Color
{
	GLubyte R, G, B;
	Color()
	{
		R = G = B = 0x00;
	}
	Color(GLubyte r, GLubyte g, GLubyte b)
	{
		R = r;
		G = g;
		B = b;
	};
};