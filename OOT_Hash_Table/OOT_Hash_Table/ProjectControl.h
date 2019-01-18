/// \ProjectControl.h
/// \Project controller for organisation
/// \Author Jamie Johnston (Inspired by CGG level 4 project)
/// \To handles all background framework for the project


#ifndef _PROJECT_CONTROL_
#define _PROJECT_CONTROL_


namespace OOT	// Using Object Orientated Technique namespace
{
	extern SDL_Renderer *_renderer;  // Allows access to renderer in other files

	bool sdlSetUp(int windowWidth, int windowHeight);	// Set up SDL function

	void setBackground(int red, int green, int blue);	// Set screen Colour Function
		
	void drawPixel(int pixelX, int pixelY, int red, int green, int blue); // Draw pixel function

	int showAndHold(); // Show and Hold screen function
	
	bool ProcessFrame(); // Returns false when program exit

	void cleanUp();		// For cleaning up closed graphics

	
};

#endif // !_PROJECT_CONTROL_

