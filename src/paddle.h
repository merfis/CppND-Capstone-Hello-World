#ifndef PADDLE_H
#define PADDLE_H

#include "movingobject.h"

class Paddle : public MovingObject
{
private:
  int _direction; // paddle direction - up or down from current position
                  // based on controller input

public:
  Paddle();
  Paddle(int x, int y, int w, int h, int r, int g, int b, int a, int d);
  ~Paddle();

  int GetDirection() const {return _direction;}
  void ResetDirection() {_direction = 0;}
  void UpdateDirection(const int d) {_direction += d;}
};

#endif