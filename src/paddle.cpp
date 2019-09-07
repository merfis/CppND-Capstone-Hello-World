#include "paddle.h"

Paddle::Paddle() {}
Paddle::~Paddle() {}

Paddle::Paddle(int x, int y, int w, int h, int r, int g, int b, int a, int d) :
  MovingObject(x, y, w, h, r, g, b, a), _direction(d) {}