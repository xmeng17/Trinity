#include "stdlib.h"
#include "stdio.h"
#include "ukf.h"
#include "linear.h"
#include "measure.h"
#include "geo.h"
#include "stats.h"
#include "time.h"
#include "particle.h"

int main(int argc, char **argv){

  srand(time(0));
  rect* mp = getMap();
  particle* p = Particle();


showP(p);
for(int i = 0; i < 30; i++){
  vec x = State(172.91,196.00,0,M_PI*i/30,M_PI/3); 
  vec z = getMeas(x,mp);
//  showVec(z);
  p = Localize(p,z,0.1,0,M_PI/3,mp);
  vec v = getPos(p,0,M_PI/3);
  showVec(v);
}
showP(p);
  free(mp);
free(p); 
  return 0;
}


