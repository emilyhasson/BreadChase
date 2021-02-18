//
// Created by Emily on 4/18/2020.
//

#include "mylibrary/location.h"

namespace myapp {

Location::Location(int row, int col) {
  row = row;
  col = col;
}

void Location::MoveUp() {
  row--;
}

void Location::MoveDown() {
  row++;
}

void Location::MoveLeft() {
  col++;
}

void Location::MoveRight() {
  col--;
}

int Location::Column() {
  return col;
}

int Location::Row() {
  return row;
}

}
