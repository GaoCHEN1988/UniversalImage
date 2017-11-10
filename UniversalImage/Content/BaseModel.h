#pragma once
#include <opencv2\core\core.hpp>

namespace UniversalImage
{
	public ref class BaseModel : Windows::UI::Xaml::DependencyObject
	{
	internal:
		BaseModel(Windows::Graphics::Imaging::SoftwareBitmap^ input,
			Windows::UI::Xaml::Controls::Image^ outImage);

	public:
	    void resetImage();

	internal:

		Windows::Graphics::Imaging::SoftwareBitmap^ m_input;
		Windows::UI::Xaml::Controls::Image^ m_outImage;
	};
}