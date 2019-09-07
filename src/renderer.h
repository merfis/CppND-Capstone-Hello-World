#ifndef RENDERER_H
#define RENDERER_H
#include "SDL.h"
#include "movingobject.h"
#include "paddle.h"
#include "ball.h"

class Renderer
{
public:
  Renderer(const std::size_t windowWidth, const std::size_t windowHeight,
    const std::size_t paddleHeight, const std::size_t lineThickness);
  ~Renderer();

  void Render(const Paddle playerPaddle, const Paddle cpuPaddle, const Ball ball);
  void UpdateWindowTitle(const int playerScore, const int cpuScore, const int remaining);
  bool WasInitialised() {return _sdlInitialised;}

private:
  SDL_Window *_sdlWindow;
  SDL_Renderer *_sdlRenderer;

  const int _windowWidth;
  const int _windowHeight;
  const int _paddleHeight;
  const int _lineThickness;

  bool _sdlInitialised;
};

#endif