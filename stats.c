#include "stats.h"
#include "stdio.h"


vec WeighedMean(mat sigma_T, vec weights){
  if (weights.size != sigma_T.row) printf("Error calculating Mean\n");
  else {
    vec x = ZeroVec(sigma_T.col);
    for (int i = 0; i < sigma_T.row; i++) {
      vec v = Vec(sigma_T.col);
      v.value = sigma_T.value[i];
      x = AddVec(x, ScaleVec(v,weights.value[i]));
    }
    return x;
  }
}

mat WeighedCovVec(mat sigma_T, vec mean, vec weights){
  if (weights.size != sigma_T.row) printf("Error Calculating Covariance\n");
  else {
    mat P = ZeroMat(sigma_T.col, sigma_T.col);
    for (int i = 0; i < sigma_T.row; i++){
      vec v = Vec(sigma_T.col);
      v.value = sigma_T.value[i];
      mat dx = Mat(1,sigma_T.col);
      dx.value[0] = SubVec(v, mean).value; 
      P = AddMat(P, ScaleMat(MultiplyMat(Transpose(dx),dx),weights.value[i]));
    }
    return P;
  }
}

mat WeighedCovMat(mat x_sigma_T, vec x_mean, mat z_sigma_T, vec z_mean, vec weights){
  if (weights.size != x_sigma_T.row) printf("Error Calculating Intercovariance");
  else{
    mat T = ZeroMat(x_sigma_T.col, z_sigma_T.col);
    for (int i = 0; i < weights.size; i++){
      vec v = Vec(x_sigma_T.col);
      v.value = x_sigma_T.value[i];
      vec w = Vec(z_sigma_T.col);
      w.value = z_sigma_T.value[i];
      mat dx = Mat(1,x_sigma_T.col);
      mat dz = Mat(1,z_sigma_T.col);
      dx.value[0] = SubVec(v, x_mean).value;
      dz.value[0] = SubVec(w, z_mean).value;
      T = AddMat(T, ScaleMat(MultiplyMat(Transpose(dx),dz),weights.value[i]));
  }
  return T;
  }
}

float RandomReal(float r){
  return r * (float)rand() / (float) RAND_MAX;
}

float RandomNormal(float mean, float std){
  float rand0 = RandomReal(1);
  float rand1 = RandomReal(1);
  return mean + std * sqrt(-2 * log(rand0)) * cos(2 * M_PI * rand1);
}

int RandomDiscrete(float* norm_weights, int num){
  float* acc_weights = (float*) malloc((num+1)*sizeof(float));
  acc_weights[0] = 0; 
  for (int i = 1; i <= num; i++){
    acc_weights[i] = acc_weights[i-1] + norm_weights[i-1];
  }

  acc_weights[num] = 1;
  float rand0 = RandomReal(1); 
  int begin = 0;
  int end = num;
  int pos = num / 2;
  while (1){
    if (pos >= num || pos < 0) return -1;
    if (acc_weights[pos] <= rand0){
      if (acc_weights[pos+1] > rand0) return pos;
      else begin = pos + 1;
    } else end = pos - 1;
    pos = (end + begin)/2;
  }
}

void Normalize(float* weights, int num){
  float sum = 0;
  for (int i = 0; i < num; i++) sum += weights[i];
  for (int i = 0; i < num; i++) weights[i] /= sum;
}

