#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "player.h"
#include "bombs.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, 
              SDL_Point const &food,
              const std::shared_ptr<Bombs> bombs);
  void UpdateWindowTitle(int fps, Player &player);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  // Bomb surface
  SDL_Surface *bombSurface;
  // Bomb Texture
  SDL_Texture *bombTexture;

  void placeBombs(const std::shared_ptr<Bombs> bombs) const;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif