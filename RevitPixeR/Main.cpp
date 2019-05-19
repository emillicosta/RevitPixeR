#include "pch.h"
#include "Main.h"
using namespace RevitPixeR;

using namespace System;
using namespace Autodesk::Revit::ApplicationServices;
using namespace Autodesk::Revit::Attributes;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::UI;

using namespace Main;

Result Command::Execute(
	ExternalCommandData^ commandData,
	String^% message,
	ElementSet^ elements)
{
	UIApplication^ uiapp = commandData->Application;
	Document^ doc = uiapp->ActiveUIDocument->Document;
	View3D^ view3d = dynamic_cast<View3D^>(doc->ActiveView);
	if (view3d != nullptr)
	{
		FormsRender^ fr = gcnew FormsRender(commandData);
		fr->ShowDialog();
	}
	else
	TaskDialog::Show("Atenção", "Para renderizar é preciso está em uma visualização 3D");

	return Result::Succeeded;
}
