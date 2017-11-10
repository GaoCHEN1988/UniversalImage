//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "Content\ModelManager.h"
#include "Content\CannyGrid.h"
#include "Content\BlurGrid.h"

using namespace UniversalImage;
using namespace Platform;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Graphics::Imaging;
using namespace Microsoft::WRL;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace concurrency;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();

	ModelManager::updateModels(m_storedBitmap, storedImage);
}

void UniversalImage::MainPage::LoadImageButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FileOpenPicker^ fileOpenPicker = ref new FileOpenPicker();
	fileOpenPicker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;
	fileOpenPicker->FileTypeFilter->Append(".jpg");
	fileOpenPicker->FileTypeFilter->Append(".png");
	fileOpenPicker->FileTypeFilter->Append(".bmp");

	fileOpenPicker->ViewMode = PickerViewMode::Thumbnail;

	create_task(fileOpenPicker->PickSingleFileAsync()).then([this](StorageFile^ file)
	{
		if (file != nullptr)
		{
			create_task(file->OpenAsync(FileAccessMode::Read)).then([this](IRandomAccessStream^ stream)
			{
				// Create the decoder from the stream
				create_task(BitmapDecoder::CreateAsync(stream)).then([this](BitmapDecoder^ decoder)
				{
					// Get the SoftwareBitmap representation of the file
					create_task(decoder->GetSoftwareBitmapAsync()).then([this](SoftwareBitmap^ image)
					{
						m_storedBitmap = image;

						if (m_storedBitmap->BitmapPixelFormat != BitmapPixelFormat::Bgra8
							|| m_storedBitmap->BitmapAlphaMode != BitmapAlphaMode::Premultiplied)
						{
							m_storedBitmap = SoftwareBitmap::Convert(m_storedBitmap, BitmapPixelFormat::Bgra8, BitmapAlphaMode::Premultiplied);
							SoftwareBitmapSource^ bitmapSource = ref new SoftwareBitmapSource();

							create_task(bitmapSource->SetBitmapAsync(m_storedBitmap)).then([this, bitmapSource]()
							{
								storedImage->Source = bitmapSource;

								ModelManager::updateModels(m_storedBitmap, storedImage);
							});
						}
					});
				});
			});
		}
	});

}

void UniversalImage::MainPage::SaveImageButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (storedImage->Source == nullptr)
		return;

	RenderTargetBitmap^ storedBitmap = ref new RenderTargetBitmap;
	create_task(storedBitmap->RenderAsync(storedImage)).then([this, storedBitmap]()
	{
		FileSavePicker^ picker = ref new FileSavePicker();
		auto imgExtensions = ref new Platform::Collections::Vector<String^>();
		imgExtensions->Append(".jpg");
		picker->FileTypeChoices->Insert("jpg", imgExtensions);

		create_task(picker->PickSaveFileAsync()).then([this, storedBitmap](StorageFile^ saveFile)
		{
			if (saveFile == nullptr)
				return;

			create_task(saveFile->OpenAsync(FileAccessMode::ReadWrite)).then([this, storedBitmap](IRandomAccessStream^ stream)
			{
				create_task(BitmapEncoder::CreateAsync(BitmapEncoder::JpegEncoderId, stream)).then([this, storedBitmap](BitmapEncoder^ encoder)
				{
					create_task(storedBitmap->GetPixelsAsync()).then([this, storedBitmap, encoder](IBuffer^ buffer)
					{
						DataReader^ dataReader = DataReader::FromBuffer(buffer);
						Platform::Array<unsigned char, 1>^ pixels = ref new Platform::Array<unsigned char, 1>(buffer->Length);
						dataReader->ReadBytes(pixels);
						encoder->SetPixelData(BitmapPixelFormat::Bgra8, BitmapAlphaMode::Ignore, storedBitmap->PixelWidth, storedBitmap->PixelHeight, 96.0, 86.0, pixels);
						create_task(encoder->FlushAsync());
					});
				});
			});
		});
	});
}

void UniversalImage::MainPage::CannyButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ModulePanel->Children->Clear();
	MainSplitView->IsPaneOpen = true;

	CannyGrid^ canny = ref new CannyGrid;
	canny->setModel((CannyModel^)ModelManager::getModel("Canny"));
	ModulePanel->Children->Append(canny);
}


void UniversalImage::MainPage::BlurButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ModulePanel->Children->Clear();
	MainSplitView->IsPaneOpen = true;

	BlurGrid^ blur = ref new BlurGrid;
	blur->setModel((BlurModel^)ModelManager::getModel("Blur"));
	ModulePanel->Children->Append(blur);
}


