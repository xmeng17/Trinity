#include "stdio.h"
#include "ukf.h"
#include "linear.h"
#include "measure.h"
#include "geo.h"
#include "stats.h"


int main(int argc, char **argv){

  vec x = State(30,14,2,1.57,0.5); 
  mat P = ZeroMat(5,5);
  for (int i = 0 ; i < 5; i++) P.value[i][i] = 1.0;
  vec z = Measure(89.1,13.9,30.1,214.5);
 
  rect* mp = getMap();
  vec weights = Weights();
  mat sigma_x_T = Prediction(&x,&P,0.1, weights);
  Correction(&x,&P,z,sigma_x_T,mp,weights);
  
  showVec(x);
  printf("\n");
  showMat(P);
  
  free(mp);
  DeMat(P);
  DeMat(sigma_x_T);
 

  return 0;
}


