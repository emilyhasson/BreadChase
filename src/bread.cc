//
// Created by Emily Hasson on 4/18/2020.
//

#include "mylibrary/bread.h"

#include <cinder/app/AppBase.h>
#include <cinder/gl/Texture.h>

namespace myapp {

Bread::Bread() {}

ci::gl::Texture2dRef Bread::GetBreadTexture() {
  auto image = cinder::loadImage( cinder::app::loadAsset( bread_image_path ) );
  ci::gl::Texture2dRef bread_texture = ci::gl::Texture2d::create(image);
  return bread_texture;
}

void Bread::IsEaten() {
  is_eaten = true;
  bread_image_path = "../assets/sky2.png";
}

}
