#pragma once

#include "BaseGrid.h"
#include "CannyModel.h"

namespace UniversalImage
{
	public ref class CannyGrid sealed : public BaseGrid
	{
	public:
		CannyGrid();
		void setModel(CannyModel^ model);

	private:
		void initialize();
		void processButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void resetButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	
	private:
		::Windows::UI::Xaml::Controls::Button^ m_processButton;
		::Windows::UI::Xaml::Controls::Button^ m_resetButton;
		::Windows::UI::Xaml::Controls::TextBox^ m_lowThresholdBox;
		::Windows::UI::Xaml::Controls::TextBox^ m_highThresholdBox;
		CannyModel^ m_model;
	};

}