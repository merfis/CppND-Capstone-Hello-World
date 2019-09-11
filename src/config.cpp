#include "config.h"

PongConfig::PongConfig(const std::string path)
{
  std::string wWidth = "windowWidth=";
  std::string wHeight = "windowHeight=";
  std::string lThickness = "lineThickness=";
  std::string pHeight = "paddleHeight=";
  std::string gRuntime = "gameRuntime=";
  std::string bXVell = "ballXVell=";
  std::string bYVell = "ballYVell=";
  
  std::ifstream stream(path);
  if (!stream)
  {
      throw std::runtime_error("Pong config file not found");
  }
  std::string line;
  while (std::getline(stream, line))
  {
    if (line.compare(0, wWidth.size(), wWidth) == 0)
    {
      _windowWidth = static_cast<std::size_t>(std::stoi(line.substr(line.find("=") + 1)));
      continue;
    }
    if (line.compare(0, wHeight.size(), wHeight) == 0)
    {
      _windowHeight = static_cast<std::size_t>(std::stoi(line.substr(line.find("=") + 1)));
      continue;
    }
    if (line.compare(0, lThickness.size(), lThickness) == 0)
    {
      _lineThickness = static_cast<std::size_t>(std::stoi(line.substr(line.find("=") + 1)));
      continue;
    }
    if (line.compare(0, pHeight.size(), pHeight) == 0)
    {
      _paddleHeight = static_cast<std::size_t>(std::stoi(line.substr(line.find("=") + 1)));
      continue;
    }
    if (line.compare(0, gRuntime.size(), gRuntime) == 0)
    {
      _gameRuntime = static_cast<std::size_t>(std::stoi(line.substr(line.find("=") + 1)));
      continue;
    }
    if (line.compare(0, bXVell.size(), bXVell) == 0)
    {
      _ballXVel = std::stof(line.substr(line.find("=") + 1));
      continue;
    }
    if (line.compare(0, bYVell.size(), bYVell) == 0)
    {
      _ballYVel = std::stof(line.substr(line.find("=") + 1));
      continue;
    }
  }
}
