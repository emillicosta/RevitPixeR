#include "pch.h"
#include "Ribbon.h"
#include <string>
using namespace System;
using namespace System::Reflection;
using namespace System::IO;
using namespace System::Windows;
using namespace System::Windows::Media::Imaging;
using namespace System::Windows::Forms;
using namespace System::Windows::Interop;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

using namespace Autodesk::Revit::ApplicationServices;
using namespace Autodesk::Revit::Attributes;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::UI;

using namespace RibbonPixeR;
using namespace std;

Result Ribbon::OnStartup(UIControlledApplication^ application)
{
	RibbonPanel^ ribbonPanel = application->CreateRibbonPanel("Render");
	// Create a push button to trigger a command add it to the ribbon panel.
	System::String^ thisAssemblyPath = Assembly::GetExecutingAssembly()->Location;
	PushButtonData^ buttonData = gcnew PushButtonData("cmdPixeR", "PixeR CPP", thisAssemblyPath, "PixeRevitCpp.Command");
	PushButton^ pushButton = dynamic_cast<PushButton^>(ribbonPanel->AddItem(buttonData));

	pushButton->ToolTip = "Say hello to the entire world.";

	String^ file = "file:///C:/Tcc/PixeR_Revit/PixeR/chaleira.png";
	Uri^ uriImage = gcnew Uri(file);
	BitmapImage^ largeImage = gcnew BitmapImage(uriImage);
	pushButton->LargeImage = largeImage;

	return Result::Succeeded;
}

Result Ribbon::OnShutdown(UIControlledApplication^ application) 
{
	return Result::Succeeded;
}
