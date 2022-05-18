#ifndef _CC_POINT_H
#define _CC_POINT_H

#include "Types.h"
#include "Vector.h"

namespace cc
{
	struct Point2
	{
		Point2();
		Point2(Float val);
		Point2(Float x, Float y);

		Float x;
		Float y;
	};

	struct Point3
	{
		Point3();
		Point3(Float val);
		Point3(Float x, Float y, Float z);

		Float x;
		Float y;
		Float z;
	};
}

#endif //_CC_POINT_H
