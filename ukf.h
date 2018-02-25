#ifndef UKF
#define UKF

#include "linear.h"
#include "motion.h"
#include "measure.h"
#include "geo.h"
#include "stats.h"

#define X_DIM 5
#define AUG_DIM 7
#define Z_DIM 4
#define LAMBDA -2

vec Weights();

mat Prediction(vec* x, mat* P, float dt, vec weights);
void Correction(vec* x, mat* P, vec z, mat sigma_x_T, rect* mp, vec weights);
void Update(vec* x, mat* P, vec z, float dt, rect* mp, vec weights);

#endif
