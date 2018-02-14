#ifndef STATS
#define STATS

#include "linear.h"
#include "stdio.h"


vec WeighedMean(mat sigma, vec weights);
mat WeighedCovVec(mat sigma, vec mean, vec weights);
mat WeighedCovMat(mat x_sigma, vec x_mean, mat z_sigma, vec z_mean, vec weights);

#endif
