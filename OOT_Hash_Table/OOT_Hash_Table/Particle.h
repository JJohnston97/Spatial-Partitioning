/// \Particle.h
/// \Particle management
/// \Author Jamie Johnsto
/// \To create, draw and handle particles

#ifndef PARTICLE_H
#define PARTICLE_H

// File Includes
#include <iostream>		// Allows to write to console
#include <vector>		// Allows the use of vector
#include <SDL.h>		// Allows the use of SDL
#include <glm/glm.hpp>	// One of three glm includes
#include <glm/gtc/matrix_transform.hpp>	// GLM include
#include <glm/gtc/type_ptr.hpp>			// GLM includes for vec2/3

class Particle
{
public:

	Particle();	//Empty particle constructor
	Particle(int _x, int _y, int _red, int _green, int _blue);	// Constuctor with vars
	
	~Particle();	// Destructor

	virtual void Draw();	// Draw function for particles
	virtual void Update();	// Update function called every frame

	int GetX() { return m_position.x; }	// Get x position function
	int GetY() { return m_position.y; }	// Get y position function
	void SetIndex(int _value) { m_index = _value; }	// Set the index
	int GetIndex() { return m_index; }				// Get current index 
	int GetPreIndex() { return m_previousIndex; }		// Get previous Index of particle
	void SetPreIndex(int _previousIndex) { m_previousIndex = _previousIndex; }	// Set the pervious index
	void SetVel();			// Set the vel of pixel when colide
	void SetColour();		// Set the colour of the pixel when they colide

	bool m_dead;		// Is pixel dead
	float m_time;		// Time var
	float m_lifeTime;	// life time of pixel 

protected:

	glm::vec2 m_particlePosition;	// Vec 2 for particle positions
	glm::vec2 m_velocity;			// Vec 2 for velocity 
	SDL_Rect m_position;			// SDL rect for position works similar to vec 2
	int m_offset;				// offset of pixels for spawn
	int m_index;				// Index value, first part of hash
	int m_previousIndex;		// Previous index of pixel stored index 
	int m_red;					// red for rgb
	int m_green;				// Green for rgb
	int m_blue;					// Blue for rgb
	float m_maxVel;				// Max velocity
	float m_minVel;				// min velocity

};

#endif // !PARTICLE_H
