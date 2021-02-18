// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/map.h>
#include <mylibrary/bread.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>

#include "cinder/gl/Texture.h"
#include "mylibrary/bread.h"
#include "mylibrary/engine.h"
#include "mylibrary/enemy.h"
#include "mylibrary/avatar.h"

namespace myapp {

const int kTileSize = 45;

enum class GameState {
  kPlaying,
  kLose,
  kWin,
};

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void LoadMap(Map map);
  void DrawMap();
  void DrawEnemy();
  void DrawHeart();
  void DrawEnemyHeart();
  void SetAvatarPolygon(b2World world);
  bool IsUnderFoot(float x1, float y1);
  void DrawHealth();
  void MyApp::DrawScore();
  void PrintText(const std::string& text, const cinder::ivec2& size,
                 const cinder::vec2& loc);
  bool BreadEaten(int col);
  void DrawGameOver();
  void CreateB2Box(b2World world, float x, float y, float size);

 private:
  b2Vec2 gravity;
  GameState state_;
  std::vector<int> eaten_breads;
  bool on_platform;
  Enemy enemy;
  Engine engine_;
  Avatar avatar;
  std::chrono::time_point<std::chrono::system_clock> last_time_;
  std::chrono::time_point<std::chrono::system_clock> last_shoot_time_;

  //  const int kSpeed = 50;
  const int kSpeed = 100;
  const int kShootTime = 5;
  float underfoot_x1 = 100;
  float underfoot_x2 = 130;
  float underfoot_y = 18;
  int score = 0;
  const int kBreadPoints = 3;
  const int kPoisonPoints = 5;
  const int kMagicBreadPoints = 10;
  const int kHitEnemyPoints = 2;
  const int kKillEnemyPoints = 5;

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
