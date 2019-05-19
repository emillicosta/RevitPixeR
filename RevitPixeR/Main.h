#pragma once
#include "FormsRender.h"

namespace Main {
	[Autodesk::Revit::Attributes::Transaction(Autodesk::Revit::Attributes::TransactionMode::Manual)]

	[Autodesk::Revit::Attributes::Regeneration(Autodesk::Revit::Attributes::RegenerationOption::Manual)]

	public ref class Command : Autodesk::Revit::UI::IExternalCommand
	{
	public:
		virtual Autodesk::Revit::UI::Result Execute(
			Autodesk::Revit::UI::ExternalCommandData^ commandData,
			System::String^% message,
			Autodesk::Revit::DB::ElementSet^ elements);
	};
}


