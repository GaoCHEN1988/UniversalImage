#pragma once
#include <opencv2\core\core.hpp>

namespace UniversalImage
{
	class OpenCVHelper
	{
	public:
		static bool TryConvert(Windows::Graphics::Imaging::SoftwareBitmap^ from, cv::Mat& convertedMat);
		static bool GetPointerToPixelData(Windows::Graphics::Imaging::SoftwareBitmap^ bitmap,
			unsigned char** pPixelData, unsigned int* capacity);
	};
}