// Header files
#include <iostream>
// Header for SDL2 functionality
#include <SDL.h>

#include <SDL_opengl.h>
#include <gl\GLU.h>

// Global variables go here

// SDL GL Context
SDL_GLContext glcontext = NULL;
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
	SDL_GL_DeleteContext(glcontext);
	
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Function to initialise OpenGL
void initOpenGL()
{
	// Smooth shading
	glShadeModel(GL_SMOOTH);

	// clear the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Clear the depth buffer to 1.0
	glClearDepth(1.0f);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// The depth test to use
	glDepthFunc(GL_LEQUAL);

	// Turn on best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

// Function to set/reset viewport
void setViewport(int width, int height)
{
	// screen ration
	GLfloat ratio;

	// make sure the height is always above 0
	if (height == 0){
		height = 1;
	}

	// calculate screen ration
	ratio = (GLfloat)width / (GLfloat)height;

	// Setup viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	//Change to poject matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Calculate perspective matrix, using glu library functions
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	//Swith to ModelView
	glMatrixMode(GL_MODELVIEW);

	//Reset using the Indentity Matrix
	glLoadIdentity();

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

	//Call our InitOpenGL Function
	initOpenGL();
	//Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);


	SDL_Event event;
	while (running){

	
		while (SDL_PollEvent(&event)){
			//Get event type
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE){
				// set our boolean which controls the game loop to false
				running = false;
			}
		}
	}


	CleanUp();

	return 0;
}