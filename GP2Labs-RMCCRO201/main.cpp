// Header files
#include <iostream>
// Header for SDL2 functionality
#include <GL/glew.h>
#include <SDL.h>

#include <SDL_opengl.h>
#include <gl\GLU.h>


#include "Vertex.h"
// Global variables go here
GLuint triangleEBO;
GLuint triangleVBO;
// SDL GL Context
SDL_GLContext glcontext = NULL;
// Pointer to our SDL Windows
SDL_Window * window;

Vertex triangleData[] = {
	//Front
		{-0.5f, 0.5f, 0.5f,
		1.0f, 0.0f, 1.0f, 1.0f },// Top Left
			
		
		{-0.5f,-0.5f, 0.5f,
		1.0f, 1.0f, 0.0f, 1.0f },// Bottom Left
				
		
		{ 0.5f,-0.5f, 0.5f,
		0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right
				
		
		{ 0.5f, 0.5f, 0.5f,
		1.0f, 0.0f, 1.0f, 1.0f },// Top Right
				
		//back
		{-0.5f, 0.5f,-0.5f,
		1.0f, 0.0f, 1.0f, 1.0f },// Top Left
					
		
		{-0.5f,-0.5f,-0.5f,
		1.0f, 1.0f, 0.0f, 1.0f },// Bottom Left
						
		{ 0.5f,-0.5f,-0.5f,
		0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right
						
		
		{ 0.5f, 0.5f,-0.5f,
		1.0f, 0.0f, 1.0f, 1.0f },// Top Right
};


GLuint indices[] = {
	//front
	0, 1, 2,
	0, 3, 2,
	//left
	4, 5, 1,
	4, 1, 0,
	//right
	3, 7, 2,
	7, 6, 2,
	//bottom
	1, 5, 2,
	6, 2, 1,
	//top
	5, 0, 7,
	5, 7, 3,
	//back
	4, 5, 6,
	4, 7, 6
};



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

void initGeometry()
{
	// Create buffer
	glGenBuffers(1, &triangleVBO);
	// Make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	// Copy vertex data to vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);

	//create buffer
	glGenBuffers(1, &triangleEBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
	//Copy Index data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

}

// Function to draw
void render()
{
	// Set the clear colour (background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
	// Make the new VBO active. Repeat here as a sanity check (may have changed since initialisation)
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);

	// Establish its 3 coordinates per vertex with zero stride (space between elements in array and contain floating point numbers
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);
	// The last parameter basically says that the colours start 3 floats into each element of the array
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (void**)(3 * sizeof(float)));
	// Establish array contains vertices (not normals, colours, texture coords etc)
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	
	//Switch to Modelview
	glMatrixMode(GL_MODELVIEW);
	//Reset using the identity Matrix
	glLoadIdentity();
	
	
	//           CAMERA    // LOOK AT POINT //  Up axis of the camera
	//         X    Y    Z // X    Y     Z  // X    Y    Z
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0f, 0.0, 1.0, 0.0);
	//translate
	// Understand that it's X, Y and Closeness to the screen (Z)
	glTranslatef(-1.5f, 1.5f, -6.0f);
	// Actually draw the triangl;e giving the number of vertices provided
	glDrawElements(GL_TRIANGLES,sizeof(indices) / sizeof(GLuint),GL_UNSIGNED_INT, 0);


	// Newly added triangle
	//glTranslatef(2.0f, 2.0f, -3.0f);
	// Actually draw the triangl;e giving the number of vertices provided
	//glDrawArrays(GL_TRIANGLES, 0, sizeof(triangleData) / (3 * sizeof(float)));
	//Switch to ModelView
	//glMatrixMode(GL_MODELVIEW);
	//Reset using the Indentity Matrix
	//glLoadIdentity();
	//Translate to -5.0f on z-axis
	//glTranslatef(0.0f, 0.0f, -5.0f);
	//Begin drawing triangles
	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f); //Colour of the vertices
	//glVertex3f(0.0f, 1.0f, 0.0f); // Top
	//glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom Left
	//glVertex3f(1.0f, -1.0f, 0.0f); // Bottom Right
	//glEnd();


	// require to swap back and front buffer
	SDL_GL_SwapWindow(window);


}
// Function to update the game state
void update()
{

}


void CleanUp(){
	glDeleteBuffers(1, &triangleEBO);
	glDeleteBuffers(1, &triangleVBO);
	SDL_GL_DeleteContext(glcontext);
	
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Function to initialise OpenGL
void initOpenGL()
{
	// Create OpenGL Context
	glcontext = SDL_GL_CreateContext(window);
	// Something went wrong in creating the context, if it is still NULL
	if (!glcontext)
	{
		std::cout << "Error Creating OpenGL Context" << SDL_GetError() << std::endl;
	}
	
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

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/*Problem: glewInit failed, something is seriously wrong*/
		std::cout << "Error:" << glewGetErrorString(err) << std::endl;
	}

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
	initGeometry();
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

		update();
		render();
	}


	CleanUp();

	return 0;
}