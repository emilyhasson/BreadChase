//
// Created by Emily on 4/18/2020.
//

#ifndef FINALPROJECT_LOCATION_H
#define FINALPROJECT_LOCATION_H

namespace myapp {

class Location {
 public:
  Location() {}
  Location(int row, int col);
  int Column();
  int Row();
  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

 private:
  int row;
  int col;
};
}

#endif  // FINALPROJECT_LOCATION_H
