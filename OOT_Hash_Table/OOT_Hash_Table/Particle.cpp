/// \Particle.cpp
/// \breif deals with creations and handing of particles

// File includes
#include <time.h>		// Allows the use of time
#include <vector>		// Allows use of vector
#include <SDL.h>		// Allows use of SDL

// Header includes
#include "ProjectControl.h"	// Project control for management
#include "Index.h"			// Indexes for pixels to be draw to etc
#include "Particle.h"		// Particle H for particles info


Particle::Particle() //Empty Constructor
{
}

Particle::Particle(int _x, int _y, int _red, int _green, int _blue) // Particle Constructor
{

	m_velocity = { 1, 1 };	// Velocity set to 1 x, 1 y
	m_position.x = _x;		// Position is equal to x set when created in partcileSystem function
	m_position.y = _y;		// Position is equal to x set when created in partcileSystem function
	m_offset = 1;			// Offset of 1 alway applied
	m_red = _red;			// Red is equal to red value set
	m_green = _green;		// Green is equal to green value set
	m_blue = _blue;			// Blue is equal to blue value set
	m_maxVel = 1.0f;		// Max velocity
	m_minVel = -1.0f;		// Min velocity

	m_previousIndex = 0;	// Previous index number

}

void Particle::Draw()
{
	if (m_index == 0 || m_index == 1 || m_index == 10 || m_index == 11) // If the pixel is within these index
	{
		m_red = 255;		// Change the colour to red
		m_green = 0;
		m_blue = 0;
	}
	else if (m_index == 8 || m_index == 9 || m_index == 18 || m_index == 19) // If in these
	{
		m_red = 0;
		m_blue = 0;			// Be green
		m_green = 255;
	}
	else if (m_index == 98 || m_index == 99 || m_index == 88 || m_index == 89) // In these
	{
		m_red = 0;
		m_green = 0;
		m_blue = 255;		// Be blue
	}
	else if (m_index == 90 || m_index == 91 || m_index == 80 || m_index == 81) // In these
	{
		m_red = 247;
		m_green = 255;		// Be yellow
		m_blue = 20;
	}
	/*else
	{
		m_red = 255;		// If you uncomment this the colision colour will not change
		m_blue = 255;		// But it will show the pixels moving in and out the the
		m_green = 255;		// Hash vectors correctly in the corners
	}*/

	OOT::drawPixel(m_position.x + 1, m_position.y + 1, m_red, m_green, m_blue); // Draw the pixel at its position with the colours given
	
}
void Particle::Update()		// Update handles movement
{
	//SCREEN BOUNDRIES
	if (m_position.x + m_velocity.x >= 640)		// If the position is greater than
	{
		m_velocity.x *= -1;		// Reverse its velocity

	}
	else if (m_position.x + m_velocity.x <= 0)	// If x is less than or equal to 0
	{

		m_velocity.x *= -1;		// Reverse its velocity
	}
	
	if (m_position.y + m_velocity.y >= 640)		// If y is greater than or equal to
	{
		m_velocity.y *= -1;		// Reverse its velocity
	}
	else if (m_position.y + m_velocity.y <= 0)	// if y is less than or equal to
	{
		m_velocity.y *= -1;		// Reverse its velocity

	}

	
	m_position.x += m_velocity.x;	// Movement for x pixels
	m_position.y += m_velocity.y;	// Movement for y pixels

	

}

void Particle::SetVel()		// Called When colided
{
	m_velocity.x *= -1;		// Reverse its velocity
	m_velocity.y *= -1;		// Reverse its velocity

}

void Particle::SetColour()	// Called When colided 
{
	m_red = 196;		// Set colour to purple
	m_blue = 255;
	m_green = 0;
}

	
Particle::~Particle()	// Destructor
{

}