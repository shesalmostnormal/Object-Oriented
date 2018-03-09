/*
Cristina S. Alonso
COP3330-0002
Assignment 1

Implementation file for the Triangle class.

*/

#include "triangle.h"
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//********************************************************************
// The constructor with 3 default parameters and accepts parameters. *
//********************************************************************

Triangle::Triangle(int len, char b, char f)
{ 	
	if (len < 1)
		length = 1;
	
	else if (len > 39)
		length = 39;

	else
		length = len;						// Length in range 1-39 units.
	
	border = b;								// Set border to default '#'
	fill = f;								// Set filler to default '*'
}

//***********************************************************
// GetSize returns the value of the member variable length. *
//***********************************************************

int Triangle::GetSize()
{
	return length;
}

//*****************************************************************
// Perimeter returns the sum of sides in an equilateral triangle. *
//*****************************************************************

int Triangle::Perimeter()
{
	return 3*length;
}

//****************************************************************
// Area returns the product of sqrt(3)/4 and the squared length. *
//****************************************************************

double Triangle::Area()
{
	return pow(3,0.5)/4.0*pow(length,2);
}

//******************************************************************
// Grow increases the sides of the triangle by 1, unless length is *
// out of bounds (> 39 units). 									   *
//******************************************************************

void Triangle::Grow()
{	

	if(length < 39){
		length++;							// Increases length by 1.
	}
}


//********************************************************************
// Shrink decreases the sides of the triangle by 1, unless length is *
// out of bounds (< 1 units). 										 *
//********************************************************************

void Triangle::Shrink()
{
	if(length > 1){
		length--;							// Decreases length by 1.
	}
}

//***************************************************
// SetBorder sets the value of the variable border. *
//***************************************************

void Triangle::SetBorder(char b_ascii)
{
	int b_num = (int) b_ascii;

	if(b_num >= 33 && b_num <= 126)
		border = (char) b_num;				// Allows a new border character.

	else 
		border = '#';						// Outside range is set to default.
}

//***********************************************
// SetFill sets the value of the variable fill. *
//***********************************************

void Triangle::SetFill(char f_ascii)
{
	int f_num = (int) f_ascii;

	if(f_num >= 33 && f_num <= 126)
		fill = (char) f_num;				// Allows a new fill character.
	
	else
		fill = '*';							// Outside range is set to default.
}

//*********************************************************************
// Draw displays a picture of the equilateral triangle on the screen. *
//*********************************************************************

char Triangle::Draw()
{
	int i = 1;

	for(i; i <= length; i++)
	{
		for(int j = 0; j <= length - i; j++)
			cout << " ";
		
		if (i > 1) cout << border;			// Prints border in each row on left side.

		for(int k = 4; k <= i*2; k++)		// Prints fill characters in each row.
			cout << fill;

		cout << border << "\n";				// Prints to complete border on right side.
	
	}

	for(int n = 1; n <= length + i; n++)
		cout << border;						// Prints bottom border.

	cout << endl;
}

//***************************************************************************
// Summary prints Triangle object details: size, perimeter, area, and draw. *
//***************************************************************************

void Triangle::Summary()
{

	cout << "Size of triangle's side = " << GetSize() << " units.\n";
	cout << "Perimeter of triangle = " << Perimeter() << " units.\n";
	cout << "Area of triangle = " << fixed << setprecision(2) << Area() << " units.\n";
	cout << "Triangle looks like: " << endl;
	cout << Draw() << endl;
}
