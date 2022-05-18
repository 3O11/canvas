#include "Point.h"

namespace cc
{
	Point2::Point2()
		: x(0.0), y(0.0)
	{}

	Point2::Point2(Float val)
		: x(val), y(val)
	{}

	Point2::Point2(Float x, Float y)
		: x(x), y(y)
	{}

	Point3::Point3()
		: x(0.0), y(0.0), z(0.0)
	{}

	Point3::Point3(Float val)
		: x(val), y(val), z(val)
	{}

	Point3::Point3(Float x, Float y, Float z)
		: x(x), y(y), z(z)
	{}
}
