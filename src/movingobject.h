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

  int GetX() const {return _x;}
  int GetY() const {return _y;}
  int GetW() const {return _w;}
  int GetH() const {return _h;}
  int GetR() const {return _r;}
  int GetG() const {return _g;}
  int GetB() const {return _b;}
  int GetA() const {return _a;}
  
  void SetCoordinates(const int x, const int y)
  {
    _x = static_cast<int>(x);
    _y = static_cast<int>(y);
  }

  void SetDimensions(const int w, const int h)
  {
    _w = static_cast<int>(w);
    _h = static_cast<int>(h);
  }

  void SetColour(const int r, const int g, const int b, const int a)
  {
    _r = r;
    _g = g;
    _b = b;
    _a = a;
  }

  void PrintCoordinates() const
  {
    std::cout << "Object is at: " << _x << ", " << _y << std::endl;
  }
};

#endif