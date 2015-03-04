//Using SDL and standard IO
#include <SDL.h>
#include "LTimer.h"
#include <stdio.h>
#include "TestPlayerGameObject.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

int main(int argc, char *argv[])
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	SDL_Renderer* gRenderer = NULL;

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 255 };


	//The frames per second cap timer
	LTimer capTimer;

	TestPlayerGameObject playerObject(SDL_Rect{ 100, 100, 10, 10 }, SDL_Color{255,0,0,255});

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			//While application is running
			while (!quit)
			{
				//Start cap timer
				capTimer.start();

				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type== SDL_MOUSEBUTTONDOWN)
					{
						//Get mouse position
						int x, y;
						Uint32 buttonState = SDL_GetMouseState(&x, &y);

						if (buttonState & SDL_BUTTON_LMASK)
						{
							playerObject.SetSelect(playerObject.CheckBound(SDL_Rect{ x, y, 10, 10 }));
						}
						else if (buttonState & SDL_BUTTON_RMASK && playerObject.IsSelected())
						{
							playerObject.Move(SDL_Point{ x, y });
						}

					}



				}

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				playerObject.Draw(gRenderer);

				//Update screen
				SDL_RenderPresent(gRenderer);

				//If frame finished early
				int frameTicks = capTimer.getTicks();
				if (frameTicks < SCREEN_TICKS_PER_FRAME)
				{
					//Wait remaining time
					SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
				}
			}
		}
	}
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}