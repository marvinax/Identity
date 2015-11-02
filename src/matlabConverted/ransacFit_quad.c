/*
 * ransacFit_quad.c
 *
 * Code generation for function 'ransacFit_quad'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "ransacFit_quad.h"
#include "mean.h"
#include "abs.h"
#include "getPowderAndQr_emxutil.h"
#include "mldivide.h"
#include "rcond.h"
#include "power.h"
#include "imgDetrend_v2.h"
#include "round.h"
#include "rand.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Declarations */
static void eml_xgemm(int m, const emxArray_real_T *A, int lda, const double B[6],
                      emxArray_real_T *C, int ldc);

/* Function Definitions */
static void eml_xgemm(int m, const emxArray_real_T *A, int lda, const double B[6],
                      emxArray_real_T *C, int ldc)
{
  int ar;
  int ic;
  int br;
  int ib;
  int ia;
  if (m == 0) {
  } else {
    ar = 0;
    while ((ldc > 0) && (ar <= 0)) {
      for (ic = 1; ic <= m; ic++) {
        C->data[ic - 1] = 0.0;
      }

      ar = ldc;
    }

    br = 0;
    ar = 0;
    while ((ldc > 0) && (ar <= 0)) {
      ar = -1;
      for (ib = br; ib + 1 <= br + 6; ib++) {
        if (B[ib] != 0.0) {
          ia = ar;
          for (ic = 0; ic + 1 <= m; ic++) {
            ia++;
            C->data[ic] += B[ib] * A->data[ia];
          }
        }

        ar += lda;
      }

      br += 6;
      ar = ldc;
    }
  }
}

void ransacFit_quad(const emxArray_real_T *gx, const emxArray_real_T *gy, const
                    emxArray_real_T *val, emxArray_real_T *val_fitted, double
                    best_beta_hat_data[], int best_beta_hat_size[2], double
                    *minErr)
{
  emxArray_real_T *y_all_hat;
  emxArray_real_T *r8;
  int cnt;
  int b_gx[1];
  emxArray_real_T c_gx;
  int i5;
  int loop_ub;
  emxArray_real_T *r9;
  int b_gy[1];
  emxArray_real_T *r10;
  emxArray_real_T *r11;
  emxArray_real_T *d_gx;
  int gx_idx_0;
  int b_gx_idx_0;
  emxArray_real_T *c_gy;
  int nx;
  emxArray_real_T *X_all;
  int unnamed_idx_0;
  double idxSet_arr[6000];
  emxArray_real_T *r12;
  emxArray_real_T *b_y_all_hat;
  double x[6];
  double y[6];
  double dv0[6];
  double dv1[6];
  double X[36];
  double b_X[36];
  short b_unnamed_idx_0;
  double err;
  emxArray_real_T *b_y;
  short unnamed_idx_1;
  unsigned char sz[2];
  emxArray_real_T *c_y;
  b_emxInit_real_T(&y_all_hat, 1);
  b_emxInit_real_T(&r8, 1);

  /*  Find the best fitted plane using RANSEC */
  /*  Chau-Wai Wong, Nov. 2014 */
  /*  Chau-Wai Wong, Apr. 2015 */
  cnt = val->size[0] * val->size[1];

  /* iterCnt = min([1000 nchoosek(cnt,6)]); */
  *minErr = 1.0E+10;
  best_beta_hat_size[0] = 0;
  best_beta_hat_size[1] = 0;
  b_gx[0] = gx->size[0] * gx->size[1];
  c_gx = *gx;
  c_gx.size = (int *)&b_gx;
  c_gx.numDimensions = 1;
  power(&c_gx, r8);
  i5 = y_all_hat->size[0];
  y_all_hat->size[0] = r8->size[0];
  emxEnsureCapacity((emxArray__common *)y_all_hat, i5, (int)sizeof(double));
  loop_ub = r8->size[0];
  for (i5 = 0; i5 < loop_ub; i5++) {
    y_all_hat->data[i5] = r8->data[i5];
  }

  b_emxInit_real_T(&r9, 1);
  b_gy[0] = gy->size[0] * gy->size[1];
  c_gx = *gy;
  c_gx.size = (int *)&b_gy;
  c_gx.numDimensions = 1;
  power(&c_gx, r8);
  i5 = r9->size[0];
  r9->size[0] = r8->size[0];
  emxEnsureCapacity((emxArray__common *)r9, i5, (int)sizeof(double));
  loop_ub = r8->size[0];
  for (i5 = 0; i5 < loop_ub; i5++) {
    r9->data[i5] = r8->data[i5];
  }

  emxFree_real_T(&r8);
  b_emxInit_real_T(&r10, 1);
  i5 = r10->size[0];
  r10->size[0] = gx->size[0] * gx->size[1];
  emxEnsureCapacity((emxArray__common *)r10, i5, (int)sizeof(double));
  loop_ub = gx->size[0] * gx->size[1];
  for (i5 = 0; i5 < loop_ub; i5++) {
    r10->data[i5] = gx->data[i5] * gy->data[i5];
  }

  b_emxInit_real_T(&r11, 1);
  i5 = r11->size[0];
  r11->size[0] = cnt;
  emxEnsureCapacity((emxArray__common *)r11, i5, (int)sizeof(double));
  for (i5 = 0; i5 < cnt; i5++) {
    r11->data[i5] = 1.0;
  }

  b_emxInit_real_T(&d_gx, 1);
  gx_idx_0 = gx->size[0] * gx->size[1];
  b_gx_idx_0 = gx->size[0] * gx->size[1];
  i5 = d_gx->size[0];
  d_gx->size[0] = gx_idx_0;
  emxEnsureCapacity((emxArray__common *)d_gx, i5, (int)sizeof(double));
  for (i5 = 0; i5 < gx_idx_0; i5++) {
    d_gx->data[i5] = gx->data[i5];
  }

  b_emxInit_real_T(&c_gy, 1);
  nx = gy->size[0] * gy->size[1];
  loop_ub = gy->size[0] * gy->size[1];
  i5 = c_gy->size[0];
  c_gy->size[0] = nx;
  emxEnsureCapacity((emxArray__common *)c_gy, i5, (int)sizeof(double));
  for (i5 = 0; i5 < nx; i5++) {
    c_gy->data[i5] = gy->data[i5];
  }

  emxInit_real_T(&X_all, 2);
  nx = y_all_hat->size[0];
  gx_idx_0 = r9->size[0];
  unnamed_idx_0 = r10->size[0];
  i5 = X_all->size[0] * X_all->size[1];
  X_all->size[0] = cnt;
  X_all->size[1] = 6;
  emxEnsureCapacity((emxArray__common *)X_all, i5, (int)sizeof(double));
  for (i5 = 0; i5 < cnt; i5++) {
    X_all->data[i5] = r11->data[i5];
  }

  emxFree_real_T(&r11);
  for (i5 = 0; i5 < b_gx_idx_0; i5++) {
    X_all->data[i5 + X_all->size[0]] = d_gx->data[i5];
  }

  emxFree_real_T(&d_gx);
  for (i5 = 0; i5 < loop_ub; i5++) {
    X_all->data[i5 + (X_all->size[0] << 1)] = c_gy->data[i5];
  }

  emxFree_real_T(&c_gy);
  for (i5 = 0; i5 < nx; i5++) {
    X_all->data[i5 + X_all->size[0] * 3] = y_all_hat->data[i5];
  }

  for (i5 = 0; i5 < gx_idx_0; i5++) {
    X_all->data[i5 + (X_all->size[0] << 2)] = r9->data[i5];
  }

  emxFree_real_T(&r9);
  for (i5 = 0; i5 < unnamed_idx_0; i5++) {
    X_all->data[i5 + X_all->size[0] * 5] = r10->data[i5];
  }

  emxFree_real_T(&r10);
  b_rand(idxSet_arr);
  for (i5 = 0; i5 < 6000; i5++) {
    idxSet_arr[i5] *= (double)cnt - 1.0;
  }

  c_round(idxSet_arr);
  for (i5 = 0; i5 < 6000; i5++) {
    idxSet_arr[i5]++;
  }

  b_emxInit_real_T(&r12, 1);
  b_emxInit_real_T(&b_y_all_hat, 1);
  for (nx = 0; nx < 1000; nx++) {
    for (i5 = 0; i5 < 6; i5++) {
      x[i5] = gx->data[(int)idxSet_arr[i5 + 6 * nx] - 1];
    }

    for (i5 = 0; i5 < 6; i5++) {
      y[i5] = gy->data[(int)idxSet_arr[i5 + 6 * nx] - 1];
    }

    b_power(x, dv0);
    b_power(y, dv1);
    for (i5 = 0; i5 < 6; i5++) {
      X[i5] = 1.0;
      X[6 + i5] = x[i5];
      X[12 + i5] = y[i5];
      X[18 + i5] = dv0[i5];
      X[24 + i5] = dv1[i5];
      X[30 + i5] = x[i5] * y[i5];
    }

    if (rcond(X) < 1.0E-10) {
      /* disp(['skipped ' int2str(i)]) */
    } else {
      for (i5 = 0; i5 < 6; i5++) {
        y[i5] = val->data[(int)idxSet_arr[i5 + 6 * nx] - 1];
      }

      for (i5 = 0; i5 < 6; i5++) {
        x[i5] = 0.0;
        for (gx_idx_0 = 0; gx_idx_0 < 6; gx_idx_0++) {
          x[i5] += X[gx_idx_0 + 6 * i5] * y[gx_idx_0];
        }

        for (gx_idx_0 = 0; gx_idx_0 < 6; gx_idx_0++) {
          b_X[i5 + 6 * gx_idx_0] = 0.0;
          for (unnamed_idx_0 = 0; unnamed_idx_0 < 6; unnamed_idx_0++) {
            b_X[i5 + 6 * gx_idx_0] += X[unnamed_idx_0 + 6 * i5] *
              X[unnamed_idx_0 + 6 * gx_idx_0];
          }
        }
      }

      d_mldivide(b_X, x);
      b_unnamed_idx_0 = (short)X_all->size[0];
      i5 = y_all_hat->size[0];
      y_all_hat->size[0] = b_unnamed_idx_0;
      emxEnsureCapacity((emxArray__common *)y_all_hat, i5, (int)sizeof(double));
      loop_ub = b_unnamed_idx_0;
      for (i5 = 0; i5 < loop_ub; i5++) {
        y_all_hat->data[i5] = 0.0;
      }

      eml_xgemm(X_all->size[0], X_all, X_all->size[0], x, y_all_hat, X_all->
                size[0]);
      i5 = b_y_all_hat->size[0];
      b_y_all_hat->size[0] = y_all_hat->size[0];
      emxEnsureCapacity((emxArray__common *)b_y_all_hat, i5, (int)sizeof(double));
      loop_ub = y_all_hat->size[0];
      for (i5 = 0; i5 < loop_ub; i5++) {
        b_y_all_hat->data[i5] = y_all_hat->data[i5] - val->data[i5];
      }

      b_abs(b_y_all_hat, r12);
      err = mean(r12);
      if (err < *minErr) {
        best_beta_hat_size[0] = 6;
        best_beta_hat_size[1] = 1;
        for (i5 = 0; i5 < 6; i5++) {
          best_beta_hat_data[i5] = x[i5];
        }

        *minErr = err;
      }
    }
  }

  emxFree_real_T(&b_y_all_hat);
  emxFree_real_T(&r12);
  emxFree_real_T(&y_all_hat);
  emxInit_real_T(&b_y, 2);
  if (best_beta_hat_size[0] == 1) {
    i5 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = X_all->size[0];
    b_y->size[1] = best_beta_hat_size[1];
    emxEnsureCapacity((emxArray__common *)b_y, i5, (int)sizeof(double));
    loop_ub = X_all->size[0];
    for (i5 = 0; i5 < loop_ub; i5++) {
      nx = best_beta_hat_size[1];
      for (gx_idx_0 = 0; gx_idx_0 < nx; gx_idx_0++) {
        b_y->data[i5 + b_y->size[0] * gx_idx_0] = 0.0;
        for (unnamed_idx_0 = 0; unnamed_idx_0 < 6; unnamed_idx_0++) {
          b_y->data[i5 + b_y->size[0] * gx_idx_0] += X_all->data[i5 +
            X_all->size[0] * unnamed_idx_0] * best_beta_hat_data[unnamed_idx_0 +
            best_beta_hat_size[0] * gx_idx_0];
        }
      }
    }
  } else {
    b_unnamed_idx_0 = (short)X_all->size[0];
    unnamed_idx_1 = (short)best_beta_hat_size[1];
    i5 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = b_unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *)b_y, i5, (int)sizeof(double));
    i5 = b_y->size[0] * b_y->size[1];
    b_y->size[1] = unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)b_y, i5, (int)sizeof(double));
    loop_ub = b_unnamed_idx_0 * unnamed_idx_1;
    for (i5 = 0; i5 < loop_ub; i5++) {
      b_y->data[i5] = 0.0;
    }

    b_eml_xgemm(X_all->size[0], best_beta_hat_size[1], X_all, X_all->size[0],
                best_beta_hat_data, b_y, X_all->size[0]);
  }

  emxFree_real_T(&X_all);
  nx = b_y->size[0] * b_y->size[1];
  for (i5 = 0; i5 < 2; i5++) {
    sz[i5] = (unsigned char)val->size[i5];
  }

  emxInit_real_T(&c_y, 2);
  i5 = c_y->size[0] * c_y->size[1];
  c_y->size[0] = sz[0];
  c_y->size[1] = sz[1];
  emxEnsureCapacity((emxArray__common *)c_y, i5, (int)sizeof(double));
  for (gx_idx_0 = 0; gx_idx_0 + 1 <= nx; gx_idx_0++) {
    c_y->data[gx_idx_0] = b_y->data[gx_idx_0];
  }

  emxFree_real_T(&b_y);
  i5 = val_fitted->size[0] * val_fitted->size[1];
  val_fitted->size[0] = c_y->size[0];
  val_fitted->size[1] = c_y->size[1];
  emxEnsureCapacity((emxArray__common *)val_fitted, i5, (int)sizeof(double));
  loop_ub = c_y->size[0] * c_y->size[1];
  for (i5 = 0; i5 < loop_ub; i5++) {
    val_fitted->data[i5] = c_y->data[i5];
  }

  emxFree_real_T(&c_y);
}

/* End of code generation (ransacFit_quad.c) */
