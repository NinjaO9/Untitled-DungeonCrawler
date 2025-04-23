#include <string>
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map> // st

using std::string;

class Cursor {
private:
  int x;
  int y;
public:
  Cursor();
  ~Cursor();
  void update();
};
