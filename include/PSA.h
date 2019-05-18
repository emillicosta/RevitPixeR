#pragma once
#include <cmath> 
#include <iostream>
#include <cstdlib>
# define M_PI           3.14159265359
using namespace std;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::UI;

ref class PSA
{
public:
	double latitude, longitude;
	int day, month, year, hour, minute, julianDate;
	int n_days = 365;
	double timeZone;

	double azimuth;
	double altitude;
	
	PSA(double latitude, double longitude, int dia, int mes, int ano, int hora, int minuto);
	
	void GetAAzimuteAltude();
	XYZ^ GetPosition();
	int JulianDate();
};

