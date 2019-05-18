#include "pch.h"
#include "SceneDescription.h"


SceneDescription::SceneDescription()
{
}

SceneDescription::SceneDescription(Document^ doc_, int height_, int width_, int n_samples_, int ray_depth_, float fov_, float aperture_, float focalDist_, XYZ^ positionSun, List<ElementId^>^ elem_light_)
{
	doc = doc_;
	height = height_;
	width = width_;
	n_samples = n_samples_;
	ray_depth = ray_depth_;
	fov = fov_;
	aperture = aperture_;
	focalDist = focalDist_;
	sun = positionSun;
	elem_light = elem_light_;

	elementDoc = GetAllModelElements(doc);
	for each(Element^ e in elementDoc)
	{
		allMesh->Add(GetMesh(e));
		allMaterial->Add(GetMaterial(e, doc));
	}


}

Bitmap^ SceneDescription::GetImage()
{
	Bitmap^ img = gcnew Bitmap(width, height);
	
	std::list<ShapeObject*> l = GetObject();

	l.push_back(Sun());
	//l.push_back(centro());
	
	Background* bg = GetBackground();

	rgb al = rgb(0.1f, 0.1f, 0.1f);
	
	Scene* world = new Scene(l, bg, al);

	Shader* shader = new LambertianShader(world);

	Camera* camera = GetCamera();

	std::stringstream ss;

	float t_max = std::numeric_limits<float>::infinity();

	Raytrace::render(ss, camera, world, shader, width, height, n_samples, ray_depth, 0.001f, t_max);
	
	for (int x = 0; x< height; x++) {
		for (int y = 0; y < width; y++) {
			int r, g, b;
			ss >> r >> g >> b;
			System::Drawing::Color newColor = System::Drawing::Color::FromArgb(r, g, b);
			img->SetPixel(y, x, newColor);
		}
	}
	return img;
}

List<Element^>^ SceneDescription::GetAllModelElements(Document^ doc)
{
	List<Element^>^ elements = gcnew List<Element^>();

	FilteredElementCollector^ collector = gcnew FilteredElementCollector(doc);
	collector = collector->WhereElementIsNotElementType();
	for each (Element^ e in collector)
	{
		if (e->Category != nullptr && e->Category->HasMaterialQuantities)
			elements->Add(e);
	}

	return elements;
}

List<Mesh^>^ SceneDescription::GetMesh(Element^ element)
{
	List<Mesh^>^ meshes = gcnew List<Mesh^>();

	Options^ opt = gcnew Options();
	GeometryElement^ geomElem = element->Geometry[opt];
	for each(GeometryObject^ geomObj in geomElem)
	{
		Solid^ geomSolid = dynamic_cast<Solid^>(geomObj);
		if (nullptr != geomSolid)
		{
			for each(Face^ geomFace in geomSolid->Faces)
			{
				Mesh^ mesh = geomFace->Triangulate();
				meshes->Add(mesh);
			}
		}
		else
		{
			GeometryInstance^ geoInstance = dynamic_cast<GeometryInstance^>(geomObj);
			if (nullptr != geoInstance)
			{
				GeometryElement^ symbolGeo = geoInstance->SymbolGeometry;

				for each(GeometryObject^ o2 in symbolGeo)
				{
					Solid^ s = dynamic_cast<Solid^>(o2);
					if (nullptr != s)
					{
						Transform^ instTransform = geoInstance->Transform;
						for each(Face^ geomFace in s->Faces)
						{
							Mesh^ mesh = geomFace->Triangulate();
							mesh = mesh->Transformed[instTransform];
							meshes->Add(mesh);
						}
					}
				}
			}
		}
	}
	return meshes;
}

List<Material^>^ SceneDescription::GetMaterial(Element^ element, Document^ doc)
{
	List<Material^>^ materiais = gcnew List<Material^>();
	Options^ opt = gcnew Options();
	GeometryElement^ geomElem = element->Geometry[opt];
	for each(GeometryObject^ geomObj in geomElem)
	{
		Solid^ geomSolid = dynamic_cast<Solid^>(geomObj);
		if (nullptr != geomSolid)
		{
			for each(Face^ geomFace in geomSolid->Faces)
			{
				ElementId^ elementId = geomFace->MaterialElementId;
				Material^ m = dynamic_cast<Material^>(doc->GetElement(elementId));
				materiais->Add(m);
			}
		}
		else
		{
			GeometryInstance^ geoInstance = dynamic_cast<GeometryInstance^>(geomObj);
			if (nullptr != geoInstance)
			{
				GeometryElement^ symbolGeo = geoInstance->SymbolGeometry;

				for each(GeometryObject^ geometryObject in symbolGeo)
				{
					Solid^ solid = dynamic_cast<Solid^>(geometryObject);
					if (nullptr != solid)
					{

						for each(Face^ geomFace in solid->Faces)
						{
							ElementId^ elementId = geomFace->MaterialElementId;
							Material^ m = dynamic_cast<Material^>(doc->GetElement(elementId));
							materiais->Add(m);
						}
					}
				}
			}
		}
	}
	return materiais;
}

std::list<ShapeObject*> SceneDescription::GetObject()//esse retorno pode gerar erro
{
	std::list<ShapeObject*> l;

	for (int i = 0; i < allMesh->Count; i++)
	{
		//mensagem += "Objeto\n\n";
		std::vector<TriangleObject*> triangles;

		List<Material^>^ allMateriali = allMaterial[i];
		List<Mesh^>^ allMeshi = allMesh[i];

		float xmin = std::numeric_limits<float>::infinity() * -1, xmax = std::numeric_limits<float>::infinity();;
		float ymin = std::numeric_limits<float>::infinity() * -1, ymax = std::numeric_limits<float>::infinity();
		float zmin = std::numeric_limits<float>::infinity() * -1, zmax = std::numeric_limits<float>::infinity();


		for (int j = 0; j < allMesh[i]->Count; j++)
		{
			//Get Material
			ElementId^ id = elementDoc[i]->Id;
			MyMaterial* mat = GetMyMaterial(allMateriali[j], id);
			//double ri =1;
			// mat = new MetalMaterial(new ConstantTexture(kd), ri);
			//mat = new DIalectrisMaterial(new ConstantTexture(kd), ri);

			for (int k = 0; k < allMeshi[j]->NumTriangles; k++)
			{
				//Get points 
				MeshTriangle^ triangle = allMeshi[j]->Triangle[k];

				point3 v1 = point3((float)triangle->Vertex[0]->X, (float)triangle->Vertex[0]->Y, (float)triangle->Vertex[0]->Z);
				xmin = min(v1.x(), xmin);
				ymin = min(v1.y(), ymin);
				zmin = min(v1.z(), zmin);

				xmax = max(v1.x(), xmax);
				ymax = max(v1.y(), ymax);
				zmax = max(v1.z(), zmax);

				point3 v2 = point3((float)triangle->Vertex[1]->X, (float)triangle->Vertex[1]->Y, (float)triangle->Vertex[1]->Z);
				xmin = min(v2.x(), xmin);
				ymin = min(v2.y(), ymin);
				zmin = min(v2.z(), zmin);

				xmax = max(v2.x(), xmax);
				ymax = max(v2.y(), ymax);
				zmax = max(v2.z(), zmax);
				point3 v3 = point3((float)triangle->Vertex[2]->X, (float)triangle->Vertex[2]->Y, (float)triangle->Vertex[2]->Z);
				xmin = min(v3.x(), xmin);
				ymin = min(v3.y(), ymin);
				zmin = min(v3.z(), zmin);

				xmax = max(v3.x(), xmax);
				ymax = max(v3.y(), ymax);
				zmax = max(v3.z(), zmax);


				triangles.push_back(new TriangleObject(mat, v1, v2, v3));// new ElementId(1)));
			}

		}
		point3 mini = point3(xmin, ymin, zmin);
		point3 maxi = point3(xmax, ymax,zmax);
		l.push_back(new MeshObject(nullptr, triangles, new CubeObject(nullptr, mini, maxi)));
	}
	return l;
}

MyMaterial* SceneDescription::GetMyMaterial(Material^ matRevit, ElementId^ id)
{
	float red = static_cast<float>(matRevit->Color->Red) / 255;
	float green = static_cast<float>(matRevit->Color->Green) / 255;
	float blue = static_cast<float>(matRevit->Color->Blue) / 255;

	rgb kd = rgb(red, green, blue);
	
	//TaskDialog::Show("classe material",matRevit->MaterialClass);

	if (matRevit->MaterialClass == "Tecido") {
		//return new LightMaterial(new ConstantTexture(rgb(0.2, 0.2, 0.2)));
	}
	if (matRevit->MaterialClass == "Metal") {
		return new MetalMaterial(new ConstantTexture(kd), 1);
	}

	return new DifuseMaterial(new ConstantTexture(kd));
}

Background* SceneDescription::GetBackground()
{
	rgb lower_left = rgb(0.2f, 0.2f, 0.2f);
	rgb lower_right = rgb(1.f, 0.f, 0.f);
	rgb top_left = rgb(0.4f, 0.4f, 0.4f);
	rgb top_right = rgb(1.f, 1.f, 0.f);

	return new Background(lower_left, lower_right, top_left, top_right);
}

Camera* SceneDescription::GetCamera()
{
	View3D^ view3D = dynamic_cast<View3D^>(doc->ActiveView);
	ViewOrientation3D^ viewOrientation3D = view3D->GetOrientation();
	point3 eye = point3((float)viewOrientation3D->EyePosition->X, (float)viewOrientation3D->EyePosition->Y, (float)viewOrientation3D->EyePosition->Z);// camera position
	vec3 up = vec3((float)viewOrientation3D->UpDirection->X, (float)viewOrientation3D->UpDirection->Y, (float)viewOrientation3D->UpDirection->Z);// up direction of the camera
	point3 lookAt = point3((float)viewOrientation3D->ForwardDirection->X, (float)viewOrientation3D->ForwardDirection->Y, (float)viewOrientation3D->ForwardDirection->Z);// the direction the caemra is looking at
	//TaskDialog::Show("Orientações",viewOrientation3D->EyePosition->ToString() + " "+ viewOrientation3D->UpDirection->ToString() + " "+ viewOrientation3D->ForwardDirection->ToString());
	return new Camera(eye, lookAt, up, fov, (float)(width / height), aperture, focalDist);
}

SphereObject* SceneDescription::Sun() 
{
	//TaskDialog::Show("sol", sun->ToString());
	point3 origin = point3((float)sun->X, (float)sun->Y, (float)sun->Z);
	//TaskDialog::Show("Posição", "minha:" + sun->ToString() + "\nrevit: " + -sun->Y +"; "+ sun->Z +"; "+ sun->Y);
	float radius = 5;
	MyMaterial* m = new LightMaterial(new ConstantTexture(rgb(1,1,1)));
	return new SphereObject(m, origin, radius);
}

/*SphereObject* SceneDescription::centro()
{
	//TaskDialog::Show("sol", sun->ToString());
	point3 origin = point3(0, 0, 1);
	//TaskDialog::Show("Posição", "minha:" + sun->ToString() + "\nrevit: " + -sun->Y +"; "+ sun->Z +"; "+ sun->Y);
	float radius = 1;
	MyMaterial* m = new LightMaterial(new ConstantTexture(rgb(1, 0, 0.9)));
	return new SphereObject(m, origin, radius);
}*/