#include "measure.h"

vec Measure(float front, float back, float left, float right){
  vec m = Vec(4);
  m.value[0] = front; // +x
  m.value[1] = back; // -x
  m.value[2] = left; // +y
  m.value[3] = right; // -y
  return m;
}

point coordTrans(point p, vec x){
  point q;
  float px = x.value[0];
  float py = x.value[1];
  float theta = x.value[3];
  q.x = (p.x - px) * cos(theta) + (p.y - py) * sin(theta);
  q.y = -(p.x - px) * sin(theta) + (p.y - py) * cos(theta);
  return q;
}


bool intersect(float x, float y){
  if ((x > 0.0001 && y < -0.0001) || (x < -0.0001 && y > 0.0001)) return true;
  return false;
}

bool isIn(vec x, rect r){
  float px = x.value[0];
  float py = x.value[1];
  return (px > r.diag[0].x && px < r.diag[1].x && py > r.diag[0].y && py < r.diag[1].y);
}

bool small(float x){
  return (x >= 0 && x < 0.0001);
}

void updateMeasure(vec m, int index, float value){
  switch (index % 8){
    case 0:
      m.value[0] = value;
      break;
    case 2:
      m.value[3] = value;
      break;
    case 4:
      m.value[1] = value;
      break;
    case 6:
      m.value[2] = value;
      break;
    default:
      updateMeasure(m, index - 1, value);
      updateMeasure(m, index + 1, value);
  };
}

void isOn(vec x, rect r, vec m){
  float px = x.value[0];
  float py = x.value[1];
  float theta = x.value[3];
  int index;
  float rotation = theta *2 / M_PI;
  if (rotation == 0.0) index = 0;
  else if (rotation == 1.0) index = 2;
  else if (rotation == 2.0) index = 4;
  else if (rotation == 3.0) index = 6;
  else rotation = (int) floor(rotation) * 2 + 1;
  float left = r.diag[0].x - px;
  float right = px - r.diag[1].x;
  float down = r.diag[0].y - py;
  float up = py - r.diag[1].y;
  
  if (small(left)) updateMeasure(m, index, 0);
  if (small(right)) updateMeasure(m, index + 4, 0);
  if (small(down)) updateMeasure(m, index + 6, 0);
  if (small(up)) updateMeasure(m, index + 2, 0);
}

rect* getMap(){
  rect* mp;
  mp = (rect*) malloc(14*sizeof(rect));
  mp[0] = Rect(0,0,0,244);
  mp[1] = Rect(244,244,0,244);
  mp[2] = Rect(72,74,46,105);
  mp[3] = Rect(72,74,155,244);
  mp[4] = Rect(120,122,46,97);
  mp[5] = Rect(120,122,143,198);
  mp[6] = Rect(196,198,143,198);
  mp[7] = Rect(120,146,196,198);
  mp[8] = Rect(46,74,151,153);
  mp[9] = Rect(120,198,143,145);
  mp[10] = Rect(0,74,103,105);
  mp[11] = Rect(120,198,95,97);
  mp[12] = Rect(0,244,0,0);
  mp[13] = Rect(0,244,244,244);
  return mp;
}

vec getMeas(vec x, rect* mp){
  vec m = Measure(512,512,512,512);
  for (int i = 0; i < 14; i++){
    if (isIn(x, mp[i])) return Measure(0,0,0,0);
    isOn(x,mp[i],m);
    for (int j = 0; j < 2; j++){
      for(int k = 0; k < 2; k++){
        point a = coordTrans(mp[i].diag[j], x);
        point b = coordTrans(mp[i].anti_diag[k], x);
        if (intersect(a.x,b.x)){
          float intersept = (a.x * b.y - a.y * b.x) / (a.x - b.x);
          if (intersept > 0.0001 && intersept < m.value[2]) m.value[2] = intersept; // left
          if (intersept < -0.0001 && -intersept < m.value[3]) m.value[3] = -intersept; // right
        }
        if (intersect(a.y,b.y)){
          float intersept = (a.y * b.x - a.x * b.y) / (a.y - b.y);
          if (intersept > 0.0001 && intersept < m.value[0]) m.value[0] = intersept; // front
          if (intersept < -0.0001 && -intersept < m.value[1]) m.value[1] = -intersept; // back
        }
      }
    }
  }
  return m;
}


