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
mat GenerateAugSigmaT(vec x, mat P);
mat PredictSigmaXT(mat aug_sigma_T, float dt);
mat CalculateSigmaZT(mat sigma_x_T,rect* mp);

mat Prediction(vec* x, mat* P, float dt, vec weights);
void Correction(vec* x, mat* P, vec z, mat sigma_x_T, rect* mp, vec weights);

#endif
