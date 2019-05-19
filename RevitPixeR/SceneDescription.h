#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <complex>  
#include <vector>
#include <math.h> 
#include <ios>      // std::left
#include <iomanip> // setw
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream> 
#include <msclr\marshal_cppstd.h>


#include <Windows.h>
#include "ShapeObject.h"
#include "ConstantTexture.h"
#include "DifuseMaterial.h"
#include "SphereObject.h"
#include "Background.h"
#include "Scene.h"
#include "Shader.h"
#include "LambertianShader.h"
#include "Camera.h"
#include "Raytrace.h"
#include "TriangleObject.h"
#include "MeshObject.h"
#include "MetalMaterial.h"
#include "DielectricsMaterial.h"
#include "LightMaterial.h"
#include "NoiseTexture.h"
#include "ImageTexture.h"
#include "Light.h"
#include "PointLight.h"

#include <thread>
#include <algorithm>
#pragma once

using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::UI;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace Autodesk::Revit::DB::Visual;

ref class SceneDescription
{
private:
	Document^ doc;
	int height, width, n_samples, ray_depth, countElem;
	float fov, aperture, focalDist;
	List<Element^>^ elementDoc = gcnew List<Element^>();
	List<List<Mesh^>^>^ allMesh = gcnew List<List<Mesh^>^>();
	List<List<Material^>^>^ allMaterial = gcnew List<List<Material^>^>();
	List<ElementId^>^ elem_light;
	XYZ^ sun;

public:
	SceneDescription();
	SceneDescription(Document^ doc, int height_, int width_, 
		int n_samples_, int ray_depth_, float fov_, float aperture_, 
		float focalDist_, XYZ^ positionSun, List<ElementId^>^ elem_light_);
	Bitmap^ GetImage();
	List<Element^>^ GetAllModelElements(Document^ doc);
	List<Mesh^>^ GetMesh(Element^ element);
	List<Material^>^ GetMaterial(Element^ element, Document^ doc);
	std::list<ShapeObject*>  GetObject();
	Background* GetBackground();
	Camera* GetCamera();
	MyMaterial* GetMyMaterial(Material^ matRevit, ElementId^ id);
	SphereObject* Sun();
	SphereObject* centro();

	System::String^ FindTextureBitmapPaths(Material^ material);
	System::String^ FindMetalFinish(Material^ material);

};
