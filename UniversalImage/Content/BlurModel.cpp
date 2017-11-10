#include "pch.h"
#include "BlurModel.h"
#include "OpenCVHelper.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <MemoryBuffer.h>

using namespace UniversalImage;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Graphics::Imaging;
using namespace Microsoft::WRL;
using namespace concurrency;

BlurModel::BlurModel(Windows::Graphics::Imaging::SoftwareBitmap^ input,
	Windows::UI::Xaml::Controls::Image^ outImage)
	: BaseModel(input, outImage)
{
}

void BlurModel::process(int size)
{
	if (!m_input)
		return;

	cv::Mat inputMat, outputMat;
	SoftwareBitmap^ outputBitmap = ref new SoftwareBitmap(m_input->BitmapPixelFormat, m_input->PixelWidth, m_input->PixelHeight, BitmapAlphaMode::Premultiplied);
	if (!(OpenCVHelper::TryConvert(m_input, inputMat) && OpenCVHelper::TryConvert(outputBitmap, outputMat)))
	{
		return;
	}

	if (size <= 0)
		return;

	cv::blur(inputMat, outputMat, cv::Size(size, size));

	SoftwareBitmapSource^ bitmapSource = ref new SoftwareBitmapSource();

	create_task(bitmapSource->SetBitmapAsync(outputBitmap)).then([this, bitmapSource]()
	{
		m_outImage->Source = bitmapSource;
	});
}