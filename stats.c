#include "stats.h"


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

