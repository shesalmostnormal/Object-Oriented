/*
Cristina S. Alonso
COP3330-0002
Assignment 3

Specification (header) file for the Time class.
*/

//-------------- time.cpp --------------

#include <iostream>       // for cout, cin
#include "time.h"        // for Display and Timer declarations

using namespace std;

//-------------- Definition of member functions for class Display


Display::Display(int lim) : LIMIT(lim)
// Initialize a new Display object.
{
	value = 0;
}

void Display::Increment()
// Add 1 to value.  If incrementing makes value
// equal to limit, reset value to zero.
{
   value++;
   if (value == LIMIT)
      value = 0;
}

void Display::Decrement()
// Add 1 to value.  If incrementing makes value
// equal to limit, reset value to zero.
{
   value--;
   if (value < 0)
      value = 0;
}

bool Display::SetValue(int val)
// Set the value on the timer to "val", as long as it's valid
// returns true for success, and false for failure.
//  On failure, current display value is unchanged
{
   if (val < 0 || val >= LIMIT)
      return false;

   value = val;
   return true;			// success
}

int Display::GetValue() const
// Return the current value.
{
   return value;
}

int Display::GetLimit() const
// Return the limit for this display
{
   return LIMIT;
}

void Display::Show() const
// Show the value of a Display.
{
   if (value < 10)          // Pad with a leading zero, if needed,
      cout << '0';

   cout << value;           // and in any case, display the value.
}

//-------------- Definition of member functions for class Time


std::ostream& operator <<(std::ostream& output, const Time& t)
{

	t.days.Show();
	output << '~';
	t.hours.Show();
	output << ':';
	t.minutes.Show();
	output << ':';
	t.seconds.Show();

	return output;
}

std::istream& operator >>(std::istream& input, Time& t)
{
	int d, h, m, s;

	input >> d >> h >> m >> s;

	if (d < 0 || h < 0 || m < 0 || s < 0)	
	{
		t.days.SetValue(0);
		t.hours.SetValue(0);
		t.minutes.SetValue(0);
		t.seconds.SetValue(0);
	}

	else 
		t.InitialSet(d,h,m,s);
	
	return input;
}

Time::Time() : days(2147483647), hours(24), minutes(60), seconds(60)
// Initialize a new Timer object,
{
	// empty
}

Time::Time(int s) : days(2147483647), hours(24), minutes(60), seconds(60)
//conversion constructor
{
	int d = days.GetValue();  // Multiply days
	int h = hours.GetValue();  // Multiply hours
	int m = minutes.GetValue(); // Multiply minutes

	days.SetValue(d);
	hours.SetValue(h);
	minutes.SetValue(m);
	seconds.SetValue(s);

}

Time::Time(int d, int h, int m, int s) : days(2147483647), hours(24), minutes(60), seconds(60)
// initializes Timer value to days, hours, minutes, seconds, if valid.
// if invalid data, defaults to 00:00
{
	if (InitialSet(d,h,m,s) == false)	

	{
		days.SetValue(0);
		hours.SetValue(0);
		minutes.SetValue(0);
		seconds.SetValue(0);
	}
}

bool Time::InitialSet(int d, int h, int m, int s)
// Set days to d, hours to h, minutes to m, seconds to s, if they are valid.
// If d, h, m, or s represent an invalid timer setting, no change
// returns true for success, false for failure
{
	if (d < 0 || d >= days.GetLimit())
		return false;
	if (h < 0 || h >= hours.GetLimit())
		return false;
	if (m < 0 || m >= minutes.GetLimit())
		return false;
	if (s < 0 || s >= seconds.GetLimit())
		return false;

	days.SetValue(d);
	hours.SetValue(h);
	minutes.SetValue(m);
	seconds.SetValue(s);
	return true;
}

const Time Time::operator +(const Time& t) const
{

   int d = days.GetValue() + t.days.GetValue();  // add days
   int h = hours.GetValue() + t.hours.GetValue();  // add hours
   int m = minutes.GetValue() + t.minutes.GetValue(); // add minutes
   int s = seconds.GetValue() + t.seconds.GetValue(); // add seconds

   
   if (s >= seconds.GetLimit())     // Check seconds limit.
   {
      s = s - seconds.GetLimit();
      m = m + 1;
   }

   if (m >= minutes.GetLimit())     // Check minutes limit.
   {             
      m = m - minutes.GetLimit();
      h = h + 1;
   }

   if (h >= hours.GetLimit())     // Check hours limit.
   {             
      h = h - hours.GetLimit();
      d = d + 1;
   }

   return Time(d,h,m,s);      // build and return result object

}

const Time Time::operator -(const Time& t) const
{

   int d = days.GetValue() - t.days.GetValue();  // Subtract days
   int h = hours.GetValue() - t.hours.GetValue();  // Subtract hours
   int m = minutes.GetValue() - t.minutes.GetValue(); // Subtract minutes
   int s = seconds.GetValue() - t.seconds.GetValue(); // Subtract seconds


   if (seconds.GetValue() < t.seconds.GetValue())
   {
      s = s + seconds.GetLimit();
      m = m - 1;
   }

   if (minutes.GetValue() < t.minutes.GetValue())
   {
      m = m + minutes.GetLimit();
      h = h - 1;
   }

   if (hours.GetValue() < t.hours.GetValue())
   {
      h = h + hours.GetLimit();
      d = d - 1;
   }

   return Time(d,h,m,s);      // build and return result object

}

const Time Time::operator *(int i) const
{
   Time r;
   bool success;

   int d = days.GetValue() * i;  // Multiply days
   int h = hours.GetValue() * i;  // Multiply hours
   int m = minutes.GetValue() * i; // Multiply minutes
   int s = seconds.GetValue() * i; // Multiply seconds

   do
   {
      if (s >= seconds.GetLimit())     // Check seconds limit.
      {
         s = s - seconds.GetLimit();
         m = m + 1;
      }

      if (m >= minutes.GetLimit())     // Check minutes limit.
      {             
         m = m - minutes.GetLimit();
         h = h + 1;
      }

      if (h >= hours.GetLimit())     // Check hours limit.
      {             
         h = h - hours.GetLimit();
         d = d + 1;
      }

      success = r.InitialSet(d,h,m,s);

   } while (!success);

   return r;      // build and return result object

}


bool Time::operator <(const Time& t) const
{

   if (days.GetValue() < t.days.GetValue())
      return true;
   if (days.GetValue() == t.days.GetValue() && hours.GetValue() < t.hours.GetValue())
      return true;
   if (days.GetValue() == t.days.GetValue() && hours.GetValue() == t.hours.GetValue() && minutes.GetValue() < t.minutes.GetValue())
      return true;
   if (days.GetValue() == t.days.GetValue() && hours.GetValue() == t.hours.GetValue() && minutes.GetValue() == t.minutes.GetValue() && seconds.GetValue() < t.seconds.GetValue())
      return true;


   return false;

}

bool Time::operator >(const Time& t) const
{
   if (days.GetValue() > t.days.GetValue())
      return true;
   if (days.GetValue() == t.days.GetValue() && hours.GetValue() > t.hours.GetValue())
      return true;
   if (days.GetValue() == t.days.GetValue() && hours.GetValue() == t.hours.GetValue() && minutes.GetValue() > t.minutes.GetValue())
      return true;
   if (days.GetValue() == t.days.GetValue() && hours.GetValue() == t.hours.GetValue() && minutes.GetValue() == t.minutes.GetValue() && seconds.GetValue() > t.seconds.GetValue())
      return true;


   return false;

}

bool Time::operator ==(const Time& t) const
{
   if (days.GetValue() == t.days.GetValue() && hours.GetValue() == t.hours.GetValue() && minutes.GetValue() == t.minutes.GetValue() && seconds.GetValue() == t.seconds.GetValue())
      return true;
   return false;

}


bool Time::operator <=(const Time& t) const
{
   return (!operator>(t));
}

bool Time::operator >=(const Time& t) const
{
   return (!operator<(t));
}

bool Time::operator !=(const Time& t) const
{
   return (!operator==(t));
}

// overloaded prefix ++ operator
Time& Time::operator ++()
{
	seconds.Increment();

	return *this;
}

// overloaded postfix ++ operator
Time Time::operator ++(int ignoreMe)
{	
	Time temp;

	int d = days.GetValue();
	int h = hours.GetValue();
	int m = minutes.GetValue();
	int s = seconds.GetValue();

	s++;

	temp.InitialSet(d,h,m,s);

	return temp;
}

// overloaded prefix -- operator
Time& Time::operator --()
{
	seconds.Decrement();

	return *this;
}

// overloaded postfix ++ operator
Time Time::operator --(int ignoreMe)
{	
	Time temp;

	int d = days.GetValue();
	int h = hours.GetValue();
	int m = minutes.GetValue();
	int s = seconds.GetValue();

	s--;

	temp.InitialSet(d,h,m,s);

	return temp;
}