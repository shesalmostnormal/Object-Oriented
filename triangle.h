/*
Cristina S. Alonso
COP3330-0002
Assignment 1

Specification (header) file for the Triangle class.
*/

#ifndef TRIANGLE_H
#define TRIANGLE_H

// Triangle class declaration.

class Triangle
{
	private:
		int length;							// One side of equilateral triangle.
		char border;						// Border character of triangle.
		char fill;							// Fill character of triangle.

	public:

		Triangle(int,char='#',char='*'); 	// Constructor to set defaults.

		int GetSize();						// Returns length of a side.
		int Perimeter();
		double Area();

		void Grow();						// Adds 1 to length of side.
		void Shrink();						// Subtracts 1 to length of side.

		void SetBorder(char);				// Determines allowable border character.
		void SetFill(char);					// Determines allowable fill character.

		char Draw();

		void Summary();						// Prints size, perimeter, area, and picture.

};

#endif