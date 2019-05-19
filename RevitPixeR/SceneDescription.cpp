#include "pch.h"
#include "SceneDescription.h"
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"


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

	std::list<ShapeObject*> objects = GetObject();

	std::list<Light*> lights;

	rgb al;
	if (sun->Z > 0) {
		float a = ((float)sun->Z / 70) / 10;
		al = rgb(a, a, a);
		point3 origin = point3((float)sun->X, (float)sun->Y, (float)sun->Z);
		lights.push_back(new PointLight(origin, rgb(0.7, 0.7, 0.5)));
	}
	else
	{
		al = rgb(0,0,0);
	}
	Background* bg = GetBackground();

	Scene* world = new Scene(objects, lights, bg, al);

	Shader* shader = new LambertianShader(world);

	Camera* camera = GetCamera();

	//std::stringstream ss;
	int dimension = height * width;
	std::vector<rgb> imagj(dimension);

	float t_max = std::numeric_limits<float>::infinity();

	int n_ts = 8;
	std::vector<std::thread> ts(n_ts);
	int n = n_ts;
	while (n >= 1) {
		int height_top = (height * (n * 1.f / n_ts)) - 1;
		int height_bottom = height * ((n - 1) * 1.0 / n_ts);
		int h = height;
		int w = width;
		int s = n_samples;
		int r = ray_depth;
		ts[n - 1] = std::thread(Raytrace::render, std::ref(imagj), camera, world, shader, w, h, height_top, height_bottom,s,r, 0.01f, t_max);
		n--;
	}
	for (int i = 0; i < n_ts; i++) {
		ts[i].join();
	}
	for (int x = 0; x< width; x++) {
		for (int y = 0; y < height ; y++) {
			int r, g, b;
			int position = x + (height - y - 1) * width;
			r = imagj[position].r();
			g = imagj[position].g();
			b = imagj[position].b();
			System::Drawing::Color newColor = System::Drawing::Color::FromArgb(r, g, b);
			img->SetPixel(x,  height - 1 - y, newColor);
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
				GraphicsStyle^ gStyle = dynamic_cast<GraphicsStyle^>( doc->GetElement(geomObj->GraphicsStyleId) );
				if (gStyle != nullptr)
				{
					if (gStyle->GraphicsStyleCategory->Id->IntegerValue == (int)(BuiltInCategory::OST_LightingFixtureSource))
						continue;
				}
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
	for (int i = 0; i < elem_light->Count; i++) {
		if (id == elem_light[i])
			return new LightMaterial(new ConstantTexture(rgb(1,1,1)));
	}

	System::String^ path = FindTextureBitmapPaths(matRevit);
	
	if (path != nullptr ) 
	{
		std::string s = msclr::interop::marshal_as<std::string>(path);
		if (s != "") {
			std::string delimiter = "|";
			std::string s1 = s.substr(0, s.find(delimiter));
			delimiter = "1";
			std::string s2 = s1.substr(s1.find(delimiter));
			delimiter = "C:";
			std::string path_ = s2.substr(0, s2.find(delimiter));
			std::string image_name = "C:/Users/emill/source/repos/RevitPixeR/Texture/" + path_;
			
			/*System::String^ a = msclr::interop::marshal_as<System::String^>(path_);
			TaskDialog::Show("Connected bitmap", a);*/
			
			int width, height, dummy;
			unsigned char* data = stbi_load(image_name.c_str(), &width, &height, &dummy, 3);

			int teste = data[0];
			return new DifuseMaterial(new ImageTexture(data, width, height));
		}
	}
	float red = static_cast<float>(matRevit->Color->Red) / 255;
	float green = static_cast<float>(matRevit->Color->Green) / 255;
	float blue = static_cast<float>(matRevit->Color->Blue) / 255;

	rgb kd = rgb(red, green, blue);
	
	if (matRevit->MaterialClass == "Metal") {
		int m = System::Convert::ToInt32(FindMetalFinish(matRevit));
		
		float index;
		if (m == 0)
			index = 0.f;
		if (m == 1)
			index = 0.33f;
		if (m == 2)
			index = 0.66f;
		if (m == 3)
			index = 1.f;
		
		return new MetalMaterial(new ConstantTexture(kd), index);
	}

	if (matRevit->MaterialClass == "Mirror") {
		return new MetalMaterial(new ConstantTexture(rgb(0.74f, 0.74f,0.74f)), 0.f);
	}

	if (matRevit->MaterialClass == "Vidro") {
		return new DielectricsMaterial(new ConstantTexture(rgb(1,1,1)), 1.5f);
	}

	if (matRevit->MaterialClass == "Pedra" && matRevit->Name == "Mármore") {
		return new MetalMaterial(new NoiseTexture(0.3f), 1.f);
	}

	//TaskDialog::Show("classe material", matRevit->MaterialClass);

	return new DifuseMaterial(new ConstantTexture(kd));
}

Background* SceneDescription::GetBackground()
{
	/*if (sun->Z > 0) {
		rgb lower_left = rgb(sun->Z/130, sun->Z/130, sun->Z/130);
		rgb lower_right = rgb(1.f, 0.f, 0.f);
		rgb top_left = rgb(sun->Z / 130, sun->Z / 130, sun->Z / 130);
		rgb top_right = rgb(1.f, 1.f, 0.f);

		return new Background(lower_left, lower_right, top_left, top_right);
	}
	else
	{*/
		return new Background(rgb(1,1,1), rgb(1, 1, 1), rgb(0.5, 0.7, 1), rgb(0.5, 0.7, 1));
	//}
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
	point3 origin = point3((float)sun->X, (float)sun->Y, (float)sun->Z);
	float radius = 50;
	MyMaterial* m = new LightMaterial(new ConstantTexture(rgb(1,1,1)));
	return new SphereObject(m, origin, radius);
}

SphereObject* SceneDescription::centro()
{
	point3 origin = point3(0,0,10);
	float radius = 10;
	std::string image_name = "C:/Users/emill/source/repos/RevitPixeR/Texture/1/Mats/Brick_Non_Uniform_Running_Burgundy.png";
	int width, height, dummy;
	unsigned char* data = stbi_load(image_name.c_str(), &width, &height, &dummy, 3);
	rgb kd = rgb(0.7f,0.7f,0.7f);
	MyMaterial* m = new MetalMaterial(new ConstantTexture(kd), 0.f);
	return new SphereObject(m, origin, radius);
}

System::String^ SceneDescription::FindTextureBitmapPaths(Material^ material)
{
	ElementId^ appearanceAssetId = material->AppearanceAssetId;

	AppearanceAssetElement^ appearanceAssetElem = dynamic_cast<AppearanceAssetElement^>  (doc->GetElement(appearanceAssetId));

	Asset^ asset = appearanceAssetElem->GetRenderingAsset();

	int size = asset->Size;
	for (int assetIdx = 0; assetIdx < size; assetIdx++)
	{
		AssetProperty^ aProperty = asset[assetIdx];

		if (aProperty->NumberOfConnectedProperties < 1)
			continue;
		Asset^ connectedAsset = dynamic_cast<Asset^>(aProperty->GetConnectedProperty(0));

		// We are only checking for bitmap connected assets.

		if (connectedAsset->Name == "UnifiedBitmapSchema")
		{
			AssetPropertyString^ path = dynamic_cast<AssetPropertyString^>(connectedAsset[UnifiedBitmap::UnifiedbitmapBitmap]);
			return path->Value;
		}
	}
}


System::String^ SceneDescription::FindMetalFinish(Material^ material)
{
	ElementId^ appearanceAssetId = material->AppearanceAssetId;

	AppearanceAssetElement^ appearanceAssetElem = dynamic_cast<AppearanceAssetElement^>  (doc->GetElement(appearanceAssetId));

	Asset^ asset = appearanceAssetElem->GetRenderingAsset();
	System::String^ mens = "";

	int size = asset->Size;
	for (int assetIdx = 0; assetIdx < size; assetIdx++)
	{
		AssetProperty^ aProperty = asset[assetIdx];
		System::Type^ type = aProperty->GetType();
		Object^ apVal = nullptr;
		auto prop = type->GetProperty("Value");
		if (prop != nullptr)
			apVal = prop->GetValue(aProperty);
		else
		{
			apVal = "";
		}
		if (aProperty->Name  == "metal_finish"){
			return apVal->ToString();
		}

	}
	return "";
}
