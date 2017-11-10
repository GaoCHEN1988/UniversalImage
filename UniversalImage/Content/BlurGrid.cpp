#include "pch.h"
#include "BlurGrid.h"

using namespace UniversalImage;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Controls;

BlurGrid::BlurGrid()
{
	initialize();
}

void BlurGrid::setModel(BlurModel^ model)
{
	m_model = model;
}

void BlurGrid::initialize()
{
	StackPanel^ gridStackPanel = ref new StackPanel;

	StackPanel^ sizePanel = ref new StackPanel;
	sizePanel->Orientation = Orientation::Horizontal;
	sizePanel->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	TextBlock ^ sizeText = ref new TextBlock;
	sizeText->Width = 120;
	sizeText->Text = "Size";

	m_sizeBox = ref new TextBox;
	m_sizeBox->Text = "10";
	m_sizeBox->Width = 80;
	m_sizeBox->InputScope = ref new InputScope();
	InputScopeName^ scopeName = ref new InputScopeName();
	scopeName->NameValue = InputScopeNameValue::Number;
	m_sizeBox->InputScope->Names->Append(scopeName);
	sizePanel->Children->Append(sizeText);
	sizePanel->Children->Append(m_sizeBox);


	m_processButton = ref new Button;
	m_processButton->Content = "Process";
	m_processButton->Width = 100;
	m_processButton->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void(::UniversalImage::BlurGrid::*)
		(::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&BlurGrid::processButton_Click);

	m_resetButton = ref new Button;
	m_resetButton->Content = "Reset";
	m_resetButton->Width = 100;
	m_resetButton->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void(::UniversalImage::BlurGrid::*)
		(::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&BlurGrid::resetButton_Click);

	StackPanel^ buttonPanel = ref new StackPanel;
	buttonPanel->Orientation = Orientation::Horizontal;
	buttonPanel->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	buttonPanel->Children->Append(m_processButton);
	buttonPanel->Children->Append(m_resetButton);

	gridStackPanel->Children->Append(sizePanel);
	gridStackPanel->Children->Append(buttonPanel);

	this->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
	this->Children->Append(gridStackPanel);
}

void BlurGrid::processButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	m_model->process(_wtoi(m_sizeBox->Text->Data()));
}

void BlurGrid::resetButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	m_model->resetImage();
}