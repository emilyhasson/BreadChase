//
// Created by Emily on 4/26/2020.
//

#ifndef FINALPROJECT_ENEMY_H
#define FINALPROJECT_ENEMY_H

#include <cinder/gl/Texture.h>

namespace myapp {

class Enemy {
 public:
  Enemy() {}
  int Size();
  void IsHit();
  bool IsKilled();
  void SetLocation(float x, float y);
  float X();
  float Y();
  ci::gl::Texture2dRef Enemy::GetEnemyTexture();
 private:
  float x_loc;
  float y_loc;
  const int size = 225;
  bool killed = false;
  int health = 3;
};

}

#endif  // FINALPROJECT_ENEMY_H
