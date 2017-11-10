#pragma once

#include "BaseGrid.h"
#include "BlurModel.h"

namespace UniversalImage
{
	public ref class BlurGrid sealed : public BaseGrid
	{
	public:
		BlurGrid();
		void setModel(BlurModel^ model);

	private:
		void initialize();
		void processButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void resetButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

	private:
		::Windows::UI::Xaml::Controls::Button^ m_processButton;
		::Windows::UI::Xaml::Controls::Button^ m_resetButton;
		::Windows::UI::Xaml::Controls::TextBox^ m_sizeBox;
		BlurModel^ m_model;
	};

}