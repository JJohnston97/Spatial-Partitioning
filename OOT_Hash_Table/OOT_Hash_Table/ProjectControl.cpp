/// \PorjectControl.cpp
/// \breif deals with SDL set up and project management

// File includes
#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>

// Header Includes
#include "ProjectControl.h"


// Using name space
namespace OOT
{
	SDL_Renderer *_renderer;	// SDL renderer used to render to screen
	SDL_Window *_window;		// SDL window used to create a window
	int _windowWidth, _windowHeight;	// Width and height of screen int
	unsigned int _lastTime;				// Last time for fps

}


bool OOT::sdlSetUp(int windowWidth, int windowHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)						// If an error is to happen
	{
		std::cout << "Something went wrong" << std::endl;	// Out put the error
		return false;										// Close the window
	}
	if (TTF_Init() < 0)
	{
		std::cout << "Error: " << TTF_GetError() << std::endl;

	}
	
	_windowWidth = windowWidth;			// Window width set
	_windowHeight = windowHeight;		// Window height set
	
	int windowPosX = 100; // Window X position
	int windowPosY = 100; // Window Y position

	_window = SDL_CreateWindow("OOT", windowPosX, windowPosY, _windowWidth, _windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	// Create the window for SDL, name, position


	if (!_window)		// If the widow cannot open
	{
		std::cout << "Cannot create SDL window" << std::endl;	
		return false;	// Exit is the only thing to do
	}

	OOT::_renderer = SDL_CreateRenderer(_window, -1, 0);		// Create a renderer for the screen


	if (!_renderer)		// If cannot create renderer
	{
		std::cout << "Cannot obtain SDL rendering context" << std::endl;
		return false;	// Exit is the only thing to do
	}

	
	_lastTime = SDL_GetTicks();
	

	return true;
}

void OOT::setBackground(int red, int green, int blue)
{
	SDL_SetRenderDrawColor(_renderer, red, green, blue, 255); // Set the colour for drawing
	SDL_RenderClear(_renderer);								  // Clear the entire screen to our selected colour

}

void OOT::drawPixel(int pixelX, int pixelY, int red, int green, int blue)
{
	
	SDL_SetRenderDrawColor(_renderer, red, green, blue, 255);  // Set the colour for drawing
	SDL_RenderDrawPoint(_renderer, pixelX, pixelY);			   // Draw a pixel to the screen
}


bool OOT::ProcessFrame()
{
	SDL_RenderPresent(_renderer);
	SDL_Event incomingEvent;

	while (SDL_PollEvent(&incomingEvent)) // Check if there is an event in the queue
	{
		switch (incomingEvent.type)		  // Switch depending on what type comes in
		{
		case SDL_QUIT:					  // Have been asked to quit
			return false;				  // Close the window 
		case SDL_KEYUP:
			switch (incomingEvent.key.keysym.sym) // Checks if the key input is esc
			{
			case SDLK_ESCAPE:			  // If it is
				return false;			  // Close the window
			}
		}
	}
	

	unsigned int current = SDL_GetTicks();	// Work out the time between each frame
	float deltaTs = (float)(current - _lastTime) / 1000.0f;
	_lastTime = current;					// Set last time to current amount of time

	


	if (deltaTs < (1.0f / 60.0f))	// if the time is greater than
	{
		SDL_Delay((unsigned int)(((1.0f / 60.0f) - deltaTs)*1000.0f));	// Create a delay to make frames even
	}



	return true;

}

void OOT::cleanUp()  // Clean up used to end the program
{

	SDL_DestroyWindow(_window);		// Destroy the window
	SDL_Quit();						// Quit the application
}


int OOT::showAndHold()			// Show and hold presents and holds the screen
{

	SDL_RenderPresent(_renderer);		// Present the screen
	bool go = true;						// Bool go for while loop
	while (go)
	{

		SDL_Event incomingEvent;			// Waits for event
		SDL_WaitEvent(&incomingEvent);
		switch (incomingEvent.type)
		{
		case SDL_QUIT:			// If event is quit
			go = false;			// Quit
			break;


		case SDL_KEYUP:		// If key is pressed
			switch (incomingEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE: // if escape, return 0 and close
				return 0;
			}

		}
	}

	cleanUp();	// Clean up at the end to finish everything off
	return 0;
}