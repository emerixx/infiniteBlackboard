#include "item.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>

int winWidth = 800;
int winHeight = 600;
int imgWidthMultiply = 4;
int imgHeightMultiply = 4;
int main() {

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *win = SDL_CreateWindow("Infinite blackboard", 30, 30, winWidth,
                                     winHeight, SDL_WINDOW_SHOWN);
  SDL_Renderer *screen = SDL_CreateRenderer(win, -1, 0);

  item test;
  test.setRenderer(screen);
  test.setSize(imgWidthMultiply * winWidth, imgHeightMultiply * winHeight);
  // test.setPos(-imgWidthMultiply * winWidth / imgWidthMultiply,
  //             -winHeight * imgHeightMultiply / imgHeightMultiply);
  test.setPos(-winWidth * (imgWidthMultiply - 1) / 2,
              -winHeight * (imgHeightMultiply - 1) / 2);
  test.loadImage("test.png");

  bool run = true;

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
          test.move(0, 10);
          break;
        case SDLK_DOWN:
          test.move(0, -10);
          break;
        case SDLK_LEFT:
          test.move(10, 0);
          break;
        case SDLK_RIGHT:
          test.move(-10, 0);
          break;
        }
      }
    }
    test.draw();
    SDL_RenderPresent(screen);
    SDL_RenderClear(screen); // clear screen
  }

  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
