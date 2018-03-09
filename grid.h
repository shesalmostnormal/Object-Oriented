/*
Cristina S. Alonso
COP3330-0002
Assignment 4

Specification (header) file for the Grid class.
*/

// Grid class

const int MAX_R = 40;
const int MAX_C = 40;

class Grid
{
public:
   // public static class constants, for direction indicators
   static const int NORTH = 0;
   static const int WEST = 1;
   static const int SOUTH = 2;
   static const int EAST = 3;

   // public member funcitons

   Grid();			// build 1 x 1 grid with mover in only
   //  square, facing east
   Grid(int r, int c);		// build grid with r rows, c cols,
   //  blocks around edge with random exit
   //  and random mover position and direction

   Grid(int r, int c, int mr, int mc, int d);
   // build empty grid with r rows, c cols, and mover
   //  at row mr, col mc, and facing direction d

   bool Move(int s);		// move forward s spaces, if possible
   void TogglePath();		// toggle whether or not moved path is shown
   void TurnLeft();		// turn the mover to the left
   void PutDown();		// put down an item at the mover's position
   bool PutDown(int r, int c);  // put down an item at (r,c), if possible
   bool PickUp();		// pick up item at current position
   bool PlaceBlock(int r, int c);	// put a block at (r,c), if possible
   void Grow(int gr, int gc);	// grow the grid by gr rows, gc columns


   void Display() const;	// display the grid on screen

   // Accessors
   bool FrontIsClear() const;	// check to see if space in front of 
   //  mover is clear
   bool RightIsClear() const;	// check to see if space to right of 
   //  mover is clear
   int GetRow() const;		// return row of the mover
   int GetCol() const;		// return column of the mover
   int GetNumRows() const;	// return number of rows in the grid
   int GetNumCols() const;	// return number of columns in the grid


private:

   char grid_arr[MAX_R][MAX_C]; // Number of stored items (max is 40)

   int rows; // Number of rows.
   int columns; // Number of columns.

   int r_position; // Row of mover.
   int c_position; // Column of mover.

   int direction; // Direction of mover.

   bool path; // Toggle boolean variable set to true = ON.
   char mover_arr[MAX_R][MAX_C]; // Recorded path of mover.

   int items; // Number of items.
   int ritemlist[MAX_R]; // Row values of items.
   int citemlist[MAX_C]; // Column values of mover.

   int blocks; // Number of blocks.

};