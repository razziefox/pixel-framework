#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//function to load images using sdl_image
SDL_Surface *load_image(char const *path, SDL_Renderer *renderer) {

    //loads image onto a surface
    SDL_Surface *surface = IMG_Load(path);

    //converts the surface into a texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    //unloads surface from earlier
    SDL_FreeSurface(surface);

    //returns back the texture given
    return texture;

}