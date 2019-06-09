#pragma once

using namespace System;

namespace RevitPixeR {
	public ref class Ribbon : Autodesk::Revit::UI::IExternalApplication
	{
	public:
		virtual Autodesk::Revit::UI::Result OnStartup(
			Autodesk::Revit::UI::UIControlledApplication^ application);

		virtual Autodesk::Revit::UI::Result OnShutdown(
			Autodesk::Revit::UI::UIControlledApplication^ application);
	};
}
