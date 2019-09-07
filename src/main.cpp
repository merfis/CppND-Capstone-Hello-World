#include <iostream>
#include <thread>
#include "game.h"
#include "renderer.h"

int main()
{
  // NICE: load parameters from a config file
  constexpr std::size_t windowWidth{960};
  constexpr std::size_t windowHeight{720};
  constexpr std::size_t lineThickness{16};
  constexpr std::size_t paddleHeight{96};
  constexpr std::size_t gameRuntime{90};

  Renderer renderer(windowWidth, windowHeight, paddleHeight, lineThickness);
  if (!renderer.WasInitialised())
  {
    std::cerr << "Renderer was not initialised" << std::endl;
    return 1;
  }
  Controller controller;

  Game game(windowWidth, windowHeight, lineThickness, paddleHeight, gameRuntime);
  game.Run(renderer, controller);

  std::cout << "Final score Player - CPU: " << game.GetScorePlayer() << " - " << game.GetScoreCpu() << std::endl;
  
  return 0;
}