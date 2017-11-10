#pragma once
#include <collection.h>
#include "CannyModel.h"
#include "BlurModel.h"

namespace UniversalImage
{

	ref class ModelManager : Windows::UI::Xaml::DependencyObject
	{
	public:
		static void updateModels(Windows::Graphics::Imaging::SoftwareBitmap^ input,
			Windows::UI::Xaml::Controls::Image^ outImage);

		static BaseModel^ getModel(Platform::String^ name);

	private:
		static Platform::Collections::Map<Platform::String^, BaseModel^> m_modelMap;
	};
}