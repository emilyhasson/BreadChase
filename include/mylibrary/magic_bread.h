//
// Created by Emily on 5/2/2020.
//

#ifndef FINALPROJECT_MAGIC_BREAD_H
#define FINALPROJECT_MAGIC_BREAD_H

#include <cinder/gl/Texture.h>

namespace myapp {

bool magic_bread_eaten = false;

class Magic {
 public:
  Magic() = default;
  ci::gl::Texture2dRef GetMagicTexture() {
    auto image = cinder::loadImage(cinder::app::loadAsset(magic_image_path));
    ci::gl::Texture2dRef magic_texture = ci::gl::Texture2d::create(image);
    return magic_texture;
  }
  void IsEaten() {
    is_eaten = true;
    magic_bread_eaten = true;
    magic_image_path = "../assets/sky2.png";
  }

 private:
  bool is_eaten = false;
  std::string magic_image_path = "../assets/magic_bread.png";

};
}

#endif  // FINALPROJECT_MAGIC_BREAD_H
