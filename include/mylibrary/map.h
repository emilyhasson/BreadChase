//
// Created by Emily on 4/18/2020.
//

#ifndef FINALPROJECT_MAP_H
#define FINALPROJECT_MAP_H

#include "cinder/gl/Texture.h"
const int kTileSize = 32;
static const int kNumRows = 23;
static const int kNumColumns = 50;
const int kGround = 0;
const int kPlatform = 1;
const int kSky = 2;
const int kBread = 3;
const int kEnemy = 4;
const int kCloud = 5;
const int kPoison = 6;
const int kMagic = 7;

namespace myapp {

class Map {

 public:
  Map();
  Map(std::vector<std::string> map_file);
  void LoadMap(int map_array[kNumRows][kNumColumns]);
  int GetMapArrayValue(int row, int column);
  ci::gl::Texture2dRef GetPlatformTexture();
  ci::gl::Texture2dRef GetGroundTexture();
  ci::gl::Texture2dRef GetSkyTexture();
  ci::gl::Texture2dRef GetCloudTexture();


 private:
  ci::Rectf placement;
  ci::gl::Texture2dRef ground;
  ci::gl::Texture2dRef platform;
  ci::gl::Texture2dRef sky;
  ci::gl::Texture2dRef cloud;
  int map[kNumRows][kNumColumns];
};
}
#endif  // FINALPROJECT_MAP_H
