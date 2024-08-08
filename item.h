#ifndef ITEMS
#define ITEMS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <string>

void itemInit();
void itemQuit();

class item {
public:
  item();
  virtual ~item();
  bool loadImage(std::string filename);
  void draw(SDL_Surface *dest);

private:
  SDL_Surface *image;
  SDL_Rect pos;
};

#endif
