/// \file Hash.cpp
/// \brief handles my hash function


// Additional File Inlcudes
#include <iostream>			// Allows for the use of cin, cout
#include <math.h>			// Allows for use of math functions
#include <string>			// Allows for the use of strings and string manipulation
#include <vector>			// Allows for the use of vectors
#include "Hash.h"			// Allows the use of the hash header file

Hash::Hash()
{

}

int Hash::m_HashFunction(int _x, int _y)

{
	int hash = 0;					// Hash set to 0
	int xgrid = _x / m_cellLength;	//calc grid x
	int ygrid = _y / m_cellLength;  // calc grid y

	int index = ygrid * m_indexSpacing + xgrid;	// calc the Index

	return index;	// Return index
}

