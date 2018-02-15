#include "ukf.h"

vec Weights(){
  vec weights = Vec(2*AUG_DIM + 1);
  weights.value[0] = (float)LAMBDA / (float)(LAMBDA + AUG_DIM);
  for (int i = 1; i < 2*AUG_DIM+1; i++) weights.value[i] = 0.5 / (float)(LAMBDA + AUG_DIM);
  return weights;
}

mat GenerateAugSigmaT(vec x, mat P){
  mat aug_sigma_T = ZeroMat(2*AUG_DIM+1, AUG_DIM);

  vec aug_x = Aug_x(x);
  mat aug_P = Aug_P(P);
  mat L_T = LLTUpper(aug_P);

  aug_sigma_T.value[0] = aug_x.value;
  float sca = sqrt(LAMBDA+AUG_DIM);

  for (int i = 0; i < AUG_DIM; i++){
    vec row = Vec(7);
    row.value = L_T.value[i];
    aug_sigma_T.value[i+1] = AddVec(aug_x, ScaleVec(row,sca)).value;
    aug_sigma_T.value[i+1+AUG_DIM] = SubVec(aug_x, ScaleVec(row,sca)).value;
  }
  return aug_sigma_T;
}

mat PredictSigmaXT(mat aug_sigma_T, float dt){
  mat sigma_x_T = Mat(2*AUG_DIM+1,X_DIM);
  for (int i = 0; i < 2*AUG_DIM+1; i++){
    vec aug_x = Vec(AUG_DIM);
    aug_x.value = aug_sigma_T.value[i];
    sigma_x_T.value[i] = Predict(aug_x,dt).value;
  }
  return sigma_x_T;
}

mat CalculateSigmaZT(mat sigma_x_T, rect* mp){
  mat sigma_z_T = Mat(2*AUG_DIM+1,Z_DIM);
  for (int i = 0; i < 2*AUG_DIM+1; i++){
    vec x = Vec(X_DIM);
    x.value = sigma_x_T.value[i];
    sigma_z_T.value[i] = getMeas(x, mp).value;
  }
  return sigma_z_T;
}

mat Prediction(vec* x, mat* P, float dt, vec weights){
  mat aug_sigma_T = GenerateAugSigmaT(*x,*P);
  mat sigma_x_T = PredictSigmaXT(aug_sigma_T,dt);
  *x = WeighedMean(sigma_x_T,weights);
  *P = WeighedCovVec(sigma_x_T,*x,weights);  
  return sigma_x_T;
}

void Correction(vec* x, mat* P, vec z, mat sigma_x_T, rect* mp, vec weights){
  mat sigma_z_T = CalculateSigmaZT(sigma_x_T, mp);
  vec z_pred = WeighedMean(sigma_z_T, weights);

  mat S = WeighedCovVec(sigma_z_T, z_pred, weights);
  mat S_I = Inverse(S);
  mat T = WeighedCovMat(sigma_x_T, *x, sigma_z_T, z_pred, weights);
  mat K = MultiplyMat(T, S_I);
  vec y = SubVec(z, z_pred);
  *x = AddVec(*x, MultiplyVM(K, y));
  *P = SubMat(*P, MultiplyMat(K, MultiplyMat(S, Transpose(K))));
}

/*

void UKF::Init(){
  x_ = sensor->GetInitState(meas_.z);
  P_ = sensor->GetInitCovariance();
  prev_meas_ = meas_;
  is_initialized = true;
}



double UKF::Fuse(Measurement meas){
  meas_ = meas;

  if (meas_.sensortype == Sensor::RADAR && use_radar_) sensor = new Radar();
  else if (meas_.sensortype == Sensor::LIDAR && use_lidar_) sensor = new Lidar();
  else {
    if (! meas_.sensortype == Sensor::RADAR && ! meas_.sensortype == Sensor::LIDAR) cout << "Unrecognized Sensor"<<endl;
    return 0.0;
  }

  if(!is_initialized){
	Init();
    return 0.0;
  }

  dt_ = (meas_.t - prev_meas_.t) / 1000000.0;
  Prediction();
  double nis = Correction();
  prev_meas_ = meas_;

  return nis;
}

}*/
