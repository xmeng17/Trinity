#ifndef STATS
#define STATS

#include "linear.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "math.h"

vec WeighedMean(mat sigma, vec weights);
mat WeighedCovVec(mat sigma, vec mean, vec weights);
mat WeighedCovMat(mat x_sigma, vec x_mean, mat z_sigma, vec z_mean, vec weights);
float RandomReal(float r);
float RandomNormal(float mean, float std);
int RandomDiscrete(float* norm_weights, int num);
void Normalize(float* weights, int num);

#endif
