//
// Created by Emily Hasson on 4/26/2020.
//

#include "mylibrary/enemy.h"
#include <cinder/app/AppBase.h>
#include <cinder/gl/Texture.h>

namespace myapp {

int Enemy::Size() {
  return size;
}

void Enemy::IsHit() {
  health--;
}

bool Enemy::IsKilled() {
  return (health == 0);
}

void Enemy::SetLocation(float x, float y) {
  x_loc = x;
  y_loc = y;
}

float Enemy::X() {
  return x_loc;
}

float Enemy::Y() {
  return y_loc;
}

ci::gl::Texture2dRef Enemy::GetEnemyTexture() {
  auto image = cinder::loadImage( cinder::app::loadAsset( "../assets/enemy.png") );
  ci::gl::Texture2dRef enemy_texture = ci::gl::Texture2d::create(image);
  return enemy_texture;
}

}
