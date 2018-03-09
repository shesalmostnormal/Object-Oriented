/*
Cristina S. Alonso
COP3330-0002
Assignment 3

Specification (header) file for the Time class.
*/

//-------------- time.h --------------

class Display
// A Display object stores and displays a single integer.
// That integer is always in the range 0 .. limit-1, where limit
// is also stored in the class.
{
	public:

		Display();
		Display(int lim);		// Initialize a new Display object.

		void Increment();		// Add 1 to value.
		void Decrement();		// Subtract 1 to value.
		bool SetValue(int val);	// Set the value.

		int GetValue() const;	// Return the current value.
		int GetLimit() const;	// Return the limit

		void Show() const;		// Show the current value.

	private:
		const int LIMIT;		// largest possible value
		int value;
};

class Time
// A Timer object consists of two Displays.
{

	public:
		Time();
		// Initialize a new Time object 00:00

		Time(int s);
		// Conversion constructor

		Time(int d, int h, int m, int s);
		// Initialize a new Time object

		bool InitialSet(int d, int h, int m, int s);
		// Set Time to d days, h hours, m minutes, s seconds
		
		// Addition, subtraction, multiplication
		const Time operator+(const Time& t) const;
		const Time operator-(const Time& t) const; 
		const Time operator*(int i) const;

		// Comparison operators
		bool operator <(const Time& t) const;
		bool operator >(const Time& t) const;
		bool operator ==(const Time& t) const;

		bool operator <=(const Time& t) const;
		bool operator >=(const Time& t) const;
		bool operator !=(const Time& t) const;

		// Increment and decrement operators
		Time& operator++();
		Time operator++(int);
		Time& operator--();
		Time operator--(int);
	
		// Insertion and extraction operators
		friend std::ostream& operator<<(std::ostream& output, const Time& t);
		friend std::istream& operator>>(std::istream& input, Time& t);


	private:
		Display days, hours, minutes, seconds; 

};

