/*
 * fitgeotrans.c
 *
 * Code generation for function 'fitgeotrans'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "fitgeotrans.h"
#include "projective2d.h"
#include "inv.h"
#include "mldivide.h"
#include "svd.h"
#include "normalizeControlPoints.h"
#include "getPowderAndQr_rtwutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void b_fitgeotrans(const double movingPoints[8], const double fixedPoints[8],
                   double tform_T[9])
{
  double T[9];
  double uv[8];
  double normMatrix2[9];
  double xy[8];
  int i33;
  double X[64];
  double s[8];
  double absxk;
  int exponent;
  double Tvec[9];
  double Tinv[9];
  double b_Tinv[9];
  int i34;
  double dv12[9];
  normalizeControlPoints(movingPoints, uv, T);
  normalizeControlPoints(fixedPoints, xy, normMatrix2);
  for (i33 = 0; i33 < 4; i33++) {
    X[i33] = xy[i33];
    X[8 + i33] = xy[4 + i33];
    X[16 + i33] = 1.0;
    X[24 + i33] = 0.0;
    X[32 + i33] = 0.0;
    X[40 + i33] = 0.0;
    X[48 + i33] = -uv[i33] * xy[i33];
    X[56 + i33] = -uv[i33] * xy[4 + i33];
  }

  for (i33 = 0; i33 < 4; i33++) {
    X[i33 + 4] = 0.0;
    X[i33 + 12] = 0.0;
    X[i33 + 20] = 0.0;
    X[i33 + 28] = xy[i33];
    X[i33 + 36] = xy[4 + i33];
    X[i33 + 44] = 1.0;
    X[i33 + 52] = -uv[4 + i33] * xy[i33];
    X[i33 + 60] = -uv[4 + i33] * xy[4 + i33];
  }

  b_svd(X, s);
  absxk = fabs(s[0]);
  if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk)) && (!(absxk <=
        2.2250738585072014E-308))) {
    frexp(absxk, &exponent);
  }

  for (i33 = 0; i33 < 4; i33++) {
    s[i33] = uv[i33];
  }

  for (i33 = 0; i33 < 4; i33++) {
    s[i33 + 4] = uv[4 + i33];
  }

  e_mldivide(X, s);
  memcpy(&Tvec[0], &s[0], sizeof(double) << 3);
  Tvec[8] = 1.0;
  memcpy(&Tinv[0], &Tvec[0], 9U * sizeof(double));
  for (i33 = 0; i33 < 3; i33++) {
    for (exponent = 0; exponent < 3; exponent++) {
      b_Tinv[i33 + 3 * exponent] = 0.0;
      for (i34 = 0; i34 < 3; i34++) {
        b_Tinv[i33 + 3 * exponent] += Tinv[i33 + 3 * i34] * T[i34 + 3 * exponent];
      }
    }
  }

  b_mldivide(normMatrix2, b_Tinv, dv12);
  inv(dv12, T);
  absxk = T[8];
  for (i33 = 0; i33 < 9; i33++) {
    T[i33] /= absxk;
  }

  projective2d_projective2d(T, &absxk, tform_T);
}

void fitgeotrans(const double movingPoints[16], double tform_T[9])
{
  double cent[2];
  int ix;
  int iy;
  int i;
  int ak;
  double c_sumOfPointDistancesFromOrigin;
  int k;
  double uv[16];
  double cv[8];
  static const double dv4[8] = { -0.57735026918962584, -0.57735026918962584,
    -0.57735026918962584, -0.57735026918962584, 0.57735026918962584,
    0.57735026918962584, 0.57735026918962584, 0.57735026918962584 };

  double X[128];
  static const double dv5[8] = { -1.7320508075688774, -0.57735026918962584,
    0.57735026918962584, 1.7320508075688774, -1.7320508075688774,
    -0.57735026918962584, 0.57735026918962584, 1.7320508075688774 };

  static const double x[8] = { -0.57735026918962584, -0.57735026918962584,
    -0.57735026918962584, -0.57735026918962584, 0.57735026918962584,
    0.57735026918962584, 0.57735026918962584, 0.57735026918962584 };

  static const double y[8] = { -1.7320508075688774, -0.57735026918962584,
    0.57735026918962584, 1.7320508075688774, -1.7320508075688774,
    -0.57735026918962584, 0.57735026918962584, 1.7320508075688774 };

  double av[8];
  double absxk;
  int exponent;
  double Tvec[9];
  double b_uv[16];
  double Tinv[9];
  double b_Tinv[9];
  double T[9];
  double dv6[9];
  static const double dv7[9] = { 172.33905535310328, 0.0, 160.5, 0.0,
    172.33905535310328, 359.5, 0.0, 0.0, 1.0 };

  ix = 0;
  iy = -1;
  for (i = 0; i < 2; i++) {
    ak = ix;
    ix++;
    c_sumOfPointDistancesFromOrigin = movingPoints[ak];
    for (k = 0; k < 7; k++) {
      ix++;
      c_sumOfPointDistancesFromOrigin += movingPoints[ix - 1];
    }

    iy++;
    cent[iy] = c_sumOfPointDistancesFromOrigin;
  }

  for (iy = 0; iy < 2; iy++) {
    cent[iy] /= 8.0;
  }

  ak = 0;
  ix = 0;
  for (iy = 0; iy < 10; iy += 8) {
    for (k = 0; k < 8; k++) {
      cv[k] = movingPoints[ak + k] - cent[ix];
    }

    memcpy(&uv[iy], &cv[0], sizeof(double) << 3);
    ak += 8;
    ix++;
  }

  for (k = 0; k < 8; k++) {
    c_sumOfPointDistancesFromOrigin = rt_hypotd_snf(uv[k], uv[8 + k]);
    cv[k] = c_sumOfPointDistancesFromOrigin * c_sumOfPointDistancesFromOrigin;
  }

  c_sumOfPointDistancesFromOrigin = cv[0];
  for (k = 0; k < 7; k++) {
    c_sumOfPointDistancesFromOrigin += cv[k + 1];
  }

  if (c_sumOfPointDistancesFromOrigin > 0.0) {
    c_sumOfPointDistancesFromOrigin = 4.0 / sqrt(c_sumOfPointDistancesFromOrigin);
  } else {
    c_sumOfPointDistancesFromOrigin = 1.0;
  }

  for (iy = 0; iy < 16; iy++) {
    uv[iy] *= c_sumOfPointDistancesFromOrigin;
  }

  for (iy = 0; iy < 8; iy++) {
    X[iy] = dv4[iy];
    X[16 + iy] = dv5[iy];
    X[32 + iy] = 1.0;
    X[48 + iy] = 0.0;
    X[64 + iy] = 0.0;
    X[80 + iy] = 0.0;
    X[96 + iy] = -uv[iy] * x[iy];
    X[112 + iy] = -uv[iy] * y[iy];
  }

  for (iy = 0; iy < 8; iy++) {
    X[iy + 8] = 0.0;
    X[iy + 24] = 0.0;
    X[iy + 40] = 0.0;
    X[iy + 56] = dv4[iy];
    X[iy + 72] = dv5[iy];
    X[iy + 88] = 1.0;
    X[iy + 104] = -uv[8 + iy] * x[iy];
    X[iy + 120] = -uv[8 + iy] * y[iy];
  }

  svd(X, av);
  absxk = fabs(av[0]);
  if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk)) && (!(absxk <=
        2.2250738585072014E-308))) {
    frexp(absxk, &exponent);
  }

  memcpy(&b_uv[0], &uv[0], sizeof(double) << 3);
  memcpy(&b_uv[8], &uv[8], sizeof(double) << 3);
  mldivide(X, b_uv, av);
  memcpy(&Tvec[0], &av[0], sizeof(double) << 3);
  Tvec[8] = 1.0;
  memcpy(&Tinv[0], &Tvec[0], 9U * sizeof(double));
  T[0] = 1.0 / c_sumOfPointDistancesFromOrigin;
  T[3] = 0.0;
  T[6] = 0.0;
  T[1] = 0.0;
  T[4] = 1.0 / c_sumOfPointDistancesFromOrigin;
  T[7] = 0.0;
  T[2] = cent[0];
  T[5] = cent[1];
  T[8] = 1.0;
  for (iy = 0; iy < 3; iy++) {
    for (ak = 0; ak < 3; ak++) {
      b_Tinv[iy + 3 * ak] = 0.0;
      for (ix = 0; ix < 3; ix++) {
        b_Tinv[iy + 3 * ak] += Tinv[iy + 3 * ix] * T[ix + 3 * ak];
      }
    }
  }

  b_mldivide(dv7, b_Tinv, dv6);
  inv(dv6, T);
  c_sumOfPointDistancesFromOrigin = T[8];
  for (iy = 0; iy < 9; iy++) {
    T[iy] /= c_sumOfPointDistancesFromOrigin;
  }

  projective2d_projective2d(T, &c_sumOfPointDistancesFromOrigin, tform_T);
}

/* End of code generation (fitgeotrans.c) */
