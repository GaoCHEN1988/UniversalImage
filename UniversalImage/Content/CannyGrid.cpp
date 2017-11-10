#include "pch.h"
#include "CannyGrid.h"

using namespace UniversalImage;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Controls;

CannyGrid::CannyGrid()
{
	initialize();
}

void CannyGrid::setModel(CannyModel^ model)
{
	m_model = model;
}

void CannyGrid::initialize()
{
	StackPanel^ gridStackPanel = ref new StackPanel;

	StackPanel^ lowThresholdPanel = ref new StackPanel;
	lowThresholdPanel->Orientation = Orientation::Horizontal;
	lowThresholdPanel->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	TextBlock ^ lowThresholdText = ref new TextBlock;
	lowThresholdText->Width = 120;
	lowThresholdText->Text = "Low Threshold";

	m_lowThresholdBox = ref new TextBox;
	m_lowThresholdBox->Text = "2";
	m_lowThresholdBox->Width = 80;
	m_lowThresholdBox->InputScope = ref new InputScope();
	InputScopeName^ scopeName = ref new InputScopeName();
	scopeName->NameValue = InputScopeNameValue::Number;
	m_lowThresholdBox->InputScope->Names->Append(scopeName);
	lowThresholdPanel->Children->Append(lowThresholdText);
	lowThresholdPanel->Children->Append(m_lowThresholdBox);

	StackPanel^ highThresholdPanel = ref new StackPanel;
	highThresholdPanel->Orientation = Orientation::Horizontal;
	highThresholdPanel->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	TextBlock ^ highThresholdText = ref new TextBlock;
	highThresholdText->Width = 120;
	highThresholdText->Text = "High Threshold";
	m_highThresholdBox = ref new TextBox;
	m_highThresholdBox->Text = "20";
	m_highThresholdBox->Width = 80;
	m_highThresholdBox->InputScope = ref new InputScope();
	scopeName = ref new InputScopeName();
	m_highThresholdBox->InputScope->Names->Append(scopeName);
	highThresholdPanel->Children->Append(highThresholdText);
	highThresholdPanel->Children->Append(m_highThresholdBox);

	m_processButton = ref new Button;
	m_processButton->Content = "Process";
	m_processButton->Width = 100;
	m_processButton->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void(::UniversalImage::CannyGrid::*)
		(::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&CannyGrid::processButton_Click);

	m_resetButton = ref new Button;
	m_resetButton->Content = "Reset";
	m_resetButton->Width = 100;
	m_resetButton->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void(::UniversalImage::CannyGrid::*)
		(::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&CannyGrid::resetButton_Click);
	
	StackPanel^ buttonPanel = ref new StackPanel;
	buttonPanel->Orientation = Orientation::Horizontal;
	buttonPanel->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	buttonPanel->Children->Append(m_processButton);
	buttonPanel->Children->Append(m_resetButton);

	gridStackPanel->Children->Append(lowThresholdPanel);
	gridStackPanel->Children->Append(highThresholdPanel);
	gridStackPanel->Children->Append(buttonPanel);

	this->Children->Append(gridStackPanel);
}

void CannyGrid::processButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	m_model->process(_wtof(m_lowThresholdBox->Text->Data()),
		_wtof(m_highThresholdBox->Text->Data()));
}

void CannyGrid::resetButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	m_model->resetImage();
}