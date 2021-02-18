//
// Created by Emily Hasson on 4/18/2020.
//

#ifndef FINALPROJECT_BREAD_H
#define FINALPROJECT_BREAD_H

#include <cinder/gl/Texture.h>
namespace myapp {

class Bread {
 public:
  Bread();
  ci::gl::Texture2dRef GetBreadTexture();
  void IsEaten();

 private:
  bool is_eaten = false;
  std::string bread_image_path = "../assets/bread2.png";

};
}
#endif  // FINALPROJECT_BREAD_H
