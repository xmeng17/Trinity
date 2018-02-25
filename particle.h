#ifndef PARTICLE
#define PARTICLE

#include "stdlib.h"
#include "math.h"
#include "measure.h"
#include "geo.h"
#include "stats.h"
#include "stdio.h"

#define NUM_P 200
#define STD_X 1
#define STD_Y 1
#define STD_THETA 0.1

typedef struct{
  float x;
  float y;
  float theta;
  float weight;
} particle;

particle* Particle();

void ParticlePred(particle* p, float dt, float v, float omega);
float* UpdateWeights(particle* p, vec z, rect* mp);
particle* Resample(particle* p, float* weights);
vec getPos(particle* p, float v, float omega);
particle* Localize(particle* p, vec z, float dt, float v, float omega, rect* mp);

void showP(particle* p);

#endif

