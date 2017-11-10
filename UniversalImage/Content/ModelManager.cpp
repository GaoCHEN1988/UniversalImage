#include "pch.h"
#include "ModelManager.h"


using namespace UniversalImage;

Platform::Collections::Map<Platform::String^, BaseModel^> ModelManager::m_modelMap;

void ModelManager::updateModels(Windows::Graphics::Imaging::SoftwareBitmap^ input,
	Windows::UI::Xaml::Controls::Image^ outImage)
{
	m_modelMap.Insert("Canny", ref new CannyModel(input, outImage));
	m_modelMap.Insert("Blur", ref new BlurModel(input, outImage));
}

BaseModel^ ModelManager::getModel(Platform::String^ name)
{
	return m_modelMap.Lookup(name);
}
