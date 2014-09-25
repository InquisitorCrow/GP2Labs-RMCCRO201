// Header files
#include <iostream>
// Header for SDL2 functionality
#include <SDL.h>

// Global variables go here
// Pointer to our SDL Windows
SDL_Window * window;

void InitWindow(int width, int height, bool fullscreen){
	// Create a window
	window = SDL_CreateWindow(
		"Lab 1",			// Window title
		SDL_WINDOWPOS_CENTERED,		// x position, centred
		SDL_WINDOWPOS_CENTERED,		// y position, centred
		width,					// Width in pixels
		height,					// Height in pixels
		SDL_WINDOW_OPENGL		// Flags
		);
}

// Used to cleanup once we exit


// Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
bool running = true;

// Global functions
void CleanUp(){
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Main Method - Entry Point
int main(int argc, char * arg[]) {
	// init everything - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init" << SDL_GetError() << std::endl;
		
		return -1;
	}
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);

	SDL_Event event;
	while (SDL_PollEvent(&event)){
		//Get event type
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE){
			// set our boolean which controls the game loop to false
			running = false;
		}
	}


	CleanUp();

	return 0;
}