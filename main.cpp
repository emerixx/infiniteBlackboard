#include "item.h"
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <iostream>

int main() {

  std::cout << "Hello world";
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *win = SDL_CreateWindow("Infinite blackboard", 30, 30, 1200, 700,
                                     SDL_WINDOW_SHOWN);
  SDL_Renderer *screen = SDL_CreateRenderer(win, -1, 0);

  item test;
  test.setRenderer(screen);
  test.loadImage("boykisser.jpg");

  bool run = true;
  while (run) {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      switch (ev.type) {
      case SDL_QUIT:
        run = false;
        break;
      }
    }
    test.draw();
    SDL_RenderPresent(screen);
  }

  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
