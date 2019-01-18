/// \@Hash.h
/// \Hash table management
/// \Author Jamie Johnsto
/// \To organise hash table

#ifndef HASH_H
#define HASH_H

//File Includes
#include <iostream>			// Allows for the use of cin, cout
#include <vector>			// Allows for the use of vectors
#include <math.h>			// Allows for use of math functions
#include <string>			// Allows for the use of strings and string manipulation
#include <SDL.h>			// Allows for the use of SDL

// Header includes
class Hash	
{
private:

	static const int sizeOfTable = 100; // Size of my table
	
public:

	Hash();					// Hash object
	~Hash() {};				// Hash destructor

	int m_cellLength = 64;		// Cell length for hash table
	int m_indexSpacing = 10;	// each index space 
	int m_HashFunction(int _x, int _y);	// The hash function

protected:

	SDL_Renderer* m_renderer;		// Sdl renderer used for drawing
	SDL_Rect* m_Position;			// Posiiton
	
};

#endif // HASH_H
