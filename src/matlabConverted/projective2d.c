/*
 * projective2d.c
 *
 * Code generation for function 'projective2d'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "projective2d.h"
#include "repmat.h"
#include "inv.h"
#include "getPowderAndQr_emxutil.h"
#include "rdivide.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void c_projective2d_transformPointsI(const double self_T[9], const
  emxArray_real_T *varargin_1, const emxArray_real_T *varargin_2,
  emxArray_real_T *varargout_1, emxArray_real_T *varargout_2)
{
  emxArray_real_T *w;
  double M[9];
  int i22;
  int loop_ub;
  emxArray_real_T *b_M;
  emxArray_real_T *c_M;
  emxInit_real_T(&w, 2);
  inv(self_T, M);
  i22 = w->size[0] * w->size[1];
  w->size[0] = varargin_1->size[0];
  w->size[1] = varargin_1->size[1];
  emxEnsureCapacity((emxArray__common *)w, i22, (int)sizeof(double));
  loop_ub = varargin_1->size[0] * varargin_1->size[1];
  for (i22 = 0; i22 < loop_ub; i22++) {
    w->data[i22] = (M[6] * varargin_1->data[i22] + M[7] * varargin_2->data[i22])
      + M[8];
  }

  emxInit_real_T(&b_M, 2);
  i22 = b_M->size[0] * b_M->size[1];
  b_M->size[0] = varargin_1->size[0];
  b_M->size[1] = varargin_1->size[1];
  emxEnsureCapacity((emxArray__common *)b_M, i22, (int)sizeof(double));
  loop_ub = varargin_1->size[0] * varargin_1->size[1];
  for (i22 = 0; i22 < loop_ub; i22++) {
    b_M->data[i22] = (M[0] * varargin_1->data[i22] + M[1] * varargin_2->data[i22])
      + M[2];
  }

  emxInit_real_T(&c_M, 2);
  b_rdivide(b_M, w, varargout_1);
  i22 = c_M->size[0] * c_M->size[1];
  c_M->size[0] = varargin_1->size[0];
  c_M->size[1] = varargin_1->size[1];
  emxEnsureCapacity((emxArray__common *)c_M, i22, (int)sizeof(double));
  loop_ub = varargin_1->size[0] * varargin_1->size[1];
  emxFree_real_T(&b_M);
  for (i22 = 0; i22 < loop_ub; i22++) {
    c_M->data[i22] = (M[3] * varargin_1->data[i22] + M[4] * varargin_2->data[i22])
      + M[5];
  }

  b_rdivide(c_M, w, varargout_2);
  emxFree_real_T(&c_M);
  emxFree_real_T(&w);
}

void d_projective2d_transformPointsI(const double self_T[9], const double
  varargin_1[16], double varargout_1_data[], int varargout_1_size[2])
{
  signed char sizeB[2];
  int k;
  double X_data[81];
  int X_size_idx_0;
  int j;
  int br;
  double Tinv[9];
  int m;
  int U_size_idx_0;
  int i31;
  double U_data[27];
  int ic;
  int ar;
  int ib;
  int ia;
  int i32;
  int U_size[1];
  int y_size[2];
  double y_data[18];
  double b_U_data[18];
  for (k = 0; k < 2; k++) {
    sizeB[k] = (signed char)((-6 * k + k) + 8);
  }

  X_size_idx_0 = sizeB[0];
  for (j = 3; j <= sizeB[1]; j++) {
    for (br = 0; br < X_size_idx_0; br++) {
      X_data[br + X_size_idx_0 * (j - 1)] = 1.0;
    }
  }

  for (j = 0; j < 2; j++) {
    br = 9;
    while (br <= X_size_idx_0) {
      X_data[8 + 9 * j] = 1.0;
      br = 10;
    }
  }

  for (j = 0; j < 2; j++) {
    memcpy(&X_data[X_size_idx_0 * j], &varargin_1[j << 3], sizeof(double) << 3);
  }

  inv(self_T, Tinv);
  k = sizeB[1];
  m = sizeB[0];
  U_size_idx_0 = sizeB[0];
  X_size_idx_0 = sizeB[0] * 3;
  for (i31 = 0; i31 < X_size_idx_0; i31++) {
    U_data[i31] = 0.0;
  }

  X_size_idx_0 = sizeB[0] << 1;
  for (j = 0; j <= X_size_idx_0; j += m) {
    i31 = j + m;
    for (ic = j; ic + 1 <= i31; ic++) {
      U_data[ic] = 0.0;
    }
  }

  br = 0;
  for (j = 0; j <= X_size_idx_0; j += m) {
    ar = 0;
    i31 = br + k;
    for (ib = br; ib + 1 <= i31; ib++) {
      if (Tinv[ib] != 0.0) {
        ia = ar;
        i32 = j + m;
        for (ic = j; ic + 1 <= i32; ic++) {
          ia++;
          U_data[ic] += Tinv[ib] * X_data[ia - 1];
        }
      }

      ar += m;
    }

    br += k;
  }

  X_size_idx_0 = sizeB[0];
  U_size[0] = sizeB[0];
  for (i31 = 0; i31 < X_size_idx_0; i31++) {
    Tinv[i31] = U_data[i31 + (U_size_idx_0 << 1)];
  }

  repmat(Tinv, U_size, y_data, y_size);
  X_size_idx_0 = sizeB[0];
  for (i31 = 0; i31 < 2; i31++) {
    for (i32 = 0; i32 < X_size_idx_0; i32++) {
      b_U_data[i32 + X_size_idx_0 * i31] = U_data[i32 + U_size_idx_0 * i31] /
        y_data[i32 + y_size[0] * i31];
    }
  }

  for (i31 = 0; i31 < 2; i31++) {
    for (i32 = 0; i32 < X_size_idx_0; i32++) {
      U_data[i32 + U_size_idx_0 * i31] = b_U_data[i32 + X_size_idx_0 * i31];
    }
  }

  X_size_idx_0 = sizeB[0];
  varargout_1_size[0] = sizeB[0];
  varargout_1_size[1] = 2;
  for (i31 = 0; i31 < 2; i31++) {
    for (i32 = 0; i32 < X_size_idx_0; i32++) {
      varargout_1_data[i32 + X_size_idx_0 * i31] = U_data[i32 + U_size_idx_0 *
        i31];
    }
  }
}

void e_projective2d_transformPointsI(const double self_T[9], const double
  varargin_1[8], double varargout_1_data[], int varargout_1_size[2])
{
  signed char sizeB[2];
  int k;
  double X_data[25];
  int X_size_idx_0;
  int j;
  int br;
  double Tinv[9];
  int m;
  int y_size_idx_0;
  int i38;
  double y_data[27];
  int ic;
  int ar;
  int ib;
  int ia;
  int i39;
  double U_data[15];
  double b_y_data[5];
  int y_size[1];
  int b_y_size[2];
  double c_y_data[18];
  for (k = 0; k < 2; k++) {
    sizeB[k] = (signed char)((-2 * k + k) + 4);
  }

  X_size_idx_0 = sizeB[0];
  for (j = 3; j <= sizeB[1]; j++) {
    for (br = 0; br < X_size_idx_0; br++) {
      X_data[br + X_size_idx_0 * (j - 1)] = 1.0;
    }
  }

  for (j = 0; j < 2; j++) {
    br = 5;
    while (br <= X_size_idx_0) {
      X_data[4 + 5 * j] = 1.0;
      br = 6;
    }
  }

  for (j = 0; j < 2; j++) {
    for (br = 0; br < 4; br++) {
      X_data[br + X_size_idx_0 * j] = varargin_1[br + (j << 2)];
    }
  }

  inv(self_T, Tinv);
  k = sizeB[1];
  m = sizeB[0];
  y_size_idx_0 = sizeB[0];
  j = sizeB[0] * 3;
  for (i38 = 0; i38 < j; i38++) {
    y_data[i38] = 0.0;
  }

  X_size_idx_0 = sizeB[0] << 1;
  for (j = 0; j <= X_size_idx_0; j += m) {
    i38 = j + m;
    for (ic = j; ic + 1 <= i38; ic++) {
      y_data[ic] = 0.0;
    }
  }

  br = 0;
  for (j = 0; j <= X_size_idx_0; j += m) {
    ar = 0;
    i38 = br + k;
    for (ib = br; ib + 1 <= i38; ib++) {
      if (Tinv[ib] != 0.0) {
        ia = ar;
        i39 = j + m;
        for (ic = j; ic + 1 <= i39; ic++) {
          ia++;
          y_data[ic] += Tinv[ib] * X_data[ia - 1];
        }
      }

      ar += m;
    }

    br += k;
  }

  X_size_idx_0 = sizeB[0];
  j = sizeB[0] * 3;
  for (i38 = 0; i38 < j; i38++) {
    U_data[i38] = y_data[i38];
  }

  j = sizeB[0];
  y_size[0] = sizeB[0];
  for (i38 = 0; i38 < j; i38++) {
    b_y_data[i38] = y_data[i38 + (y_size_idx_0 << 1)];
  }

  repmat(b_y_data, y_size, c_y_data, b_y_size);
  j = sizeB[0] - 1;
  for (i38 = 0; i38 < 2; i38++) {
    for (i39 = 0; i39 <= j; i39++) {
      U_data[i39 + X_size_idx_0 * i38] = y_data[i39 + y_size_idx_0 * i38] /
        c_y_data[i39 + b_y_size[0] * i38];
    }
  }

  j = sizeB[0];
  varargout_1_size[0] = sizeB[0];
  varargout_1_size[1] = 2;
  for (i38 = 0; i38 < 2; i38++) {
    for (i39 = 0; i39 < j; i39++) {
      varargout_1_data[i39 + j * i38] = U_data[i39 + X_size_idx_0 * i38];
    }
  }
}

void projective2d_projective2d(const double A[9], double *self_Dimensionality,
  double self_T[9])
{
  memcpy(&self_T[0], &A[0], 9U * sizeof(double));
  *self_Dimensionality = 2.0;
}

/* End of code generation (projective2d.c) */
