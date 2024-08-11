#include "item.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>

int winWidth = 1400;
int winHeight = 1200;
int imgWidthMultiply = 1;
int imgHeightMultiply = 1;
int main() {

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *win = SDL_CreateWindow("Infinite blackboard", 100, 50, winWidth,
                                     winHeight, SDL_WINDOW_SHOWN);
  SDL_Renderer *screen = SDL_CreateRenderer(win, -1, 0);

  item image;
  image.setRenderer(screen);
  image.setSize(imgWidthMultiply * winWidth, imgHeightMultiply * winHeight);
  // test.setPos(-imgWidthMultiply * winWidth / imgWidthMultiply,
  //             -winHeight * imgHeightMultiply / imgHeightMultiply);
  image.setPos(-winWidth * (imgWidthMultiply - 1) / 2,
               -winHeight * (imgHeightMultiply - 1) / 2);
  image.loadImage("./blank.png");
  // image.createBlank(100, 100, 100);
  bool run = true;
  int x, y = 0;
  while (run) {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      switch (ev.type) {
      case SDL_QUIT:
        run = false;
        break;
      case SDL_KEYDOWN:
        switch (ev.key.keysym.sym) {
        case SDLK_UP:
          image.move(0, 10);
          break;
        case SDLK_DOWN:
          image.move(0, -10);
          break;
        case SDLK_LEFT:
          image.move(10, 0);
          break;
        case SDLK_RIGHT:
          image.move(-10, 0);
          break;
        }
      }
    }
    image.draw();
    if (SDL_GetMouseState(&x, &y)) {

      image.drawPixel(x, y);

      std::cout << "x: " << x << " y: " << y << "\n";
    }
    SDL_RenderPresent(screen);
    SDL_RenderClear(screen); // clear screen
  }

  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
