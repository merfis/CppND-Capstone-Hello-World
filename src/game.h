#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include "movingobject.h"
#include "paddle.h"
#include "ball.h"
#include "renderer.h"
#include "controller.h"

// distance between the paddle and goal line
const int distPaddleGoal = 10;

// Game class
class Game
{
private:
  // moving objects: two players and a ball
  Paddle _playerPaddle;
  Paddle _cpuPaddle;
  Ball _ball;

  std::size_t _windowWidth, _windowHeight, _lineThickness, _paddleHeight, _gameRuntime;

  int _msPerFrame = 16;

  int _scorePlayer = 0;
  int _scoreCpu = 0;
  bool _goal = false;

  void updateGame();
  void movePlayerPaddle();
  void moveCpuPaddle();
  void playerScores() {_scorePlayer++;}
  void cpuScores() {_scoreCpu++;}
  bool playerBounce();
  bool cpuBounce();
  bool sideWallBounce();
  bool topBottomWallBounce();
  bool isPlayerGoal();
  bool isCpuGoal();


public:
  Game(std::size_t windowWidth, std::size_t windowHeight, std::size_t paddleHeight, std::size_t lineThickness, std::size_t gameRuntime, float ballXVel, float ballYVel);
  ~Game();

  int GetScorePlayer() {return _scorePlayer;}
  int GetScoreCpu() {return _scoreCpu;}


  void Run(Renderer &renderer, Controller &controller);

};
#endif