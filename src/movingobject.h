#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include <iostream>
#include <string>

class MovingObject
{
protected:
  int _x, _y, // coordinates
      _w, _h, // dimensions
      _r, _g, _b, _a; // colour

public:
  MovingObject();
  ~MovingObject();

  MovingObject(int x, int y, int w, int h, int r, int g, int b, int a);

  int GetX() {return _x;}
  int GetY() {return _y;}
  int GetW() {return _w;}
  int GetH() {return _h;}
  int GetR() {return _r;}
  int GetG() {return _g;}
  int GetB() {return _b;}
  int GetA() {return _a;}
  
  void SetCoordinates(int x, int y)
  {
    _x = static_cast<int>(x);
    _y = static_cast<int>(y);
  }

  void SetDimensions(int w, int h)
  {
    _w = static_cast<int>(w);
    _h = static_cast<int>(h);
  }

  void SetColour(int r, int g, int b, int a)
  {
    _r = r;
    _g = g;
    _b = b;
    _a = a;
  }

  void PrintCoordinates()
  {
    std::cout << "Object is at: " << _x << ", " << _y << std::endl;
  }
};

#endif