#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "game.c"
#include "main.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
    
//initializes window information
struct game_window {

    int width;
    int height;
    int scale;

};

//sets variables for window
width = 256;
height = 144;
scale = 4;

//sets debug_mode to true
bool debug_mode = true;

//sets isFullscreen to false
bool isFullscreen = false;


int main(int argc, char **argv) {

    //sets game windows based off variables
    struct game_window game_window = {width=256, height=144, scale=4};
    
    //starts up sdl2 and checks if it has any errors
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {

        //displays error message and quits
        printf("Error with starting SDL2!! More details: %s", SDL_GetError());
        return 1;

    }
    
    //starts up sdl_image
    IMG_Init(IMG_INIT_PNG);

    //sets flags for window
    Uint32 flags = SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE;

    //create window and set it to a variable
    SDL_Window *window = SDL_CreateWindow("pixel framework", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game_window.width*game_window.scale, game_window.height*game_window.scale, flags);

    //checks if window variable is null
    if (window == NULL) {

        //displays error message and quits
        printf("Error with creating window!! More details: %s", SDL_GetError());
        return 1;

    }

    //creates the main renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    

    //checks if renderer variable is null
    if (renderer == NULL) {

        //displays error message then quits
        printf("Error with creating the renderer!! More details: %s", SDL_GetError());

    }

    //sets renderer resolution (this is important for locking a aspect ratio!)
    SDL_RenderSetLogicalSize(renderer, game_window.width, game_window.height);

    //sets background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    /*

    /// we don't want to use the icon yet

    //sets window icon
    SDL_Surface *window_icon = IMG_Load("assets/icon.png");
    SDL_SetWindowIcon(window, window_icon);
    SDL_FreeSurface(window_icon);

    */

    //sets running variable to true
    bool running = true;
    SDL_Event event;

    //starts load variable from game.c
    load(renderer, window);

    //game loop
    while(running) {

        //update function for game.c
        update();

        //keyboard input
        while(SDL_PollEvent(&event)) {

            //if the event type is SDL_QUIT, then quit game
            if(event.type == SDL_QUIT) {
                running = false;
            }

            if(event.type == SDL_KEYDOWN) {
                const char *key = SDL_GetKeyName(event.key.keysym.sym);

                //if 'escape' is pressed, then quit game
                if (strcmp(key, "Escape") == 0) {

                    running = false;

                }

                //if f4 or f11 is pressed, then toggle fullscreen
                if (strcmp(key, "F4") == 0 || strcmp(key, "F11") == 0) {

                    //toggles between fullscreen
                    SDL_SetWindowFullscreen(window, !isFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP:0);
                    isFullscreen = !isFullscreen;

                }

            }

        }

        //clears out the screen
        SDL_RenderClear(renderer);

        //draws renderer
        draw(renderer);

        //show whats currently being drawn to renderer
        SDL_RenderPresent(renderer);
    }

    //destroys renderer
    SDL_DestroyRenderer(renderer);

    //starts any code within the destroy function in game.c
    destroy();
    
    //destroys window
    SDL_DestroyWindow(window);
    
    //quits out of sdl2_image
    IMG_Quit();

    //quits out of sdl2
    SDL_Quit();

    return 0;
}

