#ifndef GEO
#define GEO

typedef struct{
  float x;
  float y;
} point;

typedef struct{
  point diag[2]; //left bottom to right top
  point anti_diag[2]; //left top to right bottom
} rect;

point Point(float x, float y);
rect Rect(float x_d, float x_u, float y_d, float y_u);


#endif
