#pragma once
#include "BaseModel.h"

namespace UniversalImage
{
	public ref class BlurModel sealed : public BaseModel
	{
	public:
		BlurModel(Windows::Graphics::Imaging::SoftwareBitmap^ input,
			Windows::UI::Xaml::Controls::Image^ outImage);

		void process(int size);

	};
}