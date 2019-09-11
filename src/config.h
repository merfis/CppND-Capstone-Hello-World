#ifndef PONGCONFIG_H
#define PONGCONFIG_H

#include <iostream>
#include <fstream>
#include <string>

class PongConfig
{
private:
  std::size_t _windowWidth;
  std::size_t _windowHeight;
  std::size_t _lineThickness;
  std::size_t _paddleHeight;
  std::size_t _gameRuntime;
  float _ballXVel;
  float _ballYVel;

public:
  PongConfig(const std::string path);

  std::size_t GetWindowWidth() const {return _windowWidth;}
  std::size_t GetWindowHeight() const {return _windowHeight;}
  std::size_t GetLineThickness() const {return _lineThickness;}
  std::size_t GetPaddleHeight() const {return _paddleHeight;}
  std::size_t GetGameRuntime() const {return _gameRuntime;}
  float GetBallXVel() const {return _ballXVel;}
  float GetBallYVel() const {return _ballYVel;}
};

#endif