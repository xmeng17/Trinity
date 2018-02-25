#include "particle.h"

particle* Particle(){
  particle* p = (particle*) malloc(NUM_P*sizeof(particle));
  for (int i = 0; i < NUM_P; i++){
    p[i].x = RandomReal(244);
    p[i].y = RandomReal(244);
    p[i].theta = RandomReal(2 * M_PI);
    p[i].weight = 1.0 / NUM_P;
  }
  return p;
}

void ParticlePred(particle* p, float dt, float v, float omega){
  for (int i = 0; i < NUM_P; i++){
    float theta = p[i].theta;

    //motion
    if (fabs(omega) > 0.0001){
      p[i].x += v * (sin(theta+omega*dt) - sin(theta)) / omega; // px_m = s * (sin(theta_v+omega*dt) - sin(theta_v)) / omega
      p[i].y += v * (-cos(theta+omega*dt) + cos(theta)) / omega; // py_m = s * (-cos(theta_v+omega*dt) + cos(theta_v)) / omega
    } else {
      p[i].x += v * cos(theta) * dt; // px_m = s * cos(theta_v) * dt
      p[i].y += v * sin(theta) * dt; // py_m = s * sin(theta_v) * dt
    }
    p[i].theta += omega * dt;
    //noise
    p[i].x += RandomNormal(0,STD_X);
    p[i].y += RandomNormal(0,STD_Y);
    p[i].theta += RandomNormal(0,STD_THETA);

    //normalize
    if (p[i].x > 244) p[i].x = 243.9;
    if (p[i].y > 244) p[i].y = 243.9;
    if (p[i].x < 0) p[i].x = 0.1;
    if (p[i].y < 0) p[i].y = 0.1;
    while (p[i].theta > M_PI) p[i].theta -= 2 * M_PI;
    while (p[i].theta < -M_PI) p[i].theta += 2 * M_PI;
  }
}

float* UpdateWeights(particle* p, vec z, rect* mp){
  float* weights = (float*) malloc(NUM_P*sizeof(float));
  float coeff0 = 1 / (float) (2 * STD_MEAS * STD_MEAS);
  float coeff1 = M_PI * coeff0;
  for (int i = 0 ; i < NUM_P; i++){
    vec pred_z = getMeas(State(p[i].x,p[i].y,0,p[i].theta,0),mp);
    float exponential = 0;
    for (int j = 0; j < 4; j++) {
      float dsensor = pred_z.value[j] - z.value[j];
      exponential -= dsensor * dsensor;
    }
    exponential /= 100;
    weights[i] = coeff1 * exp(exponential * coeff0);

  }
  Normalize(weights, NUM_P);
  for (int i = 0; i < NUM_P; i++) p[i].weight = weights[i];
  return weights;
}

particle* Resample(particle* p, float* weights){
  particle* p_n = (particle*) malloc(NUM_P*sizeof(particle));
  for (int i = 0; i < NUM_P; i++) {
    int ind = RandomDiscrete(weights,NUM_P);
    p_n[i].x = p[ind].x;
    p_n[i].y = p[ind].y;
    p_n[i].theta = p[ind].theta;
    p_n[i].weight = p[ind].weight; 
  }
  return p_n;
}

vec getPos(particle* p,float v,float omega){
  int ind = -1;
  int max_w = 0;
  for (int i = 0; i < NUM_P; i++) if (p[i].weight > max_w) ind = i;
  return State(p[ind].x,p[ind].y,v,p[ind].theta,omega);
}

particle* Localize(particle* p, vec z, float dt, float v, float omega, rect* mp){
  ParticlePred(p,dt,v,omega);
  float* w = UpdateWeights(p,z,mp);
  return Resample(p,w);
}

void showP(particle* p){
  int** vis = (int**) malloc(122*sizeof(int*));
  for (int i = 0; i < 122; i++) vis[i] = (int*) calloc(122,sizeof(int));
  for (int i = 0; i < NUM_P; i++) vis[(int)(p[i].x / 2)][(int)(p[i].y / 2)] = 1;
  for (int i = 0; i < 122; i++){
    for (int j = 0; j < 122; j++){
      if (vis[i][j] == 1) printf("*");
      else printf(".");
    }
    printf("\n");
  }
  for (int i = 0; i < 10; i++) printf("\n");
}
