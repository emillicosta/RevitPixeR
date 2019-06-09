#pragma once
#include <chrono>
namespace RevitPixeR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;

	/// <summary>
	/// Sumário para FormsImage
	/// </summary>
	public ref class FormsImage : public System::Windows::Forms::Form
	{

	private: Bitmap^ bitmap;
			 double duration;

	public:
		FormsImage(Bitmap^ img, double duration_)
		{
			duration = duration_;
			bitmap = img;
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Limpar os recursos que estão sendo usados.
		/// </summary>
		~FormsImage()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	protected:

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FormsImage::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// labelpx1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(5, 5);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(18, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Duração em seg: " + duration;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(bitmap->Width - 80, bitmap->Height + 10);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 25);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Salvar";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &FormsImage::Button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = bitmap;
			this->pictureBox1->Location = System::Drawing::Point(5, 18);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(746, 347);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// FormsImage
			//
			if (bitmap->Width > 75)
			{
				this->ClientSize = System::Drawing::Size(bitmap->Width + 10, bitmap->Height + 50);
			}
			else
			{
				this->ClientSize = System::Drawing::Size(85, bitmap->Height + 50);
			}
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormsImage";
			this->Text = L"Revit";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		private: System::Void Button1_Click(System::Object^ sender, System::EventArgs^ e)
		{
			SaveFileDialog^ dialog = gcnew SaveFileDialog();
			dialog->DefaultExt = "png";
			dialog->Filter = "Png Image (.png)|*.png|Bitmap Image (.bmp)|*.bmp|Gif Image (.gif)|*.gif|JPEG Image (.jpeg)|*.jpeg|Tiff Image (.tiff)|*.tiff|Wmf Image (.wmf)|*.wmf";

			if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				bitmap->Save(dialog->FileName, ImageFormat::Png);
			}
		}
	};
}
