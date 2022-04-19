#include "game.h"
#include "SDL.h"
#include "bombs.h"
#include <iostream>

Game::Game(std::size_t grid_width, std::size_t grid_height, GameMenu &gm)
    : snake(grid_width, grid_height), _gm(gm), _player(gm.GetPlayerName()),
      engine(dev()), random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  _bombs = std::shared_ptr<Bombs>(new Bombs());
  PlaceFood();
  PlaceBombs();
}

Game::~Game() {
  _player.saveScore();
  _gm.DisplayPlayerScore(_player.name(), GetScore(), GetSize());
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, _bombs);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(frame_count, _player);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive)
    return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if meet a bomb
  if (_bombs->BombCell(Coordinate(new_x, new_y)))
  {
    snake.alive = false;
    return;
  }

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    _player.incrementScore();
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

void Game::PlaceBombs()
{
  int x, y;
  while (true)
  {
    /// Return if we meet the size requiremens.
    if (_numOfBombs == _bombs->count())
    {
      return;
    }

    /// Randomly generate the x and y coordinate.
    x = random_w(engine);
    y = random_h(engine);

    // Check that the location is not occupied by a (snake item + food item) before placing
    // an obstacle.
    auto foodExistsAtThisCell = food.x == x && food.y == y;
    if (!snake.SnakeCell(x, y) && !foodExistsAtThisCell)
    {
      _bombs->addCoordinate(Coordinate(x, y));
    }
  }
}


int Game::GetScore() const { return _player.score(); }
int Game::GetSize() const { return snake.size; }