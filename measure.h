#ifndef MEASURE
#define MEASURE

#include "stdio.h"
#include "math.h"
#include "geo.h"
#include "motion.h"
#include "linear.h" 
#include "stdlib.h"

typedef enum{false, true} bool;

vec Measure(float front, float back, float left, float right);
rect* getMap();
vec getMeas(vec x, rect* mp);

#endif
