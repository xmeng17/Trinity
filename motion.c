#include "stdlib.h"
#include "stdio.h"
#include "motion.h"
#include "linear.h"

vec State(float px, float py, float v, float theta, float omega){
  vec x = Vec(5);
  x.value[0] = px;
  x.value[1] = py;
  x.value[2] = v;
  x.value[3] = theta;
  x.value[4] = omega;
  return x;
}

vec Aug_x(vec x){
  vec aug_x = Vec(7);
  aug_x.value[0] = x.value[0];
  aug_x.value[1] = x.value[1];
  aug_x.value[2] = x.value[2];
  aug_x.value[3] = x.value[3];
  aug_x.value[4] = x.value[4];
  aug_x.value[5] = 0;
  aug_x.value[6] = 0;
  return aug_x;
}

mat Aug_P(mat P){
  mat aug_P = Mat(7, 7);
  for (int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++) aug_P.value[i][j] = P.value[i][j];
  }
  for (int i = 0; i < 7; i++){
    for(int j = 5; j < 7; j++) {
      aug_P.value[i][j] = 0.0;
      aug_P.value[j][i] = 0.0;
    }
  }
  aug_P.value[5][5] = STD_A * STD_A;
  aug_P.value[6][6] = STD_ALPHA * STD_ALPHA;
  return aug_P;
}

vec Predict(vec aug_x, double dt){
  float px = aug_x.value[0];
  float py = aug_x.value[1];
  float v = aug_x.value[2];
  float theta = aug_x.value[3];
  float omega = aug_x.value[4];
  float a = aug_x.value[5];
  float alpha = aug_x.value[6];

  vec x= Vec(5);

  //state
  x.value[0] = px;
  x.value[1] = py;
  x.value[2] = v;
  x.value[3] = theta;
  x.value[4] = omega;

  //motion
  if (fabs(omega) > 0.0001) {
    x.value[0] += v * (sin(theta+omega*dt) - sin(theta)) / omega; // px_m = s * (sin(theta_v+omega*dt) - sin(theta_v)) / omega
    x.value[1] += v * (-cos(theta+omega*dt) + cos(theta)) / omega; // py_m = s * (-cos(theta_v+omega*dt) + cos(theta_v)) / omega
  } else {
    x.value[0] += v * cos(theta) * dt; // px_m = s * cos(theta_v) * dt
    x.value[1] += v * sin(theta) * dt; // py_m = s * sin(theta_v) * dt
  }
  x.value[3] += omega * dt; // theta_x_m = omega * dt
  
  //noise 
  x.value[0] += a * cos(theta) * dt*dt/2; // px_n = a * cos(theta_v) * dt2/2
  x.value[1] += a * sin(theta) * dt*dt/2; // py_n = a * sin(theta_v) * dt2/2 
  x.value[2] += a * dt; // s_n = a * dt
  x.value[3] += alpha * dt*dt/2; // theta_v_n = alpha * dt2/2
  x.value[4] += alpha * dt; // omega_n = alpha * dt
  return x;
}
