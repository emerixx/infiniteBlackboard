#include "item.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <cstddef>
#include <iostream>

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
  image = NULL;
  pos.w = 100;
  pos.h = 100;
}

item::~item() {
  if (image != NULL) {
    SDL_DestroyTexture(image);
    image = NULL;
  }
}

void item::setRenderer(SDL_Renderer *renderer) { ren = renderer; }

bool item::loadImage(std::string filename) {
  if (image != NULL) {
    SDL_DestroyTexture(image);
    image = NULL;
  }
  SDL_Surface *temp = IMG_Load(filename.c_str());
  if (temp != NULL) {
    image = SDL_CreateTextureFromSurface(ren, temp);
    SDL_FreeSurface(temp);
    if (image != NULL) {

      return true;
    }
  } else {
    return false;
  }

  return 0;
}

void item::draw() {
  if (image != NULL) {
    SDL_RenderCopy(ren, image, NULL, &pos);
  } else if (image == NULL) {
    std::cout << "something is fucked (item.cpp, item::draw())\n";
  }
}
