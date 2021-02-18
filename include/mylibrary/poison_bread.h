//
// Created by Emily Hasson on 5/2/2020.
//

#ifndef FINALPROJECT_POISON_H
#define FINALPROJECT_POISON_H

#include <cinder/gl/Texture.h>

namespace myapp {

const int kDamage = 3;

class Poison {
 public:
  Poison() = default;
  ci::gl::Texture2dRef GetPoisonTexture() {
    auto image = cinder::loadImage(cinder::app::loadAsset(poison_image_path));
    ci::gl::Texture2dRef poison_texture = ci::gl::Texture2d::create(image);
    return poison_texture;
  }
  void IsEaten() {
    is_eaten = true;
    poison_image_path = "../assets/sky2.png";
  }

 private:
  bool is_eaten = false;
  std::string poison_image_path = "../assets/poison_bread.png";

};
}

#endif  // FINALPROJECT_POISON_H
