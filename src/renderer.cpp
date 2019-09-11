#include "renderer.h"

Renderer::Renderer(const std::size_t width, const std::size_t height,
  const std::size_t pHeight, const std::size_t thickness) : 
  _windowWidth(static_cast<int>(width)),
  _windowHeight(static_cast<int>(height)),
  _paddleHeight(static_cast<int>(pHeight)),
  _lineThickness(static_cast<int>(thickness)),
  _sdlInitialised(true)
{
  int sdlResult = SDL_Init(SDL_INIT_VIDEO);
  if (sdlResult != 0)
  {
    std::cerr << "Unable to initialize SDL:" << SDL_GetError() << std::endl;
    _sdlInitialised = false;
  }

  _sdlWindow = SDL_CreateWindow("CppND-Capstone Project Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (!_sdlWindow)
  {
    std::cerr << "Unable to create window:" << SDL_GetError() << std::endl;
    _sdlInitialised = false;
  }

  _sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!_sdlRenderer)
  {
    std::cerr << "Unable to create renderer:" << SDL_GetError() << std::endl;
    _sdlInitialised = false;
  }
}

Renderer::~Renderer()
{
  SDL_DestroyWindow(_sdlWindow);
  SDL_Quit();
}

void Renderer::Render(const Paddle playerPaddle, const Paddle cpuPaddle, const Ball ball)
{
  // Set draw color to green for the pitch
  SDL_SetRenderDrawColor(_sdlRenderer, 0x19, 0xA2, 0x23, 0xFF);

  // Clear back buffer
  SDL_RenderClear(_sdlRenderer);

  // Draw grey walls
  SDL_SetRenderDrawColor(_sdlRenderer, 0x9E, 0x9E, 0x9E, 0xFF);

  // Draw top wall
  SDL_Rect wall{0, 0, _windowWidth, _lineThickness};
  SDL_RenderFillRect(_sdlRenderer, &wall);

  // Draw bottom wall
  wall.y = _windowHeight - _lineThickness;
  SDL_RenderFillRect(_sdlRenderer, &wall);

  // Draw left goal
  wall.y = 0;
  wall.w = _lineThickness;
  wall.h = 180;
  SDL_RenderFillRect(_sdlRenderer, &wall);

  wall.y = 540;
  SDL_RenderFillRect(_sdlRenderer, &wall);

  // Draw right goal
  wall.x = _windowWidth - _lineThickness;
  wall.y = 0;
  SDL_RenderFillRect(_sdlRenderer, &wall);

  wall.y = 540;
  SDL_RenderFillRect(_sdlRenderer, &wall);

  // Draw white middle line
  SDL_SetRenderDrawColor(_sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  wall.x = static_cast<int>(_windowWidth / 2 - _lineThickness / 2);
  wall.y = _lineThickness;
  wall.h = _windowHeight - 2 * _lineThickness;
  SDL_RenderFillRect(_sdlRenderer, &wall);

  // Draw ball
  SDL_SetRenderDrawColor(_sdlRenderer, ball.GetR(), ball.GetG(), ball.GetB(), ball.GetA());
  SDL_Rect b{
      static_cast<int>(ball.GetX()),
      static_cast<int>(ball.GetY()),
      ball.GetW(),
      ball.GetH()};
  SDL_RenderFillRect(_sdlRenderer, &b);

  // Draw player paddle
  SDL_SetRenderDrawColor(_sdlRenderer, playerPaddle.GetR(), playerPaddle.GetG(), playerPaddle.GetB(), playerPaddle.GetA());
  SDL_Rect player{
      static_cast<int>(playerPaddle.GetX()),
      static_cast<int>(playerPaddle.GetY()),
      playerPaddle.GetW(),
      static_cast<int>(playerPaddle.GetH())};
  SDL_RenderFillRect(_sdlRenderer, &player);

  // Draw CPU paddle
  SDL_SetRenderDrawColor(_sdlRenderer, cpuPaddle.GetR(), cpuPaddle.GetG(), cpuPaddle.GetB(), cpuPaddle.GetA());
  SDL_Rect cpu{
      static_cast<int>(cpuPaddle.GetX()),
      static_cast<int>(cpuPaddle.GetY()),
      cpuPaddle.GetW(),
      static_cast<int>(cpuPaddle.GetH())};
  SDL_RenderFillRect(_sdlRenderer, &cpu);

  // Swap front buffer and back buffer
  SDL_RenderPresent(_sdlRenderer);
}

void Renderer::UpdateWindowTitle(const int playerScore, const int cpuScore, const int remaining)
{
  std::string title{"Player: " + std::to_string(playerScore) + " CPU: " + std::to_string(cpuScore) + " Remaining: " + std::to_string(remaining)};
  SDL_SetWindowTitle(_sdlWindow, title.c_str());
}