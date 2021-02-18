//
// Created by Emily on 4/18/2020.
//

#include "mylibrary/engine.h"
#include "mylibrary/movement.h"
#include "mylibrary/avatar.h"

#include <mylibrary/map.h>
#include <mylibrary/avatar.h>

namespace myapp {


void Engine::Step() {
    Avatar avatar;
    int x_dist = avatar.XCoord();
    int size = avatar.Size();

  if (movement == Movement::kRight) {

    if (longitude < kNumColumns - ((x_dist + size) / kTileSize) - 2 ) {
      longitude++;
    }
    movement = Movement::kIdle;
  }

  if (movement == Movement::kLeft) {

    if (longitude > 0) {
      longitude--;
    }
    movement = Movement::kIdle;
  }

  if (movement == Movement::kJump) {
    jumping = true;
    jump_step = 0;
    movement = Movement::kIdle;
  }

  if (jumping) {

    if (jump_step < kJumpHeight) {
      jump_step++;

    } else {
      jumping = false;
      falling = true;
    }
  }

  if (falling) {
    jump_step--;
//    if (jump_step > 0) {
//      jump_step--;
//
//    } else {
//      falling = false;
//    }
  }

  if (shooting) {
    shoot_step++;
  }

  if (enemy_shooting && enemy_shoot_step < 37) {
    enemy_shoot_step++;
  }

  if (enemy_shoot_step >= 37) {
    SetEnemyShoot(false);
  }

}

void Engine::SetShoot(bool set_shoot) {
  shooting = set_shoot;
  shoot_step = 0;
}

void Engine::SetDirection(const Movement set_movement) {
  movement = set_movement;
}

bool Engine::Jumping() {
  return (jumping || falling);
}

int Engine::JumpStep() {
  return jump_step;
}

int Engine::Longitude() {
  return longitude;
}

void Engine::PlayerHit() {
  player_health--;
}

void Engine::SetEnemyShoot(bool set_shoot) {
  enemy_shooting = set_shoot;
  enemy_shoot_step = 0;
}

}
