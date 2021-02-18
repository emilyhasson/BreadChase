//
// Created by Emily on 4/18/2020.
//

#include "mylibrary/map.h"
#include "../apps/my_app.h"
#include "cinder/gl/Texture.h"


int level_one[20][25] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

Map::Map() {
//  MyApp app;
//  ground = app.CreateTexture("ground.png");
//  platform = app.CreateTexture("platform.png");
//  sky = app.CreateTexture("sky.png");
  auto ground_image = cinder::loadImage( cinder::app::loadAsset( "../assets/ground.png" ) );
  ground = ci::gl::Texture2d::create(ground_image);

  auto platform_image = cinder::loadImage( cinder::app::loadAsset( "../assets/platform.png" ) );
  platform = ci::gl::Texture2d::create(platform_image);

  auto sky_image = cinder::loadImage( cinder::app::loadAsset( "../assets/sky.png" ) );
  sky = ci::gl::Texture2d::create(sky_image);

  LoadMap(level_one);
}

void Map::LoadMap(int map_array[20][25]){
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 25; j++) {
      map[i][j] = map_array[i][j];
    }
  }
}

int Map::GetMapArrayValue(int row, int column) {
  int value = map[row][column];
  return value;
}

ci::gl::Texture2dRef Map::GetGroundTexture() {
  return ground;
};

ci::gl::Texture2dRef Map::GetSkyTexture() {
  return sky;
};

ci::gl::Texture2dRef Map::GetPlatformTexture() {
  return platform;
};
