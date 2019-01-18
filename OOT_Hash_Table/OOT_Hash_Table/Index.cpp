/// \file Index.cpp
/// \breif handles my index creations for the hash table

// Additional File Includes
#include <vector>			// Allows use of vector
#include <SDL.h>			// Allows use of SDL

// Header Includes
#include "ProjectControl.h"	// Project control h for draws
#include "Index.h"			// Index h for index info

Index::Index()		// Index empty constructor
{


}

Index::Index(int _x, int _y, int _width, int _height)	// Constructor with vars
{
	m_positionX = _x;		// Position is equal to given positions
	m_positionY = _y;		// Position is equal to given positions

}

void Index::draw()	// Draw function for my index
{

	OOT::drawPixel(m_positionX * 64 + 1, m_positionY * 64, 0, 255, 255);
	OOT::drawPixel(m_positionX * 64 + 2, m_positionY * 64, 0, 255, 255);	// Draw the crosses that indecate the boxes for my hash table
	OOT::drawPixel(m_positionX * 64 + 3, m_positionY * 64, 0, 255, 255);	// Tested against FPS and is faster than using a for loop to draw them all
	OOT::drawPixel(m_positionX * 64, m_positionY * 64 + 1, 0, 255, 255);	// Trying both a loop and single drawn dots the fps was faster this way
	OOT::drawPixel(m_positionX * 64, m_positionY * 64 + 2, 0, 255, 255);
	OOT::drawPixel(m_positionX * 64, m_positionY * 64 + 3, 0, 255, 255);
	OOT::drawPixel(m_positionX * 64 - 1, m_positionY * 64, 0, 255, 255);
	OOT::drawPixel(m_positionX * 64 - 2, m_positionY * 64, 0, 255, 255);
	OOT::drawPixel(m_positionX * 64 - 3, m_positionY * 64, 0, 255, 255);
	OOT::drawPixel(m_positionX * 64, m_positionY * 64 - 1, 0, 255, 255);
	OOT::drawPixel(m_positionX * 64, m_positionY * 64 - 2, 0, 255, 255);
	OOT::drawPixel(m_positionX * 64, m_positionY * 64 - 3, 0, 255, 255);
	
}

Index::~Index() // Destructor
{

}



void Index::deleteParticle(int _particleIndex)	// Delete particles from the index particles
{												// contained vector
	particlesInIndex.erase(particlesInIndex.begin() + _particleIndex);	// Remove the partciles index

}
void Index::checkCollision() // Check collisions within each index
{							 // Reason for hashing is so that each index checks collisions within itself rather than
	if (particlesInIndex.size() > 1)		// one pixel checking itself agains every other pixel on the screen
	{
		for (int i = 0; i < particlesInIndex.size(); ++i)	// Loop through the particlesinIndex vec in each index
		{
			int PosOfFirstX = particlesInIndex[i]->GetX();	// Take the x and y of the first
			int PosOfFirstY = particlesInIndex[i]->GetY();	// and compare

			for (int p = 0; p < particlesInIndex.size(); ++p)
			{
				if (p == i)	// If the positions is equal to itself
				{

					continue;	// Continue

				}

				if (particlesInIndex[p]->GetX() + 1 == PosOfFirstX)	// If the x is the same
				{
					if (particlesInIndex[p]->GetY() + 1 == PosOfFirstY)	// If the y is the same
					{
						particlesInIndex.at(i)->SetVel();		// They are coliding so set their new velocity
						particlesInIndex.at(i)->SetColour();	// Set their new colour (Purple)

					}
				}
			}
		}
	}
}




