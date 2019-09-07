#ifndef BALL_H
#define BALL_H

#include "movingobject.h"

class Ball : public MovingObject
{
private:
  float _xVel, _yVel; // horizontal and vertical velocity of the ball

public:
  Ball();
  Ball(int x, int y, int w, int h, int r, int g, int b, int a, float xVel, float yVel);
  ~Ball();

  float GetXVel() {return _xVel;}
  float GetYVel() {return _yVel;}

  void SetVelocity(float xVel, float yVel)
  {
    _xVel = xVel;
    _yVel = yVel;
  }

  void PrintVelocity()
  {
    std::cout << "Ball velocity: " << _xVel << ", " << _yVel << std::endl;
  }
  
};

#endif