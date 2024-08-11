#include "item.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
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
  pos.x = 50;
  pos.y = 50;
  image = NULL;
  pos.w = 100;
  pos.h = 100;
}

void item::createBlank(int r, int b, int g) {
  SDL_Surface *surf =
      SDL_CreateRGBSurface(r, g, b, 32, pos.x, pos.y, pos.w, pos.h);
  image = SDL_CreateTextureFromSurface(ren, surf);
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

void item::setSize(int w, int h) {
  pos.w = w;
  pos.h = h;
}
void item::setPos(int x, int y) {
  pos.x = x;
  pos.y = y;
}
void item::move(int x, int y) {
  pos.x += x;
  pos.y += y;
}
void item::draw(double angle) {
  if (image != NULL) {
    SDL_Point pt;
    pt.x = pos.w / 2 + pos.x;
    pt.y = pos.h / 2 + pos.y;
    SDL_RenderCopyEx(ren, image, NULL, &pos, angle, &pt, SDL_FLIP_NONE);
  } else if (image == NULL) {
    std::cout << "something is fucked (item.cpp, item::draw(double angle))\n";
  }
}
void item::drawPixel(int x, int y) {
  SDL_Rect rect;
  rect.x = x + pos.x;
  rect.y = y + pos.y;
  rect.w = 1;
  rect.h = 1;

  SDL_RenderCopy(ren, image, NULL, &rect);
}
void item::draw() {
  if (image != NULL) {

    SDL_RenderCopy(ren, image, NULL, &pos);
  } else if (image == NULL) {
    std::cout << "something is fucked (item.cpp, item::draw())\n";
  }
}
