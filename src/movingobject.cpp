#include "movingobject.h"

MovingObject::MovingObject() {}
MovingObject::~MovingObject() {}

MovingObject::MovingObject(int x, int y, int w, int h, int r, int g, int b, int a) :
  _x(x), _y(y), _w(w), _h(h), _r(r), _g(g), _b(b), _a(a)
{

}