/*
Cristina S. Alonso
COP3330-0002
Assignment 4

Main program file for the Grid class.
*/

#include <iostream>
using namespace std;

#include "grid.h"


int main()
{
  // Set up the initial grid with user input.
  int x, y;

  cout << "Number of rows: ";
  cin >> x;
  cout << "Number of columns: ";
  cin >> y;

  Grid g(x,y);
  g.Display();

  // Now the mole starts moving.

  bool status = true;

  // First loop guides mole to one corner of the grid.
  // Breaks if "accidentally" runs into the exit.

  while ((g.GetRow() != 1) || (g.GetCol() != 1))
  {
    g.Move(1);

    if (g.GetRow() == 0) 
      {
        status = false;
        break;
      }
    else if (g.GetCol() == 0)
      {
        status = false;
        break;
      }
    else if (g.GetRow() == g.GetNumRows()-1)
      {
        status = false;
        break;
      } 
    else if (g.GetCol() == g.GetNumCols()-1)
      {
        status = false;
        break;
      }

    if (g.FrontIsClear() == true) continue;    
    else
      {
        g.TurnLeft();
        continue;
      }
  }

  // If it hasn't "accidentally" run into the exit,
  // the mole must now feel along the edges for exit.
  while (status == true)
  {
    g.Move(1);

   if (g.GetRow() == 0) break;
   else if (g.GetCol() == 0) break;
   else if (g.GetRow() == g.GetNumRows()-1) break;
   else if (g.GetCol() == g.GetNumCols()-1) break;
   
    if (g.RightIsClear() == true) 
      {
        g.TurnLeft();
        g.TurnLeft();
        g.TurnLeft();
        g.Move(1);
        break;
      }

    if (g.FrontIsClear() == true) continue;    
    else
      {
        g.TurnLeft();
        continue;
      }
  }

  if (status == false)
  {
    g.TurnLeft();
    g.Move(1);
  }

  g.Display();

  cout << "We escaped!\n\n";

  return 0;
}
