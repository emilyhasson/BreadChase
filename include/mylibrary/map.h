//
// Created by Emily on 4/18/2020.
//

#ifndef FINALPROJECT_MAP_H
#define FINALPROJECT_MAP_H

#include "cinder/gl/Texture.h"

class Map {

//  const int kTileSize = 32;

 public:

  Map();
  ~Map();
  void LoadMap(int map_array[20][25]);
  int GetMapArrayValue(int row, int column);
  ci::gl::Texture2dRef GetPlatformTexture();
  ci::gl::Texture2dRef GetGroundTexture();
  ci::gl::Texture2dRef GetSkyTexture();

 private:

  ci::Rectf placement;
  ci::gl::Texture2dRef ground;
  ci::gl::Texture2dRef platform;
  ci::gl::Texture2dRef sky;
  int map[20][25];

};

#endif  // FINALPROJECT_MAP_H
