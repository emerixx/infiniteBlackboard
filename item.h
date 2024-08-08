#ifndef ITEMS
#define ITEMS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <string>

void itemInit();
void itemQuit();

class item {
public:
  item();
  virtual ~item();
  void setRenderer(SDL_Renderer *renderer);
  bool loadImage(std::string filename);
  void draw();

private:
  SDL_Renderer *ren;
  SDL_Texture *image;
  SDL_Rect pos;
};

#endif
