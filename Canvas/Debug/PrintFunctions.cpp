#include "PrintFunctions.h"

#include <cstdio>

namespace cc
{
	namespace Debug
	{
		void PrintMatrix3(const Matrix3& m)
		{
			for (size_t i = 0; i < 3; ++i)
			{
				printf("%.4f %.4f %.4f\n", m[i][0], m[i][1], m[i][2]);
			}
			printf("\n");
		}

		void PringMatrix4(const Matrix4& m)
		{
			for (size_t i = 0; i < 4; ++i)
			{
				printf("%.4f %.4f %.4f %.4f\n", m[i][0], m[i][1], m[i][2], m[i][3]);
			}
			printf("\n");
		}
	}
}
