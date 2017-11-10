#include "pch.h"
#include "BaseModel.h"

using namespace UniversalImage;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Graphics::Imaging;
using namespace concurrency;

BaseModel::BaseModel(Windows::Graphics::Imaging::SoftwareBitmap^ input,
	Windows::UI::Xaml::Controls::Image^ outImage)
	: m_input(input)
	, m_outImage(outImage)
{
}

void BaseModel::resetImage()
{
	SoftwareBitmapSource^ bitmapSource = ref new SoftwareBitmapSource();

	create_task(bitmapSource->SetBitmapAsync(m_input)).then([this, bitmapSource]()
	{
		m_outImage->Source = bitmapSource;
	});
}