/// \Main.cpp
/// \Handles main program loop

//File includes
#include <iostream>			// Allows for the use of cin, cout
#include <vector>			// Allows for the use of vectors
#include <math.h>			// Allows for use of math functions
#include <string>			// Allows for the use of strings and string manipulation
#include <memory>			// used for pointers
#include <string>
#include <algorithm>		// Access to algorithm
#include <functional>		// Allows for use of functional objects

//Lib includes
#include <SDL.h>			// Access to SDL2 
#include <glm/glm.hpp>		// GLM Libs
#include <glm/gtc/matrix_transform.hpp>	// GLM Libs
#include <glm/gtc/type_ptr.hpp>			// GLM Libs
#include "SDL.h"			// Accses to SDL2 libarys
#include <SDL_ttf.h>		// Allows access to ttf

//Header includes
#include "Hash.h"			// Allows the use of the hash header file
#include "ProjectControl.h"	// Allows the use of Project control header
#include "Index.h"			// Allows the use of the index header
#include "Particle.h"		// Allows the use of the particle header

//Program prototypes
int GameLoop(int _gridWidth, int _gridHeight, int _particleSystemSize, int _red, int _green, int _blue);
void hashTableBuild(std::vector<Index*>& indexes, int const gridHeight, int const gridWidth);
void particleSystem(std::vector<std::shared_ptr<Particle>>& Particles, std::vector<Index*>& indexes, int _particleSystemSize, int _red, int _green, int _blue);
void addParticlesToList(std::vector<std::shared_ptr<Particle>>& Particles, std::vector<Index*>& indexes, int _particleSystemSize, int _amountToAdd);


int main(int argc, char *argv[])
{
	srand(NULL);				// Allows the use of srand

	int windowWidth = 730;	//1152	// The window width
	int windowHeight = 900;	// 900	// The window height

	int gridWidth = 11;			// Index grid Width
	int gridHeight = 11;		// Index grid height
				 
	int particleSystemSize = 2;  // Size of my particle system

	int red = 255;				// Red pixel value
	int blue = 0;				// Blue pixel value
	int green = 0;				// Green pixel value

	float timer = 0.0f;			// float for timer

	if ( !OOT::sdlSetUp(windowWidth, windowHeight) )	// If sdl set up doesn't have a window w/h
	{
		return -1;										// Return 1 and close
	}

	GameLoop(gridWidth, gridHeight, particleSystemSize, red, green, blue);	// Calls main game loop
}

int GameLoop(int _gridWidth, int _gridHeight, int _particleSystemSize, int _red, int _green, int _blue)
{
	int index;				// What index the pixel is in
	float frames = 0;		// Frames
	float lastUpdate = 0;	// Last frame update
	float frameRate = 0;	// Current frame rate
	int framesDisplay;		// Display frame in int to screen
	int lastIndex = 0;		// last index the pixel was in
	int amountToAdd = 10;	// How much to add to particles vector
	int amountToRemove = 10;// How much to remove
	Hash HashOBJ;			// Hash Object
	const Uint8* key = SDL_GetKeyboardState(NULL);	// Allows easy use of the SDL keyboard
	std::vector<Index*> indexes;					// Index partitions for pixels to be stored in
	std::vector<std::shared_ptr<Particle>> Particles;	// Shared ptr for Paricles

	hashTableBuild(indexes, _gridHeight, _gridWidth);									// Build my hash table 
	particleSystem(Particles, indexes, _particleSystemSize, _red, _green, _blue);		// Builds particles system
	std::string fpsString = "00";														// Set string to be 00 at start
	std::string pixelString = "00";

	TTF_Font *font = TTF_OpenFont("JAi_____.ttf", 58);	
	TTF_Font *font2 = TTF_OpenFont("JAi_____.ttf", 58);									// Assign the text font and size
	SDL_Colour colour = { 255, 255, 255, 255 };											// Give it a colour, white in this case
	
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, fpsString.c_str(), colour);	// Create a surface with the font, what to output, and the colour
	SDL_Surface *text2Surface = TTF_RenderText_Solid(font2, pixelString.c_str(), colour); // Create a second surface
	
	SDL_Texture *text = SDL_CreateTextureFromSurface(OOT::_renderer, textSurface);		// Create a texture to be rendered
	SDL_Texture *text2 = SDL_CreateTextureFromSurface(OOT::_renderer, text2Surface);	// Create a texture to be rendered again
	
	SDL_FreeSurface(textSurface);	// Free the surface
	SDL_FreeSurface(text2Surface);	// Free the surface of txt 2
	
	SDL_Rect textRect;				// Create a rect for the position on the screen
	SDL_Rect text2Rect;				// Create a second rect for the position of the second text
	textRect.x = 20;				// Text x, y
	textRect.y = 665;
	textRect.w = 256;				// Text width and height
	textRect.h = 64;
	text2Rect.x = 20;
	text2Rect.y = 735;
	text2Rect.w = 256;
	text2Rect.h = 64;

	textSurface = nullptr;								// Set the text surface as a null ptr as its not needed anymore
	text2Surface = nullptr;

	while (OOT::ProcessFrame())							// While the frame is processing
	{
		frames++;										// Increase frames
		if (lastUpdate < SDL_GetTicks() - 1 * 1000)		// if the last update is less that the SDL ticks 
		{
			lastUpdate = SDL_GetTicks();				// Set last update to SDL ticks
			framesDisplay = (int)frames;				// Convert float to int
			fpsString = "fps: " + std::to_string(framesDisplay);
			frames = 0;									// Frames int set to 0
		}
		frameRate = framesDisplay;						// Frame rate is equal to frame display
		
		if (key[SDL_SCANCODE_UP])						// If the up key is pressed
		{	
			if (Particles.size() <= 40000)				// If the particles system size is less than 5000
			{
				addParticlesToList(Particles, indexes, _particleSystemSize, amountToAdd); // Call the add partcles function
			}
		}

		pixelString = "Pixel Count: " + std::to_string(Particles.size());


		OOT::setBackground(0, 0, 0);				// Set the background colour to black

		for (int i = 0; i < Particles.size(); i++)	// While i is less than total particle size
		{
			Particles.at(i)->Update();				// Send them to update
		}

		for (int i = 0; i < indexes.size(); i++)	// While i is less than total index size
		{
			indexes.at(i)->draw();					// Send them to draw
			indexes.at(i)->checkCollision();		// Check collisions on each index with the particles contained
		}
		
		std::vector<int> indexToRemove;				// List of vectors to be cleared

		for (int x = 0; x < indexes.size(); ++x)	// Loop through the indexes
		{
			for (int y = 0; y < indexes[x]->GetparticlesInIndex().size(); ++y)						// Check all particles in each index 
			{
				std::shared_ptr<Particle> currentParticle = indexes[x]->GetparticlesInIndex()[y];	// current p is equaly to the next particle in that index

				index = HashOBJ.m_HashFunction(currentParticle->GetX(), currentParticle->GetY());	// Get x and y for current particle

				if (currentParticle->GetIndex() != index)						// If the index is no longer equal - Has moved
				{
					currentParticle->SetPreIndex(currentParticle->GetIndex());	// Set current particle pos to is previous positions
					currentParticle->SetIndex(index);							// Get new location and set it to current
					indexes[index]->GetparticlesInIndex().emplace_back(currentParticle);					// Find what index that particle is now in and add it to the list of particles in that index
					indexes[x]->GetparticlesInIndex().erase(indexes[x]->GetparticlesInIndex().begin() + y);	// Current index get the particles in that index
					y--;																					// Go into that current particle contained list, hashed into that bucket
				}																							// And that current pixel erase it 
				currentParticle->Draw();// Send the current pixel to draw	
			}
			indexToRemove.clear();		// Clear 
		}
		SDL_DestroyTexture(text);		// Destroy the texture to update each frame
		SDL_DestroyTexture(text2);
																				// Output the fps 
		textSurface = TTF_RenderText_Solid(font, fpsString.c_str(), colour);	// Sets the surface with the font, the dps output and the colour
		text = SDL_CreateTextureFromSurface(OOT::_renderer, textSurface);		// Create the texture with the renderer
		SDL_FreeSurface(textSurface);											// Free the surface to free memory

		text2Surface = TTF_RenderText_Solid(font2, pixelString.c_str(), colour);	// Sets the surface with the font, the dps output and the colour
		text2 = SDL_CreateTextureFromSurface(OOT::_renderer, text2Surface);		// Create the texture with the renderer
		SDL_FreeSurface(text2Surface);											// Free the surface to free memory

		SDL_RenderCopy(OOT::_renderer, text, NULL, &textRect);					// Send the image to the screen
		SDL_RenderCopy(OOT::_renderer, text2, NULL, &text2Rect);
	}
	SDL_DestroyTexture(text);													// Destroy the text at the end of free memory
	SDL_DestroyTexture(text2);
	text = nullptr;																// Null prt the text
	text2 = nullptr;
	
	return OOT::showAndHold();													// Show and hold the screen
	
}

void hashTableBuild(std::vector<Index*>& indexes, int const gridHeight, int const gridWidth)	// Creating the hash table
{
	for (int y = 0; y < gridHeight; ++y)		// Loop through the grid height
	{
		for (int x = 0; x < gridWidth; ++x)		// Loop through the grid width
		{
			Index* indexChunk = new Index();		// Create a new index object called indexChunk
			indexChunk = new Index(x, y, 10, 10);	// Give index chunck its values
			indexes.emplace_back(indexChunk);		// Push back them chunks into indexes vector
		}
	}
}

void particleSystem (std::vector<std::shared_ptr<Particle>>& Particles, std::vector<Index*>& indexes, int _particleSystemSize, int _red, int _green, int _blue)	// Particle System function
{
	int index;		// Create a var for index
		
	for (int x = 0; x < _particleSystemSize; x++)	// Loop through the total particle size
	{
		std::shared_ptr<Particle> particleParts = std::make_shared<Particle>(rand() % 640, rand() % 640, 255, 255, 255);	// Creates a share ptr of particles with random x,y and white rgb values
		indexes[0]->GetparticlesInIndex().push_back(particleParts);															// Starts with the first index and pushs the particles into the index
		Particles.emplace_back(particleParts);																				// particles contained vector
	}
}

void addParticlesToList(std::vector<std::shared_ptr<Particle>>& Particles, std::vector<Index*>& indexes, int _particleSystemSize, int _amountToAdd) // Add particles to the list function
{
	int index; // Create an var for index

	for (int x = 0; x < _amountToAdd; x++)		// Loop the amount of particles you need to add
	{
		std::shared_ptr<Particle> particleParts = std::make_shared<Particle>(rand() % 640, rand() % 640, 255, 255, 255); // Create a new particle part with rand x,y and white rgb
		indexes[0]->GetparticlesInIndex().push_back(particleParts);		// Push back them particles into the hash
		Particles.emplace_back(particleParts);							// push the particle back into paricles
	}
	_amountToAdd += 10;													// Add 10
}



