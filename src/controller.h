#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "paddle.h"

class Controller
{
private:
  bool _stopGame = false;

public:
  void HandleInput(Paddle &paddle);

  bool getStopGame() {return _stopGame;}
};

#endif