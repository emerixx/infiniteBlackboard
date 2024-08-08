#include "item.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>

void itemInit() {
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void itemQuit() {
  SDL_Quit();
  IMG_Quit();
}

item::item() {
  pos.x = 0;
  pos.y = 0;
  image = SDL_CreateRGBSurface(0, 600, 400, 16, 0, 0, 0, 0);
  pos.w = image->clip_rect.w;
  pos.h = image->clip_rect.h;
  SDL_FillRect(image, NULL, 0xffff00);
}

item::~item() {
  if (image != NULL) {
    SDL_FreeSurface(image);
  }
}

bool item::loadImage(std::string filename) {
  if (image != NULL) {
    SDL_FreeSurface(image);
  }
  image = IMG_Load(filename.c_str());
  if (image != NULL) {
    return true;
  } else {
    return false;
  }

  return 0;
}

void item::draw(SDL_Surface *dest) {
  if (image != NULL) {
    SDL_BlitSurface(image, NULL, dest, &pos);
  }
}
