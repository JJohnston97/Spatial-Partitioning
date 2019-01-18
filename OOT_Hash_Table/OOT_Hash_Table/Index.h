/// \Index.h
/// \Index management
/// \Author Jamie Johnsto
/// \To create, draw and handle indexes

#ifndef INDEX_H
#define INDEX_H

// File Includes
#include <vector>		// Allows use of vector
#include <memory>		// Allows the use of shared ptr

//Header Includes
#include "Particle.h"	// Inlucde particle header

class Index
{
public:
	Index();				// Index Obj empty
	Index(int _x, int _y, int _width, int _height); // Index obj with definition 

	~Index();				// Index Destructor


	virtual void draw();	// Draw function for my indexes

	int m_indexID;			// Index ID assigned to each index

	int GetX() { return m_positionX; }	// Get X function to be able to get the X position of the index
	int GetY() { return m_positionY; }	// Get Y function to be able to get the Y position of the index
	std::vector<std::shared_ptr<Particle>>& GetparticlesInIndex() { return particlesInIndex; } // Used to get the particles contained within the index
	void deleteParticle(int _particleIndex);  // Delete particle function used to remove particles from index within hash
	void checkCollision();					  // Used to check collision

protected:
	
	int m_positionX;			// X pos of index
	int m_positionY;			// Y pos of index
	std::vector<std::shared_ptr<Particle>> particlesInIndex; // Create a vector called get particles in index, with a shared ptr to particles, contained in each index 

};

#endif // !HASH_H