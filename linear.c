#include "stdlib.h"
#include "math.h"
#include "linear.h"
#include "stdio.h"

vec Vec(int size){
  vec v;
  v.value = (float*) malloc(size * sizeof(float));
  v.size = size;
  return v;
}

mat Mat(int row, int col){
  mat m;
  m.value = (float**) malloc(row * sizeof(float*));
  for (int i = 0; i < row; i++) m.value[i] = (float*) malloc(col * sizeof(float));
  m.row = row;
  m.col = col;
  return m;
}

void DeVec(vec v){
  free(v.value);
}

void DeMat(mat m){
  for (int i = 0; i < m.row; i++) free(m.value[i]);
  free(m.value);
}

vec ZeroVec(int size){
  vec v;
  v.value = (float*) calloc(size, sizeof(float));
  v.size = size;
  return v;
}

mat ZeroMat(int row, int col){
  mat m; 
  m.value = (float**)malloc(row * sizeof(float*));
  for (int i = 0; i < row; i++) m.value[i] = (float*) calloc(col, sizeof(float));
 
  m.row = row;
  m.col = col;
  return m;
}

vec Col(mat m, int ind){
  vec v = Vec(m.row);
  for (int i = 0; i < m.col; i++) v.value[i] = m.value[i][ind];
  return v;
}

vec ScaleVec(vec v, float k){
  vec ret = Vec(v.size);
  for (int i = 0; i < v.size; i++) ret.value[i] = k * v.value[i];
  return ret;
}

mat ScaleMat(mat m, float k){
  mat ret = Mat(m.row, m.col);
  for (int i = 0; i < m.row; i++) {
    for (int j = 0; j < m.col; j++){
      ret.value[i][j] = k * m.value[i][j];
    }
  }
  return ret;
}

vec AddVec(vec u, vec v){
  if (u.size == v.size){
    vec ret = Vec(u.size);
    for (int i = 0; i < u.size; i++) ret.value[i] = u.value[i] + v.value[i];
    return ret;
  } else printf("Error adding vectors, vec1.size = %d, vec2.size = %d\n",u.size, v.size);
}

mat AddMat(mat m, mat n){
  if (m.row == n.row && m.col == n.col){
    mat ret = Mat(m.row, m.col);
    for (int i = 0; i < m.row; i++){
      for (int j = 0; j < m.col; j++) ret.value[i][j] = m.value[i][j] + n.value[i][j];
    }
    return ret;
  } else printf("Error adding matrixes, mat1.shape = %d*%d, mat2.shape = %d*%d\n", m.row,m.col,n.row,n.col);
}

vec SubVec(vec u, vec v){
  if (u.size == v.size){
    vec ret = Vec(u.size);
    for (int i = 0; i < u.size; i++) ret.value[i] = u.value[i] - v.value[i];
    return ret;
  } else printf("Error subtracting vectors, vec1.size = %d, vec2.size = %d\n", u.size, v.size);

}

mat SubMat(mat m, mat n){
  if (m.row == n.row && m.col == n.col){
    mat ret = Mat(m.row, m.col);
    for (int i = 0; i < m.row; i++){
      for (int j = 0; j < m.col; j++) ret.value[i][j] = m.value[i][j] - n.value[i][j];
    }
    return ret;
  } else printf("Error subtracting matrixes, mat1.shape = %d*%d, mat2.shape = %d*%d\n", m.row, m.col, n.row, n.col);

}

float Dot(vec u, vec v){
  if (u.size == v.size){
    float ret = 0;
    for (int i = 0; i < u.size; i++) ret += u.value[i] + v.value[i];
    return ret;
  } else printf("Error calculating dot products, vec1.size = %d, vec2.size = %d\n", u.size, v.size);
}

vec Ele(vec u, vec v){
  if (u.size == v.size){
    vec ret = Vec(u.size);
    for (int i = 0; i < u.size; i++) ret.value[i] = u.value[i] * v.value[i];
    return ret;
  } else printf("Error calculating elementwise multiplication, vec1.size = %d, vec2.size = %d\n", u.size, v.size);
}

vec MultiplyVM(mat m, vec u){
  if (m.col == u.size){
    vec ret = Vec(m.row);
    //ret[i] = m[i][].u[]
    for (int i = 0; i < m.row; i++){
      ret.value[i] = 0.0;
      for (int j = 0; j < m.col; j++) ret.value[i] += m.value[i][j] * u.value[j];
    }
    return ret;
  } else printf("Error multiplying matrix and vector, mat.shape = %d*%d, vec.size = %d\n", m.row, m.col, u.size);
}

mat MultiplyMat(mat m, mat n){
  if (m.col == n.row){
    mat ret = Mat(m.row,n.col);
    //ret[i][j] = m[i][].n[][j]
    for (int i = 0; i < m.row; i++){
      for (int j = 0; j < n.col; j++){
        ret.value[i][j] = 0.0;
        for (int k = 0; k < m.col; k++) ret.value[i][j] += m.value[i][k] * n.value[k][j];
      }
    }
    return ret;
  } else printf("Error multiplying matrixes, mat1.shape = %d*%d, mat2.shape = %d*%d\n", m.row, m.col, n.row, n.col);
}

mat LLTLower(mat m){
  if (m.row == m.col){ 
    mat ret = ZeroMat(m.row,m.col);
    for (int i = 0; i < m.row; i++){
      for (int j = 0; j < i+1; j++){
        double s = 0;
        for (int k = 0; k < j; k++) s += ret.value[i][k] * ret.value[j][k];
        ret.value[i][j] = (i == j) ? sqrt(m.value[i][i] - s) : ((m.value[i][j] - s) / ret.value[j][j]);
      }
    }
    return ret;
  } else printf("Error calculating LLT, mat.shape = %d*%d\n",m.row,m.col);
}

mat LLTUpper(mat m){
  return Transpose(LLTLower(m)); 
}

mat InverseLower(mat m){
  if (m.row == m.col){
    mat ret = Mat(m.row, m.col);
    for (int j = 0; j < m.row; j++){
      ret.value[j][j] = 1.0 / m.value[j][j];
      for (int i = j+1; i < m.row; i++) {
        float sum = 0.0;
        for (int k = j; k < i; k++) sum -= m.value[i][k] * ret.value[k][j];
        ret.value[i][j] = sum / m.value[i][i];
      }
    }
    return ret;
  } else printf("Error doing lower matrix inverse, mat.shape = %d*%d\n", m.row, m.col);
}

mat InverseUpper(mat m){
  return Transpose(InverseLower(Transpose(m)));
}

mat Inverse(mat m){
  mat L = InverseLower(LLTLower(m));
  return MultiplyMat(Transpose(L),L);
}

mat Transpose(mat m){
  mat ret = Mat(m.col, m.row);
  for (int i = 0; i < m.row; i++){
    for (int j = 0; j < m.col; j++) ret.value[j][i] = m.value[i][j];
  }
  return ret;
}

void shapeVec(vec v){
  printf("%d\n",v.size);
}  

void shapeMat(mat m){
  printf("%d*%d\n",m.row, m.col);
}

void showVec(vec m){
  for (int i = 0; i < m.size; i++) printf("%.2f ",m.value[i]);
  printf("\n");
}

void showMat(mat m){
  for (int i = 0; i < m.row; i++){
    for (int j = 0; j < m.col; j++){
      printf("%.2f ",m.value[i][j]);
    }
    printf("\n");
  }
}


