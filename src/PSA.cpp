#include "pch.h"
#include "PSA.h"


PSA::PSA(double latitude_, double longitude_, int dia_, int mes_, int ano_, int hora_, int minuto_)
{
	latitude = latitude_  * (M_PI / 180.0);
	longitude = longitude_ * (M_PI / 180);
	day = dia_;
	month = mes_;
	year = ano_;
	hour = hora_;
	minute = minuto_;
	julianDate = day + JulianDate();
	if (year % 100 != 0 && year % 4 == 0 && year % 400 == 0)//year leap
	{
		n_days += 1;
	}
	timeZone = -3 * 15 * (M_PI / 180.0);
}

int PSA::JulianDate() 
{
	int dayPlus = 0;
	if (year % 100 != 0 && year % 4 == 0 && year % 400 == 0)//year leap
	{
		dayPlus = 1;
	}
	switch ( month )
	  {
		 case 1:
			 return 0;
			break;
		 case 2:
			 return 31;
			 break;
		 case 3:
			 return 59 + dayPlus;
			 break;
		 case 4:
			 return 90 + dayPlus;
			 break;
		 case 5:
			 return 120 + dayPlus;
			 break;
		 case 6:
			 return 151 + dayPlus;
			 break;
		 case 7:
			 return 181 + dayPlus;
			 break;
		 case 8:
			 return 212 + dayPlus;
			 break;
		 case 9:
			 return 243 + dayPlus;
			 break;
		 case 10:
			 return 273 + dayPlus;
			 break;
		 case 11:
			 return 304 + dayPlus;
			 break;
		 default:
			return 334 + dayPlus;
	  }
}

XYZ^ PSA::GetPosition()
{

	int r = 40; //distancia da terra com o sol
	
	GetAAzimuteAltude();

	System::String^ men = azimuth +"; altitude : "+ altitude + "\n";
	//men += "altitude seno: " + sin(altitude) + " cos: " + cos(altitude) + "\n";
	//men += "azimuth seno: " + sin(azimuth) + " cos: " + cos(azimuth) + "\n\n\n";
	azimuth *= (M_PI / 180.0);
	altitude *= (M_PI / 180.0);

	double x = r * sin(altitude) * cos(azimuth);
	double y = r * sin(altitude) * sin(azimuth);
	double z = r * cos(altitude);
	//men += "altitude seno: "+ sin(altitude) +" cos: "+cos(altitude) + "\n";
	//men += "azimuth seno: " + sin(azimuth) + " cos: " + cos(azimuth) + "\n";

	XYZ ^ position = gcnew XYZ(x, y, z);
	men += position->ToString();
	TaskDialog::Show("sol", men);
	return position;
}

void PSA::GetAAzimuteAltude()
{
	double difference;
	double declination;
	double equation;
	double localTime;
	double solarTime;
	double sunrise;
	double sunset;
	// Temp data.
	double t, m, test;

	t = 2 * M_PI * ((julianDate - 1) / 365.0);
	declination = (0.322003
		- 22.984 *  cos(t)
		- 0.357898 *  cos(2 * t)
		- 0.14398 *  cos(3 * t)
		+ 3.94638 *  sin(t)
		+ 0.019334 *  sin(2 * t)
		+ 0.05928 *  sin(3 * t)
		);
	if (declination > 89.9) declination = 89.9;
	if (declination < -89.9) declination = -89.9;

	declination = declination * (M_PI / 180.0);
	// Calculate the equation of time as per Carruthers et al.
	t = (279.134 + 0.985647 * julianDate) * (M_PI / 180.0);
	equation = (5.0323
		- 100.976 * sin(t)
		+ 595.275 * sin(2 * t)
		+ 3.6858 * sin(3 * t)
		- 12.47 * sin(4 * t)
		- 430.847 * cos(t)
		+ 12.5024 * cos(2 * t)
		+ 18.25 * cos(3 * t)
		);
	// Convert seconds to hours.
	equation = equation / 3600.00;
	System::String^ mens = "";
	// Calculate difference (in minutes) from reference longitude.
	difference = (((longitude - timeZone) * 180 / M_PI) * 4) / 60.0;
	// Convert solar noon to local noon.
	double local_noon = 12.0 - equation - difference;
	// Calculate angle normal to meridian plane.
	if (latitude > (0.99 * (M_PI / 2.0))) latitude = (0.99 * (M_PI / 2.0));
	if (latitude < -(0.99 * (M_PI / 2.0))) latitude = -(0.99 * (M_PI / 2.0));
	test = -tan(latitude) * tan(declination);
	if (test < -1) t = acos(-1.0) / (15 * (M_PI / 180.0));
	else if (test > 1) t = acos(1.0) / (15 * (M_PI / 180.0));
	else t = acos(-tan(latitude) * tan(declination)) / (15 * (M_PI / 180.0));
	// Sunrise and sunset.
	sunrise = local_noon - t;
	sunset = local_noon + t;


	// Caculate solar time.
	solarTime = equation + difference;
	// Calculate hour angle.
	double hourAngle = (15 * (solarTime - 12)) * (M_PI / 180.0);
	// Calculate current altitude.
	t = (sin(declination) * sin(latitude)) + (cos(declination) * cos(latitude) * cos(hourAngle));
	altitude = asin(t);
	// Calculate current azimuth.
	t = (sin(declination) * cos(latitude))
		- (cos(declination) * sin(latitude)
			* cos(hourAngle));
	// Avoid division by zero error.
	double sin1, cos2;
	if (altitude < (M_PI / 2.0)) {
		sin1 = (-cos(declination) * sin(hourAngle)) / cos(altitude);
		cos2 = t / cos(altitude);
	}
	else {
		sin1 = 0.0;
		cos2 = 0.0;
	}
	// Some range checking.
	if (sin1 > 1.0) sin1 = 1.0;
	if (sin1 < -1.0) sin1 = -1.0;
	if (cos2 < -1.0) cos2 = -1.0;
	if (cos2 > 1.0) cos2 = 1.0;
	// Calculate azimuth subject to quadrant.
	if (sin1 < -0.99999) azimuth = asin(sin1);
	else if ((sin1 > 0.0) && (cos2 < 0.0)) {
		if (sin1 >= 1.0) azimuth = -(M_PI / 2.0);
		else azimuth = (M_PI / 2.0) + ((M_PI / 2.0) - asin(sin1));
	}
	else if ((sin1 < 0.0) && (cos2 < 0.0)) {
		if (sin1 <= -1.0) azimuth = (M_PI / 2.0);
		else azimuth = -(M_PI / 2.0) - ((M_PI / 2.0) + asin(sin1));
	}
	else azimuth = asin(sin1);
	// A little last-ditch range check.
	if ((azimuth < 0.0) && (localTime < 10.0)) {
		azimuth = -azimuth;
	}
	
	localTime = hour + (minute/60.0);

	// Caculate solar time.
	solarTime = localTime + equation + difference;
	// Calculate hour angle.
	hourAngle = (15 * (solarTime - 12)) * (M_PI / 180.0);
	// Calculate current altitude.
	t = (sin(declination) * sin(latitude)) + (cos(declination) * cos(latitude) * cos(hourAngle));
	altitude = asin(t);
	// Calculate current azimuth.
	t = (cos(latitude) * sin(declination)) - (cos(declination) * sin(latitude) * cos(hourAngle));
	azimuth = acos(t / cos(altitude));
		// Output aziumth value.
	t = round(azimuth * (180.0 / M_PI) * 100) / 100.0;
	azimuth = t;
		// Output altitude value.
	t = round(altitude * (180.0 / M_PI) * 100) / 100.0;
	altitude = t;

}