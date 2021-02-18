// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <mylibrary/map.h>
#include <cinder/Font.h>
#include <cinder/Text.h>

#include <chrono>
#include <fstream>

#include "cinder/gl/Texture.h"
#include "mylibrary/avatar.h"
#include "mylibrary/bread.h"
#include "mylibrary/poison_bread.h"
#include "mylibrary/magic_bread.h"
#include "mylibrary/enemy.h"
#include "mylibrary/engine.h"
#include "mylibrary/movement.h"

using cinder::Color;
using cinder::ColorA;
using cinder::TextBox;
using cinder::app::KeyEvent;
using myapp::Map;
using myapp::Enemy;
using cinder::app::KeyEvent;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;


namespace myapp {

using cinder::app::KeyEvent;
ci::gl::Texture2dRef bread_texture;
ci::gl::Texture2dRef magic_texture;
ci::gl::Texture2dRef poison_texture;
ci::gl::Texture2dRef heart_texture;
ci::gl::Texture2dRef avatar_texture;
ci::gl::Texture2dRef enemy_heart_texture;
int map_grid[kNumRows][kNumColumns];
std::vector<std::string> map_vector;
bool on_platform;
const int kStartHeight = 5;
int starting_height = 5;
const char kNormalFont[] = "Arial";
int jump_step = 0;

MyApp::MyApp() {
}

void MyApp::setup() {
  state_ = GameState::kPlaying;
  engine_.SetDirection(Movement::kIdle);
  auto image = loadImage(loadAsset("../assets/avatar.png"));
  avatar_texture = ci::gl::Texture2d::create(image);

  auto heart_image = loadImage(loadAsset("../assets/heart.png"));
  heart_texture = ci::gl::Texture2d::create(heart_image);

  auto enemy_heart_image = loadImage(loadAsset("../assets/enemy_heart.png"));
  enemy_heart_texture = ci::gl::Texture2d::create(enemy_heart_image);

  std::ifstream map_file{"../assets/level1_map"};
  std::string str;

  while (std::getline(map_file, str)) {
    map_vector.push_back(str);
  }
  b2Vec2 set_gravity(0.0f, -10.0f);
  gravity = set_gravity;
  b2World world(gravity);
  SetAvatarPolygon(world);
}

void MyApp::update() {
  if (state_ == GameState::kPlaying) {
    const auto time = system_clock::now();
    if (time - last_time_ > std::chrono::milliseconds(kSpeed)) {
      engine_.Step();
      last_time_ = time;
      if (time - last_shoot_time_ > std::chrono::seconds(kShootTime)) {
        engine_.SetEnemyShoot(true);
        last_shoot_time_ = time;
      }
    }
    if (!enemy.IsKilled() && avatar.XCoord() >= enemy.X()) {
      engine_.PlayerHit();
    }
    if (engine_.PlayerHealth() < 1) {
      state_ = GameState::kLose;
    }
    if (enemy.IsKilled() && magic_bread_eaten) {
      state_ = GameState::kWin;
    }
  }
}

void MyApp::LoadMap(Map map) {
  for (int row = 0; row < kNumRows; row++) {
    for (int col = 0; col < kNumColumns; col++) {
      map_grid[row][col] = map.GetMapArrayValue(row, col);
    }
  }
}

void MyApp::DrawGameOver() {
  std::string result_string;
  if (state_ == GameState::kLose) {
    result_string = "You lose :( Score: ";
  }
  if (state_ == GameState::kWin) {
    result_string = "You win :) Score: ";
  }
  result_string += std::to_string(score);
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  int health = engine_.PlayerHealth();
  ci::Rectf location(100.0f, 100.0f, 700.0f, 700.0f);
  ci::gl::draw(heart_texture, location);
  PrintText(result_string, size, center);
}

bool MyApp::IsUnderFoot(float x1, float y1) {
  return ((x1 / kTileSize == underfoot_x1 || x1 / kTileSize == underfoot_x2)
    && (y1 / kTileSize == underfoot_y));
}

void MyApp::CreateB2Box(b2World world, float x, float y, float size) {
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(avatar.XCoord(), avatar.YCoord());
  b2Body* groundBody = world.CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(avatar.Size() / 2, avatar.Size() / 2);
  groundBody->CreateFixture(&groundBox, 0.0f);
}

void MyApp::DrawMap() {
  Map map;
  b2World world(gravity);
  LoadMap(map);
  int longitude = engine_.Longitude();

  if (engine_.Jumping()) {
    jump_step = engine_.JumpStep();
  }
  starting_height = kStartHeight - jump_step;

  ci::Rectf bread_location;
  int row_count = 0;
  int col_count = 0;

  for (int row = starting_height; row < kNumRows; row++) {
    row_count++;
    col_count = 0;

    for (int col = longitude; col < kNumColumns; col++) {
      col_count++;

      if (row_count == 14 && col_count == 9) {
        if (map_grid[row][col] == kPlatform) {
          engine_.Landed();
        }
        if (map_grid[row][col] == kSky && !(engine_.Jumping())) {
          engine_.Falling();
        }
      }

      float x1 = (col - longitude) * kTileSize;
      float y1 = (row - starting_height) * kTileSize;
      float x2 = x1 + kTileSize;
      float y2 = y1 + kTileSize;
      ci::Rectf location(x1, y1, x2, y2);

      if (map_grid[row][col] == kGround) {
        ci::gl::Texture2dRef ground = map.GetGroundTexture();
        ci::gl::draw(ground, location);
      }

      if (map_grid[row][col] == kPlatform) {
        ci::gl::Texture2dRef platform = map.GetPlatformTexture();
        ci::gl::draw(platform, location);
        if (IsUnderFoot(x1, y1)) {
          CreateB2Box(world, x1, y1, kTileSize);
        }
      }

      if (map_grid[row][col] == kSky) {
        ci::gl::Texture2dRef sky = map.GetSkyTexture();
        ci::gl::draw(sky, location);
      }

      if (map_grid[row][col] == kCloud) {
        ci::gl::Texture2dRef cloud = map.GetCloudTexture();
        ci::gl::draw(cloud, location);
      }

      if (map_grid[row][col] == kBread) {
        Bread bread;

        if (((col - longitude) < ((avatar.XCoord() + avatar.Size()) / kTileSize) - 1)
        || (BreadEaten(col))) {

          bread.IsEaten();

          if (!(BreadEaten(col))) {
            eaten_breads.push_back(col);
            score += kBreadPoints;
          }
        }
        bread_texture = bread.GetBreadTexture();
        ci::gl::draw(bread_texture, location);
      }

      if (map_grid[row][col] == kPoison) {
        Poison poison;
        if (((col - longitude) < ((avatar.XCoord() + avatar.Size()) / kTileSize) - 1)
            || (BreadEaten(col))) {

          poison.IsEaten();

          if (!(BreadEaten(col))) {
            eaten_breads.push_back(col);
            score -= kPoisonPoints;

            for (int i = 0; i < kDamage; i++) {
              engine_.PlayerHit();
            }

          }
        }
        ci::gl::Texture2dRef sky = map.GetSkyTexture();
        ci::gl::draw(sky, location);

        poison_texture = poison.GetPoisonTexture();
        ci::gl::draw(poison_texture, location);
      }

      if (map_grid[row][col] == kMagic) {
        Magic magic;
        if (((col - longitude) < ((avatar.XCoord() + avatar.Size()) / kTileSize) - 3)
            || (BreadEaten(col))) {

          magic.IsEaten();

          if (!(BreadEaten(col))) {
            eaten_breads.push_back(col);
            score += kMagicBreadPoints;
          }
        }
        ci::gl::Texture2dRef sky = map.GetSkyTexture();
        ci::gl::draw(sky, location);

        magic_texture = magic.GetMagicTexture();
        ci::gl::draw(magic_texture, location);
      }

      if (map_grid[row][col] == kEnemy) {
        enemy.SetLocation(x2, y2);
        ci::gl::Texture2dRef sky = map.GetSkyTexture();
        ci::gl::draw(sky, location);
      }
    }
  }
}

bool MyApp::BreadEaten(int col) {
  for (int i = 0; i < eaten_breads.size(); i++) {
    if (eaten_breads.at(i) == col) {
      return true;
    }
  }
  return false;
}

void MyApp::PrintText(const std::string& text, const cinder::ivec2& size,
               const cinder::vec2& loc) {

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 30))
      .size(size)
      .color(Color(1, 1, 1))
//      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawHealth() {
  const cinder::vec2 text_location {100, 30};
  const cinder::ivec2 size = {500, 50};
  int health = engine_.PlayerHealth();
  std::string health_string = "Health: ";
  health_string += std::to_string(health);
  PrintText(health_string, size, text_location);
}

void MyApp::DrawScore() {
  const cinder::vec2 text_location {100, 80};
  const cinder::ivec2 size = {500, 50};
  std::string score_string = "Score: ";
  score_string += std::to_string(score);
  PrintText(score_string, size, text_location);
}

void MyApp::DrawEnemy() {
  if (!(enemy.IsKilled())) {
    float x2 = enemy.X();
    float y2 = enemy.Y();
    float x1 = (x2 - enemy.Size());
    float y1 = (y2 - enemy.Size());
    ci::Rectf location(x1, y1, x2, y2);
    ci::gl::Texture2dRef enemy_texture = enemy.GetEnemyTexture();
    ci::gl::draw(enemy_texture, location);
  }
}

void MyApp::draw() {
  if (state_ == GameState::kWin || state_ == GameState::kLose) {
    DrawGameOver();
    return;
  }
  DrawMap();
  DrawEnemy();
  DrawHeart();
  DrawEnemyHeart();

  ci::Rectf avatar_location(avatar.XCoord(), avatar.YCoord(),
      avatar.XCoord() + avatar.Size(),
      avatar.YCoord() + avatar.Size());

  ci::gl::draw(avatar_texture, avatar_location);

  DrawHealth();
  DrawScore();
}

void MyApp::SetAvatarPolygon(b2World world) {
  CreateB2Box(world, avatar.XCoord(), avatar.YCoord(), (avatar.Size() / 2));
}

void MyApp::DrawEnemyHeart() {
  if (engine_.EnemyShooting() && !enemy.IsKilled()) {
    float heart_size = 75;
    float x1 = enemy.X() - (engine_.EnemyShootStep() * kTileSize);
    float y1 = enemy.Y() - (enemy.Size() / 2);
    float x2 = x1 + heart_size;
    float y2 = y1 + heart_size;
    ci::Rectf location(x1, y1, x2, y2);
    ci::gl::draw(enemy_heart_texture, location);

    if ((x1 <= (avatar.XCoord() + avatar.Size())) && (x1 >= avatar.XCoord())
      && (y1 <= (avatar.YCoord() + (avatar.Size() / 2)))) {
        engine_.SetEnemyShoot(false);
        engine_.PlayerHit();
        score --;
    }
  }
}

void MyApp::DrawHeart() {
  if (engine_.Shooting()) {
    float heart_size = 75;
    float x1 = avatar.XCoord() + (engine_.ShootStep() * kTileSize);
    float y1 = avatar.YCoord() + (avatar.Size() / 4);
    float x2 = x1 + heart_size;
    float y2 = y1 + heart_size;
    ci::Rectf location(x1, y1, x2, y2);
    ci::gl::draw(heart_texture, location);
    if (x2 >= (enemy.X() - (enemy.Size() / 2))) {
      engine_.SetShoot(false);
      enemy.IsHit();

      if (enemy.IsKilled()) {
        score += kKillEnemyPoints;
      } else {
        score += kHitEnemyPoints;
      }
    }
  }
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_RIGHT: {
      engine_.SetDirection(Movement::kRight);
      break;
    }
    case KeyEvent::KEY_LEFT: {
      engine_.SetDirection(Movement::kLeft);
      break;
    }
    case KeyEvent::KEY_SPACE: {
      if (!(engine_.Jumping())) {
        engine_.SetDirection(Movement::kJump);
      }
      break;
    }
    case KeyEvent::KEY_f: {
      if ((!enemy.IsKilled()) && (!engine_.Shooting())) {
        engine_.SetShoot(true);
      }
      break;
    }
  }
}

}  // namespace myapp
