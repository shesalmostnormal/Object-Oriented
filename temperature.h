/*
Cristina S. Alonso
COP3330-0002
Assignment 2

Specification (header) file for the Temperature class.
*/

#ifndef TEMPERATURE_H
#define TEMPERATURE_H

class Temperature
{
	// Converting among Fahrenheit, Celsuis, and Kelvin.
	friend double FtoC (double);
	friend double FtoK (double);
	friend double CtoF (double);
	friend double CtoK (double);	
	friend double KtoF (double);
	friend double KtoC (double);
	
	// Translate scale character to full word representation.
	friend void LongFormat (char);

	private:

		double degrees;
		char scale;
		char format;

	public:
		
		// Constructor without parameters.
		Temperature();

		// Constructor with parameters.
		Temperature(double, char);

		// Allows user to change degrees and scale.
		void Input();

		// Displays numeric and character values in specified format.
		void Show();

		// Sets valid temperature.
		bool Set(double, char) const;
		
		// Accessor functions to retrieve degrees and scale.
		double GetDegrees() const;
		char GetScale() const;
		
		// Specified decimal places and scale description.
		bool SetFormat(char);

		// Converts temperature between scales.
		bool Convert(char);

		// Returns -1, 0, or 1 for comparison.
		int Compare(const Temperature& d);

		// Adds number of degrees in given scale.
		void Increment(int, char);

	
};

#endif
