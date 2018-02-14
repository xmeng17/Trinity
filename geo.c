#include "geo.h"

point Point(float x, float y){
  point p;
  p.x = x;
  p.y = y;
  return p;
}

rect Rect(float x_d, float x_u, float y_d, float y_u){
  rect r;
  r.diag[0] = Point(x_d,y_d);
  r.diag[1] = Point(x_u,y_u);
  r.anti_diag[0] = Point(x_d,y_u);
  r.anti_diag[1] = Point(x_u,y_d);
  return r;
}
