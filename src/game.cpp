#include <iostream>
#include <vector>
#include "game.h"

Game::Game(std::size_t wWidth, std::size_t wHeight,
  std::size_t pHeight, std::size_t lThickness, std::size_t gRuntime,
  float ballXVel, float ballYVel) : 
  _windowWidth(wWidth), _windowHeight(wHeight), _lineThickness(lThickness),
  _paddleHeight(pHeight), _gameRuntime(gRuntime)
{
  std::size_t midY = static_cast<int> (wHeight / 2);
  std::size_t paddleY = static_cast<int>(midY - pHeight / 2);

  // Setup player paddle on the left side of the pitch, colour red, static
  _playerPaddle = Paddle(lThickness + distPaddleGoal, paddleY, lThickness, pHeight, 0xCC, 0x00, 0x33, 0xFF, 0);

  // Setup cpu paddle on the right side of the pitch, colour blue, static
  _cpuPaddle = Paddle(wWidth - 2 * lThickness - distPaddleGoal, paddleY, lThickness, pHeight, 0x00, 0x00, 0xCC, 0xFF, 0);

  // Setup ball in the middle of the pitch, colour black, starting to move
  // NICE randomise ball velocity
  _ball = Ball(static_cast<int> (wWidth / 2 - lThickness / 2), static_cast<int> (midY - lThickness / 2),
    lThickness, lThickness, 0x00, 0x00, 0x00, 0xFF, ballXVel, ballYVel);
}

Game::~Game()
{
  std::cout << "Game::~Game\n";
}

void Game::Run(Renderer &renderer, Controller &controller)
{
  bool stopGame = false;
  Uint32 ticksCount = SDL_GetTicks();
  Uint32 gameEnd = ticksCount + _gameRuntime * 1000;

  std::cout << "Game run\n";

  Uint32 frameStart, frameDuration;
  int remaining = _gameRuntime;
  renderer.UpdateWindowTitle(0, 0, remaining);
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), gameEnd) && !stopGame)
  {
    frameStart = SDL_GetTicks();
    _goal = false;
    // std::cout << SDL_GetTicks() << std::endl;
    controller.HandleInput(_playerPaddle);
    stopGame = controller.getStopGame();
    if (stopGame)
    {
      std::cout << "Game stopped by controller" << std::endl;
    }
    updateGame();
    renderer.Render(_playerPaddle, _cpuPaddle, _ball);
    frameDuration = SDL_GetTicks() - frameStart;
    if (frameDuration < _msPerFrame) {
      SDL_Delay(_msPerFrame - frameDuration);
    }
    // wait a bit if someone scored
    if(_goal)
    {
      SDL_Delay(500);
    }
    remaining = static_cast<int>((gameEnd - frameStart) / 1000);
    renderer.UpdateWindowTitle(_scorePlayer, _scoreCpu, remaining);
  };

  SDL_Delay(3000);
  std::cout << "Game::Run ended\n";
};

void Game::updateGame()
{
  // update player position
  movePlayerPaddle();
  // update cpu paddle
  moveCpuPaddle();

  // update ball position
  _ball.SetCoordinates(_ball.GetX() + _ball.GetXVel() * _msPerFrame / 1000, _ball.GetY() + _ball.GetYVel() * _msPerFrame / 1000);

  int xVel = _ball.GetXVel();
  int yVel = _ball.GetYVel();

  // check if the player or cpu paddle collides with the ball,
  // bounce off if yes and increase x velocity of the ball by 7%
  if (playerBounce() || cpuBounce())
  {
    xVel = -1.07f * _ball.GetXVel();
  }
  else if (isPlayerGoal() || isCpuGoal())
  {
    // decrease ball position and velocity
    _ball.SetCoordinates(static_cast<int>(_windowWidth / 2 - _ball.GetW() / 2), static_cast<int> (_windowHeight / 2 - _ball.GetH() / 2));
    xVel = -0.85f * _ball.GetXVel();
    yVel = -0.85f * _ball.GetYVel();
  }
  else if (sideWallBounce())
  {
    xVel = -1.02 * _ball.GetXVel();
    yVel = 1.02 * _ball.GetYVel();
  }
  else if (topBottomWallBounce())
  {
    xVel = 1.02 * _ball.GetXVel();
    yVel = -1.02 * _ball.GetYVel();
  }

  // limit ball velocity, so that there's time for the player and cpu to react
  if (std::abs(_ball.GetXVel()) > _windowWidth)
  {
    xVel = 0.9f * _ball.GetXVel();
  }
  if (std::abs(_ball.GetYVel()) > _windowHeight)
  {
    yVel = 0.9f * _ball.GetYVel();
  }
  _ball.SetVelocity(xVel, yVel);
}

// moves player paddle according to the user input
void Game::movePlayerPaddle()
{
  if (_playerPaddle.GetDirection() != 0)
  {
    // calculate player's new position
    int playerY = _playerPaddle.GetY() + _playerPaddle.GetDirection() * static_cast<int>(_lineThickness / 4);
    // make sure paddle doesn't go out of screen
    if (playerY >= _lineThickness && playerY <= _windowHeight - _lineThickness - _playerPaddle.GetH())
    {
      _playerPaddle.SetCoordinates(_playerPaddle.GetX(), playerY);
    }
    _playerPaddle.ResetDirection();
  }
}

// decides whether to move the cpu paddle and moves it if necessary
void Game::moveCpuPaddle()
{
  // cpu only moves if the ball is in its half moving towards its goal
  if ((_ball.GetX() + _ball.GetW() > _windowWidth / 2) && _ball.GetXVel() > 0) 
  {
    int direction = 0;
    bool moveUp = _cpuPaddle.GetY() + _cpuPaddle.GetH() / 2 > _ball.GetY();
    // make sure the cpu paddle doesn't go out of the field
    if (moveUp && _cpuPaddle.GetY() > 100)
    {
      direction--;
    }
    else if (!moveUp && _cpuPaddle.GetY() + _cpuPaddle.GetH() < 620)
    {
      direction++;
    }
    _cpuPaddle.SetCoordinates(_cpuPaddle.GetX(), _cpuPaddle.GetY() + direction * static_cast<int>(_lineThickness / 4));
  }
}

// calculates if the ball collided with the player paddle
bool Game::playerBounce()
{
  if ((_ball.GetX() - _playerPaddle.GetX() - _playerPaddle.GetW() <= 0) &&
      (_ball.GetY() + _ball.GetH() >= _playerPaddle.GetY()) &&
      (_ball.GetY() <= _playerPaddle.GetY() + _playerPaddle.GetH()) &&
      (_ball.GetXVel() < 0)
      )
  {
    return true;
  }
  return false;
}

// calculates if the ball collided with the cpu paddle
bool Game::cpuBounce()
{
  if ((_cpuPaddle.GetX() -_ball.GetX() - _ball.GetW() <= 0) &&
      (_ball.GetY() + _ball.GetH() >= _cpuPaddle.GetY()) &&
      (_ball.GetY() <= _cpuPaddle.GetY() + _cpuPaddle.GetH()) &&
      (_ball.GetXVel() > 0)
      )
  {
    return true;
  }
  return false;
}

// calculates if player scored a goal and updates player score if that's the case
bool Game::isPlayerGoal()
{
  if (_ball.GetX() + _ball.GetW() >= _windowWidth - _lineThickness && (_ball.GetY() >=180) && (_ball.GetY() + _ball.GetH() <= 540) && _ball.GetXVel() > 0 )
  {
    playerScores();
    _goal = true;
    return true;
  }
  return false;
}

// calculates if cpu scored a goal and updates cpu score if that's the case
bool Game::isCpuGoal()
{
  if (_ball.GetX() <= _lineThickness && (_ball.GetY() >=180) && (_ball.GetY() + _ball.GetH() <= 540) && _ball.GetXVel() < 0)
  {
    cpuScores();
    _goal = true;
    return true;
  }
  return false;
}

bool Game::sideWallBounce()
{
  if ((_ball.GetX() <= _lineThickness && _ball.GetXVel() < 0) ||
      (_ball.GetX() + _ball.GetW() >= _windowWidth - _lineThickness && _ball.GetXVel() > 0)
  )
  {
    return true;
  }
  return false;
}

bool Game::topBottomWallBounce()
{
  if ((_ball.GetY() <= _lineThickness && _ball.GetYVel() < 0) ||
        ((_ball.GetY() + _ball.GetH() >= _windowHeight - _lineThickness) && _ball.GetYVel() > 0))
  {
    return true;
  }
  return false;
}