#ifndef _CC_BASIC_ANIMATOR
#define _CC_BASIC_ANIMATOR

#include "Types.h"
#include <string_view>

namespace cc
{
	class BasicAnimator
	{
	public:
		BasicAnimator();

		void SetResolution(int32_t width, int32_t height);
		void SetFPS(int32_t fps);
		void SetLength(Float length);

		template <typename Func>
		void Animate(Func icFunc);

	private:
		int32_t     m_fps;
		Float       m_animLength;
		std::string m_filePrefix;
	};
}

#endif //_CC_BASIC_ANIMATOR