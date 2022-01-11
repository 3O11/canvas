#ifndef _CC_VECTOR_H
#define _CC_VECTOR_H

namespace cc
{
	struct Vector2
	{
		Vector2();
		Vector2(float val);
		Vector2(float x, float y);

		float x;
		float y;
	};

	struct Vector3
	{
		Vector3();
		Vector3(float val);
		Vector3(float x, float y, float z);

		float x;
		float y;
		float z;
	};
}

#endif //_CC_VECTOR_H
