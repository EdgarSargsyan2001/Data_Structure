#ifndef POINT_H
#define POINT_H

class Point {

public:
  Point(int a = -1, int b = -1);
  int get_X();
  int get_Y();

private:
  int x;
  int y;
};


#endif