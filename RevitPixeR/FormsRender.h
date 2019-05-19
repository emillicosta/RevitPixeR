#include <string>
#include <msclr\marshal_cppstd.h>
#include <chrono>
#include "SceneDescription.h"
#include "FormsImage.h"
#include "FormLight.h"
#include "PSA.h"
#pragma once

namespace RevitPixeR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Collections::Generic;
	using namespace Autodesk::Revit::DB;
	using namespace Autodesk::Revit::UI;
	using namespace std;

	/// <summary>
	/// Sumário para FormsRender
	/// </summary>
	public ref class FormsRender : public System::Windows::Forms::Form
	{
	private:
		ExternalCommandData^ commandData;
		UIApplication^ uiapp;
		Document^ doc;
		List<ElementId^>^ lights_on = gcnew List<ElementId^>();

		int day, month, year, hour, min;
		
	public:
		FormsRender(ExternalCommandData^ commandData_)
		{
			commandData = commandData_;
			uiapp = commandData->Application;
			doc = uiapp->ActiveUIDocument->Document;

			lights_on = GetElementLight(doc);

			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Limpar os recursos que estão sendo usados.
		/// </summary>
		~FormsRender()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^ groupBoxDetalhes;
	private: System::Windows::Forms::ComboBox^ comboBoxQuality;
	private: System::Windows::Forms::TextBox^ textBoxWidth;
	private: System::Windows::Forms::TextBox^ textBoxHeight;
	private: System::Windows::Forms::Label^ labelpx2;
	private: System::Windows::Forms::Label^ labelpx1;
	private: System::Windows::Forms::Label^ labelQuality;
	private: System::Windows::Forms::Label^ labelWidth;
	private: System::Windows::Forms::Label^ labelHeight;
	private: System::Windows::Forms::GroupBox^ groupBoxCamera;
	private: System::Windows::Forms::TextBox^ textBoxFocalDist;
	private: System::Windows::Forms::TextBox^ textBoxAperture;
	private: System::Windows::Forms::TextBox^ textBoxFov;
	private: System::Windows::Forms::Label^ labelAperture;
	private: System::Windows::Forms::Label^ label1FocalDist;
	private: System::Windows::Forms::Label^ labelFov;
	private: System::Windows::Forms::GroupBox^ groupBoxLighting;
	private: System::Windows::Forms::Label^ labelLongitude;
	private: System::Windows::Forms::Label^ labelLatitude;
	private: System::Windows::Forms::Label^ labelDateHour;
	private: System::Windows::Forms::Label^ labelSky;
	private: System::Windows::Forms::Label^ labelArtificial;
	private: System::Windows::Forms::ComboBox^ comboBoxSky;
	private: System::Windows::Forms::MaskedTextBox^ maskedTextBoxDateHour;
	private: System::Windows::Forms::TextBox^ textBoxLongitude;
	private: System::Windows::Forms::TextBox^ textBoxLatitude;
	private: System::Windows::Forms::Button^ buttonLight;
	private: System::Windows::Forms::Button^ buttonRender;

	private:
		/// <summary>
		/// Variável de designer necessária.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necessário para suporte ao Designer - não modifique 
		/// o conteúdo deste método com o editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FormsRender::typeid));
			this->groupBoxDetalhes = (gcnew System::Windows::Forms::GroupBox());
			this->comboBoxQuality = (gcnew System::Windows::Forms::ComboBox());
			this->textBoxWidth = (gcnew System::Windows::Forms::TextBox());
			this->textBoxHeight = (gcnew System::Windows::Forms::TextBox());
			this->labelpx2 = (gcnew System::Windows::Forms::Label());
			this->labelpx1 = (gcnew System::Windows::Forms::Label());
			this->labelQuality = (gcnew System::Windows::Forms::Label());
			this->labelWidth = (gcnew System::Windows::Forms::Label());
			this->labelHeight = (gcnew System::Windows::Forms::Label());
			this->groupBoxCamera = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxFocalDist = (gcnew System::Windows::Forms::TextBox());
			this->textBoxAperture = (gcnew System::Windows::Forms::TextBox());
			this->textBoxFov = (gcnew System::Windows::Forms::TextBox());
			this->labelAperture = (gcnew System::Windows::Forms::Label());
			this->label1FocalDist = (gcnew System::Windows::Forms::Label());
			this->labelFov = (gcnew System::Windows::Forms::Label());
			this->groupBoxLighting = (gcnew System::Windows::Forms::GroupBox());
			this->buttonLight = (gcnew System::Windows::Forms::Button());
			this->comboBoxSky = (gcnew System::Windows::Forms::ComboBox());
			this->maskedTextBoxDateHour = (gcnew System::Windows::Forms::MaskedTextBox());
			this->textBoxLongitude = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLatitude = (gcnew System::Windows::Forms::TextBox());
			this->labelLongitude = (gcnew System::Windows::Forms::Label());
			this->labelLatitude = (gcnew System::Windows::Forms::Label());
			this->labelDateHour = (gcnew System::Windows::Forms::Label());
			this->labelSky = (gcnew System::Windows::Forms::Label());
			this->labelArtificial = (gcnew System::Windows::Forms::Label());
			this->buttonRender = (gcnew System::Windows::Forms::Button());
			this->groupBoxDetalhes->SuspendLayout();
			this->groupBoxCamera->SuspendLayout();
			this->groupBoxLighting->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBoxDetalhes
			// 
			this->groupBoxDetalhes->Controls->Add(this->comboBoxQuality);
			this->groupBoxDetalhes->Controls->Add(this->textBoxWidth);
			this->groupBoxDetalhes->Controls->Add(this->textBoxHeight);
			this->groupBoxDetalhes->Controls->Add(this->labelpx2);
			this->groupBoxDetalhes->Controls->Add(this->labelpx1);
			this->groupBoxDetalhes->Controls->Add(this->labelQuality);
			this->groupBoxDetalhes->Controls->Add(this->labelWidth);
			this->groupBoxDetalhes->Controls->Add(this->labelHeight);
			this->groupBoxDetalhes->Location = System::Drawing::Point(6, 6);
			this->groupBoxDetalhes->Name = L"groupBoxDetalhes";
			this->groupBoxDetalhes->Size = System::Drawing::Size(271, 76);
			this->groupBoxDetalhes->TabIndex = 0;
			this->groupBoxDetalhes->TabStop = false;
			this->groupBoxDetalhes->Text = L"Detalhes da imagem";
			// 
			// comboBoxQuality
			// 
			this->comboBoxQuality->FormattingEnabled = true;
			this->comboBoxQuality->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Baixa", L"Média", L"Alta" });
			this->comboBoxQuality->Location = System::Drawing::Point(80, 46);
			this->comboBoxQuality->Name = L"comboBoxQuality";
			this->comboBoxQuality->Size = System::Drawing::Size(121, 21);
			this->comboBoxQuality->TabIndex = 7;
			this->comboBoxQuality->SelectedIndex = 0;
			// 
			// textBoxWidth
			// 
			this->textBoxWidth->Location = System::Drawing::Point(195, 17);
			this->textBoxWidth->Name = L"textBoxWidth";
			this->textBoxWidth->Size = System::Drawing::Size(35, 20);
			this->textBoxWidth->TabIndex = 6;
			this->textBoxWidth->Text = L"200";
			this->textBoxWidth->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &FormsRender::TextBox1_KeyPress);
			// 
			// textBoxHeight
			// 
			this->textBoxHeight->Location = System::Drawing::Point(46, 17);
			this->textBoxHeight->Name = L"textBoxHeight";
			this->textBoxHeight->Size = System::Drawing::Size(35, 20);
			this->textBoxHeight->TabIndex = 5;
			this->textBoxHeight->Text = L"200";
			this->textBoxHeight->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &FormsRender::TextBox1_KeyPress);
			// 
			// labelpx2
			// 
			this->labelpx2->AutoSize = true;
			this->labelpx2->Location = System::Drawing::Point(87, 20);
			this->labelpx2->Name = L"labelpx2";
			this->labelpx2->Size = System::Drawing::Size(18, 13);
			this->labelpx2->TabIndex = 4;
			this->labelpx2->Text = L"px";
			// 
			// labelpx1
			// 
			this->labelpx1->AutoSize = true;
			this->labelpx1->Location = System::Drawing::Point(237, 20);
			this->labelpx1->Name = L"labelpx1";
			this->labelpx1->Size = System::Drawing::Size(18, 13);
			this->labelpx1->TabIndex = 3;
			this->labelpx1->Text = L"px";
			// 
			// labelQuality
			// 
			this->labelQuality->AutoSize = true;
			this->labelQuality->Location = System::Drawing::Point(6, 49);
			this->labelQuality->Name = L"labelQuality";
			this->labelQuality->Size = System::Drawing::Size(55, 13);
			this->labelQuality->TabIndex = 2;
			this->labelQuality->Text = L"Qualidade";
			// 
			// labelWidth
			// 
			this->labelWidth->AutoSize = true;
			this->labelWidth->Location = System::Drawing::Point(146, 20);
			this->labelWidth->Name = L"labelWidth";
			this->labelWidth->Size = System::Drawing::Size(43, 13);
			this->labelWidth->TabIndex = 1;
			this->labelWidth->Text = L"Largura";
			// 
			// labelHeight
			// 
			this->labelHeight->AutoSize = true;
			this->labelHeight->Location = System::Drawing::Point(6, 20);
			this->labelHeight->Name = L"labelHeight";
			this->labelHeight->Size = System::Drawing::Size(34, 13);
			this->labelHeight->TabIndex = 0;
			this->labelHeight->Text = L"Altura";
			// 
			// groupBoxCamera
			// 
			this->groupBoxCamera->Controls->Add(this->textBoxFocalDist);
			this->groupBoxCamera->Controls->Add(this->textBoxAperture);
			this->groupBoxCamera->Controls->Add(this->textBoxFov);
			this->groupBoxCamera->Controls->Add(this->labelAperture);
			this->groupBoxCamera->Controls->Add(this->label1FocalDist);
			this->groupBoxCamera->Controls->Add(this->labelFov);
			this->groupBoxCamera->Location = System::Drawing::Point(6, 88);
			this->groupBoxCamera->Name = L"groupBoxCamera";
			this->groupBoxCamera->Size = System::Drawing::Size(271, 72);
			this->groupBoxCamera->TabIndex = 1;
			this->groupBoxCamera->TabStop = false;
			this->groupBoxCamera->Text = L"Câmera";
			// 
			// textBoxFocalDist
			// 
			this->textBoxFocalDist->Location = System::Drawing::Point(90, 42);
			this->textBoxFocalDist->Name = L"textBoxFocalDist";
			this->textBoxFocalDist->Size = System::Drawing::Size(35, 20);
			this->textBoxFocalDist->TabIndex = 5;
			this->textBoxFocalDist->Text = L"5";
			this->textBoxFocalDist->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &FormsRender::TextBox1_KeyPress_double);
			// 
			// textBoxAperture
			// 
			this->textBoxAperture->Location = System::Drawing::Point(195, 18);
			this->textBoxAperture->Name = L"textBoxAperture";
			this->textBoxAperture->Size = System::Drawing::Size(35, 20);
			this->textBoxAperture->TabIndex = 4;
			this->textBoxAperture->Text = L"0";
			this->textBoxAperture->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &FormsRender::TextBox1_KeyPress_double);
			// 
			// textBoxFov
			// 
			this->textBoxFov->Location = System::Drawing::Point(90, 15);
			this->textBoxFov->Name = L"textBoxFov";
			this->textBoxFov->Size = System::Drawing::Size(35, 20);
			this->textBoxFov->TabIndex = 3;
			this->textBoxFov->Text = L"45";
			this->textBoxFov->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &FormsRender::TextBox1_KeyPress_double);
			// 
			// labelAperture
			// 
			this->labelAperture->AutoSize = true;
			this->labelAperture->Location = System::Drawing::Point(146, 18);
			this->labelAperture->Name = L"labelAperture";
			this->labelAperture->Size = System::Drawing::Size(47, 13);
			this->labelAperture->TabIndex = 2;
			this->labelAperture->Text = L"Abertura";
			// 
			// label1FocalDist
			// 
			this->label1FocalDist->AutoSize = true;
			this->label1FocalDist->Location = System::Drawing::Point(6, 45);
			this->label1FocalDist->Name = L"label1FocalDist";
			this->label1FocalDist->Size = System::Drawing::Size(77, 13);
			this->label1FocalDist->TabIndex = 1;
			this->label1FocalDist->Text = L"Distância focal";
			// 
			// labelFov
			// 
			this->labelFov->AutoSize = true;
			this->labelFov->Location = System::Drawing::Point(6, 18);
			this->labelFov->Name = L"labelFov";
			this->labelFov->Size = System::Drawing::Size(83, 13);
			this->labelFov->TabIndex = 0;
			this->labelFov->Text = L"Campo de visão";
			// 
			// groupBoxLighting
			// 
			this->groupBoxLighting->Controls->Add(this->buttonLight);
			this->groupBoxLighting->Controls->Add(this->comboBoxSky);
			this->groupBoxLighting->Controls->Add(this->maskedTextBoxDateHour);
			this->groupBoxLighting->Controls->Add(this->textBoxLongitude);
			this->groupBoxLighting->Controls->Add(this->textBoxLatitude);
			this->groupBoxLighting->Controls->Add(this->labelLongitude);
			this->groupBoxLighting->Controls->Add(this->labelLatitude);
			this->groupBoxLighting->Controls->Add(this->labelDateHour);
			this->groupBoxLighting->Controls->Add(this->labelSky);
			this->groupBoxLighting->Controls->Add(this->labelArtificial);
			this->groupBoxLighting->Location = System::Drawing::Point(8, 170);
			this->groupBoxLighting->Name = L"groupBoxLighting";
			this->groupBoxLighting->Size = System::Drawing::Size(268, 155);
			this->groupBoxLighting->TabIndex = 2;
			this->groupBoxLighting->TabStop = false;
			this->groupBoxLighting->Text = L"Iluminação";
			// 
			// buttonLight
			// 
			this->buttonLight->Location = System::Drawing::Point(75, 16);
			this->buttonLight->Name = L"buttonLight";
			this->buttonLight->Size = System::Drawing::Size(123, 25);
			this->buttonLight->TabIndex = 9;
			this->buttonLight->Text = L"Selecionar";
			this->buttonLight->UseVisualStyleBackColor = true;
			this->buttonLight->Click += gcnew System::EventHandler(this, &FormsRender::ButtonLight_Click);
			// 
			// comboBoxSky
			// 
			this->comboBoxSky->FormattingEnabled = true;
			this->comboBoxSky->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Céu Aberto", L"Parcialmente Nublado", L"Nublado" });
			this->comboBoxSky->Location = System::Drawing::Point(75, 47);
			this->comboBoxSky->Name = L"comboBoxSky";
			this->comboBoxSky->Size = System::Drawing::Size(121, 21);
			this->comboBoxSky->TabIndex = 8;
			this->comboBoxSky->SelectedIndex = 0;
			// 
			// maskedTextBoxDateHour
			// 
			this->maskedTextBoxDateHour->Location = System::Drawing::Point(78, 80);
			this->maskedTextBoxDateHour->Mask = L"00/00/0000 90:00";
			this->maskedTextBoxDateHour->Name = L"maskedTextBoxDateHour";
			this->maskedTextBoxDateHour->Size = System::Drawing::Size(121, 20);
			this->maskedTextBoxDateHour->TabIndex = 7;
			this->maskedTextBoxDateHour->Text = L"110320190800";
			this->maskedTextBoxDateHour->ValidatingType = System::DateTime::typeid;
			// 
			// textBoxLongitude
			// 
			this->textBoxLongitude->Location = System::Drawing::Point(204, 108);
			this->textBoxLongitude->Name = L"textBoxLongitude";
			this->textBoxLongitude->Size = System::Drawing::Size(49, 20);
			this->textBoxLongitude->TabIndex = 6;
			this->textBoxLongitude->Text = L"-35,2";
			this->textBoxLongitude->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &FormsRender::TextBoxLongitude_KeyPress);
			// 
			// textBoxLatitude
			// 
			this->textBoxLatitude->Location = System::Drawing::Point(70, 108);
			this->textBoxLatitude->Name = L"textBoxLatitude";
			this->textBoxLatitude->Size = System::Drawing::Size(53, 20);
			this->textBoxLatitude->TabIndex = 5;
			this->textBoxLatitude->Text = L"-5,7";
			this->textBoxLatitude->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &FormsRender::TextBoxLongitude_KeyPress);
			// 
			// labelLongitude
			// 
			this->labelLongitude->AutoSize = true;
			this->labelLongitude->Location = System::Drawing::Point(144, 111);
			this->labelLongitude->Name = L"labelLongitude";
			this->labelLongitude->Size = System::Drawing::Size(54, 13);
			this->labelLongitude->TabIndex = 4;
			this->labelLongitude->Text = L"Longitude";
			// 
			// labelLatitude
			// 
			this->labelLatitude->AutoSize = true;
			this->labelLatitude->Location = System::Drawing::Point(6, 111);
			this->labelLatitude->Name = L"labelLatitude";
			this->labelLatitude->Size = System::Drawing::Size(45, 13);
			this->labelLatitude->TabIndex = 3;
			this->labelLatitude->Text = L"Latitude";
			// 
			// labelDateHour
			// 
			this->labelDateHour->AutoSize = true;
			this->labelDateHour->Location = System::Drawing::Point(4, 83);
			this->labelDateHour->Name = L"labelDateHour";
			this->labelDateHour->Size = System::Drawing::Size(51, 13);
			this->labelDateHour->TabIndex = 2;
			this->labelDateHour->Text = L"Dia/Hora";
			// 
			// labelSky
			// 
			this->labelSky->AutoSize = true;
			this->labelSky->Location = System::Drawing::Point(4, 55);
			this->labelSky->Name = L"labelSky";
			this->labelSky->Size = System::Drawing::Size(65, 13);
			this->labelSky->TabIndex = 1;
			this->labelSky->Text = L"Tipo do Céu";
			// 
			// labelArtificial
			// 
			this->labelArtificial->AutoSize = true;
			this->labelArtificial->Location = System::Drawing::Point(4, 21);
			this->labelArtificial->Name = L"labelArtificial";
			this->labelArtificial->Size = System::Drawing::Size(43, 13);
			this->labelArtificial->TabIndex = 0;
			this->labelArtificial->Text = L"Artificial";
			// 
			// buttonRender
			// 
			this->buttonRender->Location = System::Drawing::Point(160, 336);
			this->buttonRender->Name = L"buttonRender";
			this->buttonRender->Size = System::Drawing::Size(106, 32);
			this->buttonRender->TabIndex = 3;
			this->buttonRender->Text = L"Renderizar";
			this->buttonRender->UseVisualStyleBackColor = true;
			this->buttonRender->Click += gcnew System::EventHandler(this, &FormsRender::ButtonRender_Click);
			// 
			// FormsRender
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 400);
			this->Controls->Add(this->buttonRender);
			this->Controls->Add(this->groupBoxLighting);
			this->Controls->Add(this->groupBoxCamera);
			this->Controls->Add(this->groupBoxDetalhes);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormsRender";
			this->Text = L"PixeR";
			this->groupBoxDetalhes->ResumeLayout(false);
			this->groupBoxDetalhes->PerformLayout();
			this->groupBoxCamera->ResumeLayout(false);
			this->groupBoxCamera->PerformLayout();
			this->groupBoxLighting->ResumeLayout(false);
			this->groupBoxLighting->PerformLayout();
			this->ResumeLayout(false);

		}

		Void ButtonLight_Click(System::Object^ sender, System::EventArgs^ e)
		{
			FormLight^ fl = gcnew FormLight(commandData, lights_on);
			fl->ShowDialog();
			lights_on = fl->GetLights();
		}
		Void ButtonRender_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (textBoxHeight->Text != "")
			{
				if (textBoxWidth->Text != "")
				{
					if (comboBoxQuality->SelectedIndex != -1)
					{
						if (textBoxFov->Text != "")
						{
							if (textBoxAperture->Text != "")
							{
								if (textBoxFocalDist->Text != "")
								{
									if (comboBoxSky->SelectedIndex != -1)
									{
										if (DateHourIsValid())
										{
											if (textBoxLatitude->Text!= "")
											{
												if (textBoxLongitude->Text != "")
												{
													SceneDescription^ s = gcnew SceneDescription(doc, GetHeight(), GetWidth(), GetSample(),
														GetRayDepth(), GetFov(), GetAperture(), GetFocusDist(), GetPositionSun(), lights_on);
													chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
													Bitmap^ img = s->GetImage();
													chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
													chrono::duration<double> duration = t2 - t1;
													FormsImage^ fi = gcnew FormsImage(img, duration.count());
													fi->ShowDialog();

												}
												else
												{
													TaskDialog::Show("PixeR", "Selecione a Longitude");
												}
											}
											else
											{
												TaskDialog::Show("PixeR", "Selecione a Latitude");
											}
										}
										else
										{
											TaskDialog::Show("P", "Selecione o dia e hora");
										}
									}
									else
									{
										TaskDialog::Show("PixeR", "Selecione o tipo de céu");
									}
								}
								else
								{
									TaskDialog::Show("PixeR", "Selecione o campo distância focal");
								}
							}
							else
							{
								TaskDialog::Show("PixeR", "Selecione o campo abertura da câmera");
							}
						}
						else
						{
							TaskDialog::Show("Pixer", "Selecione o campo de visão da câmera!");
						}
					}
					else
					{
						TaskDialog::Show("PixeR", "Selecione a qualidade");
					}
				}
				else
				{
					TaskDialog::Show("PixeR", "Preencha o campo largura");
				}
			}
			else
			{
				TaskDialog::Show("PixeR", "Preencha o campo altura");
			}

		}

		List<ElementId^>^ GetElementLight(Document^ doc)
		{
			List<ElementId^>^ elem_light = gcnew List<ElementId^>();

			FilteredElementCollector^ collector = gcnew FilteredElementCollector(doc);
			collector = collector->WhereElementIsNotElementType()
				->OfClass(FamilyInstance::typeid)
				->OfCategory(BuiltInCategory::OST_LightingFixtures);
			for each(Element^ e in collector)
			{
				ElementId^ eid = e->Id;
				elem_light->Add(eid);
			}

			return elem_light;
		}

		XYZ^ GetPositionSun()
		{
			PSA^ positionSun = gcnew PSA(GetLatitude(), GetLongitude(), day, month, year, hour, min);
			XYZ^ sun = positionSun->GetPosition();
			return sun;
		}

		double GetLatitude()
		{
			return Convert::ToDouble(textBoxLatitude->Text);
		}

		double GetLongitude()
		{
			return Convert::ToDouble(textBoxLongitude->Text);
		}

		int GetSample()
		{
			if (comboBoxQuality->Text == "Baixa")
			{
				return 10;
			}
			else if (comboBoxQuality->Text == "Média")
			{
				return 25;

			}
			else
			{
				return 50;
			}
		}

		int GetRayDepth()
		{
			if (comboBoxQuality->Text == "Baixa")
			{
				return  10;
			}
			else if (comboBoxQuality->Text == "Média")
			{
				return 50;
			}
			else
			{
				return 100;
			}
		}

		float GetFov()
		{
			double d = Convert::ToDouble(textBoxFov->Text);
			return (float)d;
		}

		float GetAperture()
		{
			double d = Convert::ToDouble(textBoxAperture->Text);
			return (float)d;
		}

		float GetFocusDist()
		{
			double d = Convert::ToDouble(textBoxFocalDist->Text);
			return (float)d;
		}

		int GetHeight()
		{
			double d = Convert::ToDouble(textBoxHeight->Text);
			return (int)d;
		}

		int GetWidth()
		{
			double d = Convert::ToDouble(textBoxWidth->Text);
			return (int)d;
		 }

		bool DateHourIsValid()
		{
			std::string s = msclr::interop::marshal_as<std::string>( maskedTextBoxDateHour->Text);
			std::string delimiter = "/";
			std::string dayS = s.substr(0, s.find(delimiter));
			std::string monthS = s.substr(3, s.find(delimiter));
			std::string yearS = s.substr(6,4);
			std::string hourS = s.substr(11, 2);
			std::string minS = s.substr(s.find(":") + 1);

			if (dayS.length() == 2 && monthS.length() == 2 && yearS.length() == 4 && hourS.length() == 2 && minS.length() == 2)
			{
				day = std::stoi(dayS);
				month = std::stoi(monthS);
				year = std::stoi(yearS);
				hour = std::stoi(hourS);
				min = std::stoi(minS);
				if (year % 100 != 0 && year % 4 == 0 && year % 400 == 0)//year leap
				{
					if (month == 2 &&
						day > 0 && day <= 29 &&
						hour >= 0 && hour <= 23 &&
						min >= 0 && min < 60)
						return true;
				}
				if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				{
					if (day > 0 && day <= 31 &&
						hour >= 0 && hour <= 23 &&
						min >= 0 && min < 60)
						return true;
				}
				else
				{
					if (month > 1 && month < 12 &&
						day > 0 && day <= 30 &&
						hour >= 0 && hour <= 23 &&
						min >= 0 && min < 60)
						return true;
				}
				return false;
			}
			return false;

		}

		void TextBoxLongitude_KeyPress(Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
		{
			// Verify that the pressed key isn't CTRL or any non-numeric digit
			if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && (e->KeyChar != ',') && (e->KeyChar != '-'))
			{
				e->Handled = true;
			}

			// If you want, you can allow decimal (float) numbers
			System::Windows::Forms::TextBox^ a;
			a = dynamic_cast<System::Windows::Forms::TextBox^>(sender);
			if ((e->KeyChar == '-') && (a->Text != "")) {
				e->Handled = true;
			}
			if ((e->KeyChar == ',') && (a->Text->IndexOf(',') > -1))
			{
				e->Handled = true;
			}
		}
		void TextBox1_KeyPress_double(Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
		{
			// Verify that the pressed key isn't CTRL or any non-numeric digit
			if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && (e->KeyChar != ','))
			{
				e->Handled = true;
			}
			System::Windows::Forms::TextBox^ a;
			a = dynamic_cast<System::Windows::Forms::TextBox^>(sender);
			if ((e->KeyChar == ',') && (a->Text->IndexOf(',') > -1))
			{
				e->Handled = true;
			}
		}
		void TextBox1_KeyPress(Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
		{
			// Verify that the pressed key isn't CTRL or any non-numeric digit
			if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar))
			{
				e->Handled = true;
			}
		}
#pragma endregion
	};
}
