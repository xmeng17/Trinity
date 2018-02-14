#ifndef MOTION
#define MOTION

#include "math.h"
#include "linear.h"

#define STD_A 0.5
#define STD_ALPHA 0.3

vec Aug_x(vec x);
mat Aug_P(mat P);
vec State(float px, float py, float v, float theta, float omega);
vec Predict(vec aug_x, double dt);

#endif
