#ifndef LINEAR
#define LINEAR

typedef struct{
  float* value;
  int size;
} vec;

typedef struct{
  float** value;
  int row;
  int col;
} mat;

vec Vec(int size);
mat Mat(int row, int col);

void DeVec(vec v);
void DeMat(mat m);

vec ZeroVec(int size);
mat ZeroMat(int row, int col);

vec Col(mat m, int ind);

vec ScaleVec(vec v, float k);
mat ScaleMat(mat m, float k);

vec AddVec(vec u, vec v);
mat AddMat(mat m, mat n);

vec SubVec(vec u, vec v);
mat SubMat(mat m, mat n);

float Dot(vec u, vec v);
vec Ele(vec u, vec v);

vec MultiplyVM(mat m, vec u);
mat MultiplyMat(mat m, mat n);


mat LLTLower(mat m);
mat LLTUpper(mat m);

mat Inverse(mat m);
mat InverseLower(mat m);
mat InverseUpper(mat m);

mat Transpose(mat m);

void shapeVec(vec v);
void shapeMat(mat m);
void showVec(vec v);
void showMat(mat m);

#endif
