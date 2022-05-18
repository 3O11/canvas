#include "BasicAnimator.h"

namespace cc
{
    BasicAnimator::BasicAnimator()
    {
        ResetToDefaults();
    }

	void BasicAnimator::SetResolution(int32_t width, int32_t height)
    {
        m_width = width;
        m_height = height;
    }
	
    void BasicAnimator::SetFPS(Float fps)
    {
        m_fps = fps;
    }
	
    void BasicAnimator::SetLength(Float length)
    {
        m_length = length;
    }
	
    void BasicAnimator::SetTimeWindow(Float renderStart, Float renderEnd)
    {
        m_renderSubset = true;

        m_renderStart = renderStart;
        m_renderEnd = m_length <= renderEnd ? renderEnd : m_length;
    }

    void BasicAnimator::SetBackgroundColour(const RGBA& bgColour)
    {
        m_backgroundColour = bgColour;
    }

	void BasicAnimator::ResetToDefaults()
    {
        m_width            = 1280;
        m_height           = 720;
        m_fps              = 30;
        m_length           = 10;
        m_backgroundColour = RGBA(0.0f, 0.0f, 0.0f);

        m_renderSubset = false;
        m_renderStart  = 0;
        m_renderEnd    = 10;

        m_filePrefix = "out";
    }
}
