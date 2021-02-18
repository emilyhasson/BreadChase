//
// Created by Emily Hasson on 4/18/2020.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include "movement.h"

namespace myapp {

class Engine {
 public:
  Engine() {}
  void Step();
  void SetDirection(Movement);
  bool Jumping();
  int JumpStep();
  int Longitude();
  void SetShoot(bool set_shoot);
  void SetEnemyShoot(bool set_shoot);
  int ShootStep() {
    return shoot_step;
  }
  bool Shooting() {
    return shooting;
  }
  int EnemyShootStep() {
    return enemy_shoot_step;
  }
  bool EnemyShooting() {
    return enemy_shooting;
  }
  int PlayerHealth() {
    return player_health;
  }
  void PlayerHit();
  void Landed() {
    falling = false;
  }
  void Falling() {
    falling = true;
  }

 private:
//  const int kEnemyShootTime = 25;
  Movement movement;
  bool jumping = false;
  bool falling = false;
  bool shooting = false;
  int longitude = 0;
  int jump_step;
  int shoot_step;
  const int kJumpHeight = 5;
  int player_health = 10;
  bool enemy_shooting = false;
  int enemy_shoot_step;
};
}

#endif  // FINALPROJECT_ENGINE_H
