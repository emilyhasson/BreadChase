// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/map.h>

#include "cinder/gl/Texture.h"



namespace myapp {

const int kTileSize = 32;

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void LoadMap();
  void DrawMap();
  ci::gl::Texture2dRef CreateTexture(std::string filepath);
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
