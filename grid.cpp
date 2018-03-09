/*
Cristina S. Alonso
COP3330-0002
Assignment 4

Implementation file for the Grid class.
*/

#include <iostream>
#include "grid.h"
#include <cstring>

#include <cstdlib> // for srand(), rand()
#include <ctime> // for time()

using namespace std;

// ****************************************************************
// Build 1x1 grid with mover in only square, facing East.		  *
// ****************************************************************

Grid::Grid() : path(true),items(0),blocks(0) // Default constructor.
{
	rows = 1;
	columns = 1;

	// Creates 1x1 grid.
	for (int i = 0; i < MAX_R; ++i)
		for (int j = 0; j < MAX_C; ++j)
			grid_arr[i][j] = '.';

	// Mover in the only position EAST.
	r_position = 0;
	c_position = 0;

	direction = EAST;

	// FOR TOGGLE

	for (int i = 0; i < MAX_R; ++i)
		for (int j = 0; j < MAX_C; ++j)
			mover_arr[i][j] = grid_arr[i][j];

}

// ****************************************************************
// Build grid with r rows, c cols, blocks around edge with random *
// exit and random mover position and direction.				  *
// ****************************************************************

Grid::Grid(int r, int c) : path(true),items(0),blocks(0) // Constructor accepts two integers, rows and columns.
{
	// SET NUMBER OF ROWS AND COLUMNS

	if (r < 3) 
	// If number of rows is less than 3, default to 3.
		rows = 3;
	else if (r > MAX_R) 
	// If number of rows is greater than max, default to max.
		rows = MAX_R;
	else rows = r;
	
	if (c < 3) 
	// If number of columns is less than 3, default to 3.
		columns = 3;
	else if (c > MAX_C) 
	// If number of columns is greater than max, default to max.
		columns = MAX_C;
	else columns = c;

	// BORDER: Blocks placed all around the edge where mover cannot move through.

	for (int i = 0; i < MAX_R; ++i)
		{
			for (int j = 0; j < MAX_C; ++j)
			{
				if (i == 0 || i == (MAX_R-1))
				{
					grid_arr[i][j] = '#';

				}
				else
				{
					if(j == 0 || j == (MAX_R-1))
						grid_arr[i][j] = '#';
					else
						grid_arr[i][j] = '.';
				}
			}
		}

	srand(time(0));

	// MOVER

	int rand_d, rand_r, rand_c;

	int compass[] = {NORTH,WEST,SOUTH,EAST};

	rand_d = compass[(int)(rand()%4)]; // Each direction has 25% possibility. 

	direction = rand_d;

	rand_r = rand() % (rows-2) + 1; // random number from 1 to row-2
	rand_c = rand() % (columns-2) + 1; // random number from 1 to column-2

	r_position = rand_r;
	c_position = rand_c;
		
	// RANDOM EXIT 

	int exitrow, exitcol;
	
	do
	{
		exitrow = rand() % rows; // random number from 0 to row-1

		if (exitrow == 0 || exitrow == (rows-1))
			{	
				exitcol = rand() % (columns-2) + 1; // random number between 1 and column-2
				grid_arr[exitrow][exitcol] = ' ';
				break;
			}

		else if (exitrow >= 1 && exitrow <= (rows-2))
			{	
				exitcol = rand() % 2; // random number between 0 and 1
				
				if (exitcol == 0)
					{	
						grid_arr[exitrow][0] = ' ';
						break;
					}

				else if (exitcol == 1)
					{	
						grid_arr[exitrow][columns-1] = ' ';
						break;
					}
			}

		else
			continue;
	
	} while ( (exitrow == 0 && exitcol == 0) 
		|| (exitrow == (rows-1) && exitcol == 0) 
		|| (exitrow == 0 && exitcol == (columns-1)) 
		|| (exitrow == (rows-1) && exitcol == (columns-1)) );

	// FOR TOGGLE

	for (int i = 0; i < MAX_R; ++i)
		for (int j = 0; j < MAX_C; ++j)
			mover_arr[i][j] = grid_arr[i][j];

}

// ****************************************************************
// Build empty grid with r rows, c cols, and mover at row mr, col *
// mc, and facing direction d.									  *
// ****************************************************************

Grid::Grid(int r, int c, int mr, int mc, int d) : path(true),items(0),blocks(0) // Constructor takes 5 parameters.
{
	// SET NUMBER OF ROWS AND COLUMNS

	if (r < 1)
	// If number of rows is less than 1, default to 3.
		rows = 3;
	else if (r > MAX_R)
	// If number of rows is greater than max, default to max.
		rows = MAX_R;
	else rows = r;
	
	if (c < 1)
	// If number of columns is less than 1, default to 3.
		columns = 3;
	else if (c > MAX_C)
	// If number of columns is greater than max, default to max.
		columns = MAX_C;
	else columns = c;

	// GRID: Empty

	for (int i = 0; i < MAX_R; ++i)
		for (int j = 0; j < MAX_C; ++j)
			grid_arr[i][j] = '.';

	// MOVER

	direction = d;
	
	
	// If mr out of range 0 to r-1, adjust to closest first or last row.
	if (mr < 0)
		r_position = 0;
	else if (mr > (rows-1))
		r_position = (rows-1);
	else if (mr >= 0 || mr <= (rows-1))
		r_position = mr;

	// If mc out of range 0 to c-1, adjust to closest first or last column.
	if (mc < 0)
		c_position = 0;
	else if (mc > (columns-1))
		c_position = (columns-1);
	else if (mc >= 0 || mc <= (columns-1))
		c_position = mc;
	
	/* 

	IMPORTANT NOTE: NO RANDOM EXIT SPECIFIED FOR THIS CONSTRUCTOR.
	If a random exit is needed, please uncomment below:
	
	srand(time(0));

	int exitrow, exitcol;
	
	do
	{
		exitrow = rand() % rows; // random number from 0 to row-1

		if (exitrow == 0 || exitrow == (rows-1))
			{	
				exitcol = rand() % (columns-2) + 1; // random number between 1 and column-2
				grid_arr[exitrow][exitcol] = 'x';
				break;
			}

		else if (exitrow >= 1 && exitrow <= (rows-2))
			{	
				exitcol = rand() % 2; // random number between 0 and 1
				
				if (exitcol == 0)
					{	
						grid_arr[exitrow][0] = 'x';
						break;
					}

				else if (exitcol == 1)
					{	
						grid_arr[exitrow][columns-1] = 'x';
						break;
					}
			}

		else
			continue;
	
	} while ( (exitrow == 0 && exitcol == 0) 
		|| (exitrow == (rows-1) && exitcol == 0) 
		|| (exitrow == 0 && exitcol == (columns-1)) 
		|| (exitrow == (rows-1) && exitcol == (columns-1))
		|| (exitrow == r_position && exitcol == c_position));

	*/

	// FOR TOGGLE

	for (int i = 0; i < MAX_R; ++i)
		for (int j = 0; j < MAX_C; ++j)
			mover_arr[i][j] = grid_arr[i][j];

}

// ****************************************************************
// Move forward s spaces, if possible.							  *
// ****************************************************************

bool Grid::Move(int s)
{
	int forwardrow = GetRow();
	int forwardcol = GetCol();

	// Must be positive amount of spaces.
	if (s < 0)
		return false;

	int count = 0;

	// Must not attempt to move through a "block".
	while(FrontIsClear() == true && count < s)
	{		
		switch(direction)
		{
			case 0:
			{
				forwardrow--;
				if (forwardrow < 0 || forwardrow >= GetNumRows())
					return false;			
				break;
			}
			case 1:
			{
				forwardcol--;
				if (forwardcol < 0 || forwardcol >= GetNumCols())
					return false;
				break;	
			}
			case 2:
			{
				forwardrow++;
				if (forwardrow < 0 || forwardrow >= GetNumRows())
					return false;
				break;
			}
			case 3:
			{
				forwardcol++;
				if (forwardcol < 0 || forwardcol >= GetNumCols())
					return false;
				break;	
			}
		}

		mover_arr[forwardrow][forwardcol] = ' ';
		count++;
	}
	
	r_position = forwardrow;
	c_position = forwardcol;	
	
	return true;

}

// ****************************************************************
// Toggle whether or not moved path is shown.					  *
// ****************************************************************

void Grid::TogglePath()
{
	path = !path;
}

// ****************************************************************
// Turn mover to the left.										  *
// ****************************************************************

void Grid::TurnLeft()
{
	int d = direction;
	int compass[] = {NORTH,WEST,SOUTH,EAST};

	// Mover turns 90 degrees to left.
	if (direction == 3)
		d = compass[0];
	else if (direction == 2)
		d = compass[3];
	else if (direction == 1)
		d = compass[2];
	else if (direction == 0)
		d = compass[1];
	
	direction = d;
}

// ****************************************************************
// Put down an item at the mover's position.					  *
// ****************************************************************

void Grid::PutDown()
{
	int MAXitems = GetNumRows() * GetNumCols();
	int r_item = GetRow();
	int c_item = GetCol();

	// Inserting item row and column into arrays for each.
	if (items < MAXitems)
	{
		ritemlist[items] = r_item;
		citemlist[items] = c_item;

		items++;
	}

}

// ****************************************************************
// Put down an item at (r,c), if possible.						  *
// ****************************************************************

bool Grid::PutDown(int r, int c)
{
	int MAXitems = GetNumRows() * GetNumCols();
	int r_item = r;
	int c_item = c;

	bool status = false;

	// Inserting item user input row and column.
	if (items < MAXitems)
	{
		ritemlist[items] = r_item;
		citemlist[items] = c_item;

		items++;
		status = true;
	}

	return status;
}

// ****************************************************************
// Pick up item at current position.							  *
// ****************************************************************

bool Grid::PickUp()
{
	int MAXitems = GetNumRows() * GetNumCols();
	int r_item = GetRow();
	int c_item = GetCol();

	bool status = false;

	// Item in specific row and column will be deleted.
	for (int i = 0; i < items; ++i)
	{
		if (r_item == ritemlist[i] && c_item == citemlist[i])
		{	
			for (int j = i; j < items; ++j)
			{

				ritemlist[j] = ritemlist[j+1];

				citemlist[j] = citemlist[j+1];
			}

			items--;
			status = true;
		}

	}

	return status;


}

// ****************************************************************
// Put a block at (r,c), if possible.							  *
// ****************************************************************

bool Grid::PlaceBlock(int r, int c)
{
	int MAXblocks = GetNumRows() * GetNumCols();
	int r_block = r;
	int c_block = c;

	// Blocks placed at user input positions.
	if (blocks < MAXblocks)
	{
		grid_arr[r_block][c_block] = '#';
		mover_arr[r_block][c_block] = '#';

		blocks++;
		return true;
	}
	else return false;
}

// ****************************************************************
// Grow the grid by gr rows, gc columns.						  *
// ****************************************************************

void Grid::Grow(int gr, int gc)
{
	// Rows and columns being added.
	int addrows = gr;
	int addcols = gc;

	// Rows and columns already in array.
	int r_current = GetNumRows();
	int c_current = GetNumCols();

	// Total new number of rows and columns.
	int r_total = r_current + addrows;
	int c_total = c_current + addcols;

	// When exceeding the maximum value, rows and columns are set to the max.
	if (r_total > MAX_R)
	{
		r_total = MAX_R;
	}
	
	if (c_total > MAX_C)
	{
		c_total = MAX_C;
	}
	
	rows = r_total;
	columns = c_total;
	
}

// ****************************************************************
// Display the grid on screen.									  *
// ****************************************************************

void Grid::Display() const
{
	char orient;

	bool positionflag; // Whether or not there's an item and mover.
	bool itemflag; // Whether or not there's an item.
	bool blockflag; // Whether or not there's a block.

	// Orientation to print.
	switch(direction)
	{
		case 0:
			orient = '^';
			break;
		case 1:
			orient = '<';
			break;
		case 2:
			orient = 'v';
			break;
		case 3:
			orient = '>';
			break;
	}

	cout << "The Grid:" << "\n";

	for (int i = 0; i < GetNumRows(); ++i)
		{
			for (int j = 0; j < GetNumCols(); ++j)
			{		
				
				if (i == r_position && j == c_position)
				{
					// Check if an item and mover positon.
					for (int k = 0; k < items; ++k)
					{
						if (i == ritemlist[k] && j == citemlist[k])
						{
							cout << "@ ";
							positionflag = true;
							break;
						}
						else positionflag = false;
					}

					if (positionflag == false)
					{
						cout << orient << " ";
					}
				}

				else
				{	
					// Check if an item in grid space.
					for (int k = 0; k < items; ++k)
						{
							if (i == ritemlist[k] && j == citemlist[k])
							{
								cout << "0 ";
								itemflag = true;
								break;
							}
							else itemflag = false;
						}
					// When toggle is set to OFF. 
					if (itemflag == false && path == false)
					{
						cout << grid_arr[i][j] << " ";
					}
					// When toggle is set to ON (default).
					else if (itemflag == false && path == true)
					{
						cout << mover_arr[i][j] << " ";
					}

				}

			}

			cout << endl;
		}

	cout << "\n";

}

// ****************************************************************
// Accessor: Check to see if space in front of mover is clear.	  *
// ****************************************************************

bool Grid::FrontIsClear() const
{
	int frontrow = GetRow();
	int frontcol = GetCol();

	switch(direction)
	{
		case 0:
		{
			frontrow--;
			if (grid_arr[frontrow][frontcol] == '#' || mover_arr[frontrow][frontcol] == '#')
				return false;
			return true;
		}
		case 1:
		{
			frontcol--;
			if (grid_arr[frontrow][frontcol] == '#' || mover_arr[frontrow][frontcol] == '#')
				return false;
			return true;			
		}
		case 2:
		{
			frontrow++;
			if (grid_arr[frontrow][frontcol] == '#' || mover_arr[frontrow][frontcol] == '#')
				return false;			
			return true;
		}
		case 3:
		{
			frontcol++;
			if (grid_arr[frontrow][frontcol] == '#' || mover_arr[frontrow][frontcol] == '#')
				return false;
			return true;
		}
	}

}

// ****************************************************************
// Accessor: Check to see if space to right of mover is clear.	  *
// ****************************************************************

bool Grid::RightIsClear() const
{
	int rightrow = GetRow();
	int rightcol = GetCol();

	switch(direction)
	{
		case 0:
		{
			rightcol++;
			if (grid_arr[rightrow][rightcol] == '#' || mover_arr[rightrow][rightcol] == '#')
				return false;			
			return true;
		}
		case 1:
		{
			rightrow--;
			if (grid_arr[rightrow][rightcol] == '#' || mover_arr[rightrow][rightcol] == '#')
				return false;
			return true;			
		}
		case 2:
		{
			rightcol--;
			if (grid_arr[rightrow][rightcol] == '#' || mover_arr[rightrow][rightcol] == '#')
				return false;			
			return true;
		}
		case 3:
		{
			rightrow++;
			if (grid_arr[rightrow][rightcol] == '#' || mover_arr[rightrow][rightcol] == '#')
				return false;
			return true;			
		}
	}

}

// ****************************************************************
// Accessor: Return row of the mover.							  *
// ****************************************************************

int Grid::GetRow() const
{
	return r_position;
}

// ****************************************************************
// Accessor: Return column of the mover.						  *
// ****************************************************************

int Grid::GetCol() const
{
	return c_position;
}

// ****************************************************************
// Accessor: Return number of rows in the grid.					  *
// ****************************************************************

int Grid::GetNumRows() const
{
	return rows;
}

// ****************************************************************
// Accessor: Return number of columns in the grid.				  *
// ****************************************************************

int Grid::GetNumCols() const
{
	return columns;
}
