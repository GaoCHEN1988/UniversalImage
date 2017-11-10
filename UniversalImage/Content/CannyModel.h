#pragma once
#include "BaseModel.h"

namespace UniversalImage
{
	public ref class CannyModel sealed : public BaseModel
	{
	public:
		CannyModel(Windows::Graphics::Imaging::SoftwareBitmap^ input,
			Windows::UI::Xaml::Controls::Image^ outImage);

		void process(double lowThreshold, double highThreshold);

	};
}