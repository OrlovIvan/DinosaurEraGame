#include "pch.h"
#include "PlayTableSDL.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

using namespace std;

#define SDL_MAIN_HANDLED

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gImageSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

//Loads individual image
/*SDL_Surface* loadSurface(std::string path)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    return loadedSurface;
}*/
SDL_Surface* loadSurface(std::string path)
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

bool initSDL()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
            else
            {
                //Get window surface
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }

    return success;
}

bool loadPNG()
{
    bool success = true;
    gImageSurface = loadSurface("C:\\Git\\DinosaurEraGame\\Debug\\02_getting_an_image_on_the_screen\\hello.png");
    if (gImageSurface == NULL)
    {
        printf("Failed to load default image!\n");
        success = false;
    }
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("C:\\Git\\DinosaurEraGame\\Debug\\04_key_presses\\press.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        printf("Failed to load default image!\n");
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("C:\\Git\\DinosaurEraGame\\Debug\\04_key_presses\\up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        printf("Failed to load up image!\n");
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("C:\\Git\\DinosaurEraGame\\Debug\\04_key_presses\\down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        printf("Failed to load down image!\n");
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("C:\\Git\\DinosaurEraGame\\Debug\\04_key_presses\\left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        printf("Failed to load left image!\n");
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("C:\\Git\\DinosaurEraGame\\Debug\\04_key_presses\\right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        printf("Failed to load right image!\n");
        success = false;
    }

    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface(gImageSurface);
    gImageSurface = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

void drawTable()
{
    //Start up SDL and create window
    if (!initSDL())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        //Load media
        //if (!loadMedia())
        if (!loadPNG())
        
        {
            printf("Failed to load media!\n");
        }
        else
        {
            //Apply the image
            SDL_BlitSurface(gImageSurface, NULL, gScreenSurface, NULL);
            //Update the surface
            SDL_UpdateWindowSurface(gWindow);

            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Set default current surface
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

            //While application is running
            while (!quit)
            {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    //User presses a key
                    else if (e.type == SDL_KEYDOWN)
                    {
                        //Select surfaces based on key press
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                            break;

                        case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                            break;

                        case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                            break;

                        case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                            break;

                        default:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                }
                //Apply the current image
                SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
            //Hack to get window to stay up
            //SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
        }
    }

    //Free resources and close SDL
    close();
}
