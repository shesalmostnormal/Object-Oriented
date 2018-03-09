/*
Cristina S. Alonso
COP3330-0002
Assignment 2

Implementation file for the Temperature class.

*/

#include "temperature.h"
#include <iostream>
#include <cctype>
#include <cmath>
#include <iomanip>
using namespace std;

//**************************************************************
// Friend functions for converting between temperature scales. *
//**************************************************************

double FtoC (double temp)
	{ return (temp-32)*(5./9.); }

double FtoK (double temp)
	{ return ((temp-32)*(5./9.))+273.15; }

double CtoF (double temp)
	{ return (temp*(9./5.))+32.; }

double CtoK (double temp)
	{ return temp+273.15; }

double KtoF (double temp)
	{ return (temp*(9./5.))-459.67; }

double KtoC (double temp)
	{ return temp-273.15; }

//****************************************************************
// Friend function for translating scale character to full name. *
//****************************************************************

void LongFormat (char s)
{
	string strscale;

	switch(toupper(s))
	{
		case 'C': 
		{
			strscale = "Celsuis";
			break;
		}
		case 'F':
		{
			strscale = "Fahrenheit";
			break;
		}
		case 'K':
		{
			strscale = "Kelvin";
			break;
		}
	}

	cout << strscale << "\n\n";
}

//******************************************
// Default constructor with no parameters. *
//******************************************

Temperature::Temperature()
{
	degrees = 0;
	scale = 'C';
	format = 'D';
}

//***********************************************************
// The constructor accepts arguments for degrees and scale. *
//***********************************************************

Temperature::Temperature(double deg, char s)
{
	if (Set(deg, s) != true)
	{
		degrees = 0;
		scale = 'C';
		format = 'D';
	}
	else
	{
		degrees = deg;
		scale = s;
		format = 'D';
	}
}

//*********************************************************************
// Prompts user to enter a temperature, and allows user input in form *
// of numeric value and character.									  *
//*********************************************************************

void Temperature::Input()
{
	// User entry.
	cout << "Enter temperature:\n";
	cin >> degrees >> scale;

	while(Set(degrees, scale) == false)
	// Loop until valid temperature entered.
	{	
		cout << "Invalid temperature. Try again: ";
		cin >> degrees >> scale;
	}
	
}

//***************************************************************************
// Output temperature to the screen and returns to initial format settings. *
//***************************************************************************

void Temperature::Show()
{
	int oldprecision = cout.precision();
	char oldfill = cout.fill();
	ios_base::fmtflags oldflags = cout.flags();

	if (SetFormat(format) == true)
	{
		switch(format)
		{
			case 'D':	// Default format settings.
			{
				cout << GetDegrees() << " ";	
				cout << GetScale() << "\n\n";
				break;
			}

			case 'P': 	// Precision-1: 1 decimal place, and scale letter.
			{
				scale = toupper(scale);
				cout << setprecision(1) << fixed << GetDegrees();
				cout << " " << GetScale() << "\n\n";
				break;
			}

			case 'L': 	// Long: Default precision, and full word of scale.
			{
				cout << GetDegrees() << " ";
				LongFormat(scale);
				break;
			}
		}
	}

	cout.precision(oldprecision); 	// Restores old prior precision setting.
	cout.fill(oldfill);				// Restores old fill char setting.
	cout.flags(oldflags);			// Restores all prior format flags.

}

//**************************************************************
// Set the temperature to the specified values unless invalid. *
//**************************************************************

bool Temperature::Set(double deg, char s) const
{

	if (toupper(s) == 'C')	
	// Minimum value of Celsuis.
	{
		if (deg < -273.15)
			return false;
		return true;
	}

	else if (toupper(s) == 'F') 
	// Minimum value of Fahrenheit.
	{
		if (deg < -459.67)
			return false;
		return true;
	}

	else if (toupper(s) == 'K')
	// Minimum value of Kelvin.
	{
		if (deg < 0)
			return false;
		return true;
	}
	else return false;

}

//***************************************************
// Accessor function returns degrees to the caller. *
//***************************************************

double Temperature::GetDegrees() const
{
	return degrees;
}

//*************************************************
// Accessor function returns scale to the caller. *
//*************************************************

char Temperature::GetScale() const
{
	return scale;
}

//**********************************************
// Allows caller to change the format setting. *
//**********************************************

bool Temperature::SetFormat(char f)
{	

	if (f == 'D' || f == 'P' || f == 'L')
	{	
		format = f;
		return true;
	}	
	return false;
	// Failure if invalid setting.

}

//**********************************************************************
// Converts temperature to be represented in scale given in parameter. *
//**********************************************************************

bool Temperature::Convert(char sc)
{
	bool status;
	double newdeg;

	if (toupper(scale) == toupper(sc))	
	// No change if temperature scales are the same.
	{
		status = true;
	}
	else if (toupper(sc) == 'F' || toupper(sc) == 'C' || toupper(sc) == 'K')
	// Change if temperature scale to change to is among Fahrenheit, Celsuis, and Kelvin.
	{	
		if (toupper(scale) == 'F')
		{		
			if (toupper(sc) == 'C')
				newdeg = FtoC(degrees);
			else if (toupper(sc) == 'K')
				newdeg = FtoK(degrees);
		}

		else if (toupper(scale) == 'C')
		{		
			if (toupper(sc) == 'F')
				newdeg = CtoF(degrees);
			else if (toupper(sc) == 'K')
				newdeg = CtoK(degrees);
		}

		else if (toupper(scale) == 'K')
		{		
			if (toupper(sc) == 'F')
				newdeg = KtoF(degrees);
			else if (toupper(sc) == 'C')
				newdeg = KtoC(degrees);
		}

		degrees = newdeg;
		scale = sc;
		status = true;
	}

	else status = false;
	// No change. Entry is invalid.

	return status;

}

//********************************************************************************
// Comparison of two Temperature objects withut changing either original object. *
//********************************************************************************

int Temperature::Compare(const Temperature& d)
{
	if (Set(d.degrees, d.scale) == true)
	{
		if (scale == d.scale)
		{
			if (degrees < d.degrees)
				return -1;
			else if (degrees > d.degrees)
				return 1;
			return 0;
		}
		else if (scale != d.scale)
		{
			Convert(d.scale);
			// Allows conversion of parameter object to calling object scale.
			
			if (degrees < d.degrees)
				return -1;
			else if (degrees > d.degrees)
				return 1;
			return 0;
		}
	}
}

//**************************************************************************
// Move the temperature forward by number of degrees given in scale given. *
//**************************************************************************

void Temperature::Increment(int deg, char sc)
{
	double newdeg;

	if (Set(deg,sc) == true)
	// Confirms increment is allowed value.
	{
		if (toupper(sc) == toupper(scale))
		// No change if parameter object scale is the same as calling object scale. 
		{
			degrees += deg;
		}
		else if (toupper(sc) == 'F' || toupper(sc) == 'C' || toupper(sc) == 'K')
		// Change degrees to calling object scale before incrementing. 
		{
			if (toupper(scale) == 'F')
			{		
				if (toupper(sc) == 'C')
					newdeg = CtoF(deg);
				else if (toupper(sc) == 'K')
					newdeg = KtoF(deg);
			}

			else if (toupper(scale) == 'C')
			{		
				if (toupper(sc) == 'F')
					newdeg = FtoC(deg);
				else if (toupper(sc) == 'K')
					newdeg = KtoC(deg);
			}

			else if (toupper(scale) == 'K')
			{		
				if (toupper(sc) == 'F')
					newdeg = FtoK(deg);
				else if (toupper(sc) == 'C')
					newdeg = CtoK(deg);
			}
		
			degrees += newdeg;
		}
	}
}


