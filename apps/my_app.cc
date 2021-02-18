// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include "cinder/gl/Texture.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <mylibrary/map.h>

namespace myapp {

using cinder::app::KeyEvent;
ci::gl::Texture2dRef bread_texture;
int map_grid[20][25];
Map map;

MyApp::MyApp() { }

void MyApp::setup() {
  auto bread_image = loadImage( loadAsset( "Bread.png" ) );
  bread_texture = ci::gl::Texture2d::create(bread_image);
}

void MyApp::update() { }

void LoadMap() {
  for (int row = 0; row < 20; row++) {
    for (int col = 0; col < 25; col++) {
      map_grid[row][col] = map.GetMapArrayValue(row, col);
    }
  }
}

void DrawMap() {
  LoadMap();
  float x = 0;
  float y = 0;

  for (int row = 0; row < 20; row++) {

    for (int col = 0; col < 25; col++) {
      ci::Rectf location(x, y, col * kTileSize, row * kTileSize);

      if (map_grid[row][col] == 0) {
        ci::gl::Texture2dRef ground = map.GetGroundTexture();
        ci::gl::draw(ground, location);
      }

      if (map_grid[row][col] == 1) {
        ci::gl::Texture2dRef platform = map.GetPlatformTexture();
        ci::gl::draw(platform, location);
      }

      if (map_grid[row][col] == 2) {
        ci::gl::Texture2dRef sky = map.GetSkyTexture();
        ci::gl::draw(sky, location);
      }
    }
  }
}

ci::gl::Texture2dRef MyApp::CreateTexture(std::string filepath) {
  auto image = loadImage( loadAsset( filepath ) );
  ci::gl::Texture2dRef texture = ci::gl::Texture2d::create(image);
  return texture;
}

void MyApp::draw() {
  ci::Rectf rectangle(100, 150, 200, 250);

  ci::gl::draw(bread_texture, rectangle);

  DrawMap();
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
