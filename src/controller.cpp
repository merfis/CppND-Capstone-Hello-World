#include "SDL.h"
#include "controller.h"

void Controller::HandleInput(Paddle &paddle)
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      _stopGame = true;
      break;
    }
  }

  // Get state of the keyboard
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  // If escape key is pressed also end loop
  if (state[SDL_SCANCODE_ESCAPE])
  {
    _stopGame = true;
  }

  // Update paddle direction based on W/S or up/down keys
  if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
  {
    paddle.UpdateDirection(-1);
  }
  if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
  {
    paddle.UpdateDirection(1);
  }
  
};