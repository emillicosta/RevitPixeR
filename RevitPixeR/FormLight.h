#pragma once

namespace RevitPixeR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace Autodesk::Revit::DB;
	using namespace Autodesk::Revit::UI;
	using namespace std;

	/// <summary>
	/// Sumário para FormLight
	/// </summary>
	public ref class FormLight : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::CheckedListBox^ checkedListBox1;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::Button^ button1;
	public:
		List<ElementId^>^ lights_on = gcnew List<ElementId^>();
		ExternalCommandData^ commandData;
		Document^ doc;
		FormLight(ExternalCommandData^ commandData_, List<ElementId^>^ lights_on_)
		{
			commandData = commandData_;
			doc = commandData->Application->ActiveUIDocument->Document;
			lights_on = lights_on_;

			InitializeComponent();
		}
		List<ElementId^>^ GetLights()
		{
			List<ElementId^>^ light_on = gcnew List<ElementId^>();
			for each(Object^ item in checkedListBox1->CheckedItems)
			{
				light_on->Add(dynamic_cast<ElementId^>(item));
			}
			return light_on;
		}
	protected:
		/// <summary>
		/// Limpar os recursos que estão sendo usados.
		/// </summary>
		~FormLight()
		{
			if (components)
			{
				delete components;
			}
		}

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FormLight::typeid));
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->checkedListBox1);
			this->groupBox1->Controls->Add(this->radioButton2);
			this->groupBox1->Controls->Add(this->radioButton1);
			this->groupBox1->Location = System::Drawing::Point(11, 17);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(261, 189);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Luzes Acessas";
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(6, 19);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(55, 17);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Todas";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &FormLight::RadioButton1_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(130, 19);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(76, 17);
			this->radioButton2->TabIndex = 1;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Nenhumas";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &FormLight::RadioButton2_CheckedChanged);
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Location = System::Drawing::Point(8, 54);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(230, 109);
			this->checkedListBox1->TabIndex = 2;
			for each (ElementId ^ id in lights_on) {
				Element^ e = doc->GetElement(id);
				this->checkedListBox1->Items->Add(e, true);
			}
			this->checkedListBox1->DisplayMember = "Name";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(197, 226);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Ok";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &FormLight::Button1_Click);

			// 
			// FormLight
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->groupBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormLight";
			this->Text = L"PixeR";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
		void RadioButton1_CheckedChanged(Object^ sender, EventArgs^ e)
		{
			for (int i = 0; i < checkedListBox1->Items->Count; i++)
			{
				checkedListBox1->SetItemChecked(i, true);
			}
		}

		void RadioButton2_CheckedChanged(Object^ sender, EventArgs^ e)
		{
			for (int i = 0; i < checkedListBox1->Items->Count; i++)
			{
				checkedListBox1->SetItemChecked(i, false);
			}
		}
		void Button1_Click(Object^ sender, EventArgs^ e)
		{
			Close();
		}
#pragma endregion
	};
}
