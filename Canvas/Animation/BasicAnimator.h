#ifndef _CC_BASIC_ANIMATOR
#define _CC_BASIC_ANIMATOR

#include "Types.h"
#include "RGB.h"
#include "Image.h"
#include <string>
#include <string_view>

namespace cc
{
	class BasicAnimator
	{
	public:
		BasicAnimator();

		void SetResolution(int32_t width, int32_t height);
		void SetFPS(Float fps);
		void SetLength(Float length);
		void SetTimeWindow(Float animStart, Float animEnd);
		void SetBackgroundColour(const RGBA& bgColour);

		void ResetToDefaults();

		template <typename Func>
		void Animate(Func icFunc)
		{
			Float startTime = m_renderSubset ? m_renderStart : 0;
			Float endTime = m_renderSubset ? m_renderEnd : m_length;
			
			int32_t startFrame = startTime * m_fps;
			int32_t endFrame = endTime * m_fps;

			cc::Image canvas(m_width, m_height, m_backgroundColour);

			for (int32_t currentFrame = startFrame; currentFrame < endFrame; currentFrame++)
			{
				icFunc(canvas, (Float)currentFrame / endFrame);

				std::string currentFrameString = std::to_string(currentFrame);
				
				cc::Image::Save(m_filePrefix + std::string(4 - currentFrameString.size(), '0') + currentFrameString + ".png", canvas, cc::ImageType::PNG);

				canvas.Fill(m_backgroundColour);
			}
		}

	private:
		int32_t     m_width;
		int32_t     m_height;
		Float       m_fps;
		Float       m_length;
		RGBA        m_backgroundColour;

		bool        m_renderSubset;
		Float       m_renderStart;
		Float       m_renderEnd;

		std::string m_filePrefix;
	};
}

#endif //_CC_BASIC_ANIMATOR
