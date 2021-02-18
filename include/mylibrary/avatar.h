//
// Created by Emily on 4/18/2020.
//

#ifndef FINALPROJECT_AVATAR_H
#define FINALPROJECT_AVATAR_H

namespace myapp {
class Avatar {
 public:
  Avatar() {}
  float XCoord();
  float YCoord();
  float Size();
 private:
  const float location_x = 250;
  const float location_y = 375;
  const float size = 285;
};
}
#endif  // FINALPROJECT_AVATAR_H
