#include "ball.h"

Ball::Ball() {}
Ball::~Ball() {}

Ball::Ball(int x, int y, int w, int h, int r, int g, int b, int a, float xVel, float yVel) :
  MovingObject(x, y, w, h, r, g, b, a), _xVel(xVel), _yVel(yVel) {}
