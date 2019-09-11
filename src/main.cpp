#include <iostream>
#include "config.h"
#include "game.h"
#include "renderer.h"

int main()
{
  PongConfig pConf("pong.conf");

  Renderer renderer(pConf.GetWindowWidth(), pConf.GetWindowHeight(), pConf.GetPaddleHeight(), pConf.GetLineThickness());
  if (!renderer.WasInitialised())
  {
    std::cerr << "Renderer was not initialised" << std::endl;
    return 1;
  }
  Controller controller;

  Game game(pConf.GetWindowWidth(), pConf.GetWindowHeight(), pConf.GetPaddleHeight(), pConf.GetLineThickness(), pConf.GetGameRuntime(), pConf.GetBallXVel(), pConf.GetBallYVel());
  game.Run(renderer, controller);

  std::cout << "Final score Player - CPU: " << game.GetScorePlayer() << " - " << game.GetScoreCpu() << std::endl;
  
  return 0;
}