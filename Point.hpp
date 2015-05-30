#ifndef POINT_HPP
#define POINT_HPP

class Point
{
	public:
		Point(){};
		Point(int x, int y) : x(x), y(y){};
		~Point(){};
		int x;
		int y;
};

#endif
