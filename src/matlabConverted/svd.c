/*
 * svd.c
 *
 * Code generation for function 'svd'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "svd.h"
#include "mldivide.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Declarations */
static void b_eml_xaxpy(int n, double a, const double x[128], int ix0, double y
  [16], int iy0);
static double b_eml_xdotc(int n, const double x[64], int ix0, const double y[64],
  int iy0);
static double b_eml_xnrm2(int n, const double x[8], int ix0);
static void c_eml_xaxpy(int n, double a, const double x[16], int ix0, double y
  [128], int iy0);
static void d_eml_xaxpy(int n, double a, int ix0, double y[64], int iy0);
static double d_eml_xnrm2(int n, const double x[64], int ix0);
static void e_eml_xaxpy(int n, double a, const double x[64], int ix0, double y[8],
  int iy0);
static void eml_xaxpy(int n, double a, int ix0, double y[128], int iy0);
static double eml_xdotc(int n, const double x[128], int ix0, const double y[128],
  int iy0);
static void eml_xrotg(double *a, double *b, double *c, double *s);
static void f_eml_xaxpy(int n, double a, const double x[8], int ix0, double y[64],
  int iy0);

/* Function Definitions */
static void b_eml_xaxpy(int n, double a, const double x[128], int ix0, double y
  [16], int iy0)
{
  int ix;
  int iy;
  int k;
  if (a == 0.0) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

static double b_eml_xdotc(int n, const double x[64], int ix0, const double y[64],
  int iy0)
{
  double d;
  int ix;
  int iy;
  int k;
  d = 0.0;
  ix = ix0;
  iy = iy0;
  for (k = 1; k <= n; k++) {
    d += x[ix - 1] * y[iy - 1];
    ix++;
    iy++;
  }

  return d;
}

static double b_eml_xnrm2(int n, const double x[8], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 2.2250738585072014E-308;
  kend = (ix0 + n) - 1;
  for (k = ix0; k <= kend; k++) {
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

static void c_eml_xaxpy(int n, double a, const double x[16], int ix0, double y
  [128], int iy0)
{
  int ix;
  int iy;
  int k;
  if (a == 0.0) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

static void d_eml_xaxpy(int n, double a, int ix0, double y[64], int iy0)
{
  int ix;
  int iy;
  int k;
  if (a == 0.0) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

static double d_eml_xnrm2(int n, const double x[64], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 2.2250738585072014E-308;
  kend = (ix0 + n) - 1;
  for (k = ix0; k <= kend; k++) {
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

static void e_eml_xaxpy(int n, double a, const double x[64], int ix0, double y[8],
  int iy0)
{
  int ix;
  int iy;
  int k;
  if (a == 0.0) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

static void eml_xaxpy(int n, double a, int ix0, double y[128], int iy0)
{
  int ix;
  int iy;
  int k;
  if (a == 0.0) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

static double eml_xdotc(int n, const double x[128], int ix0, const double y[128],
  int iy0)
{
  double d;
  int ix;
  int iy;
  int k;
  d = 0.0;
  ix = ix0;
  iy = iy0;
  for (k = 1; k <= n; k++) {
    d += x[ix - 1] * y[iy - 1];
    ix++;
    iy++;
  }

  return d;
}

static void eml_xrotg(double *a, double *b, double *c, double *s)
{
  double roe;
  double absa;
  double absb;
  double scale;
  double ads;
  double bds;
  roe = *b;
  absa = fabs(*a);
  absb = fabs(*b);
  if (absa > absb) {
    roe = *a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    scale = 0.0;
    *b = 0.0;
  } else {
    ads = absa / scale;
    bds = absb / scale;
    scale *= sqrt(ads * ads + bds * bds);
    if (roe < 0.0) {
      scale = -scale;
    }

    *c = *a / scale;
    *s = *b / scale;
    if (absa > absb) {
      *b = *s;
    } else if (*c != 0.0) {
      *b = 1.0 / *c;
    } else {
      *b = 1.0;
    }
  }

  *a = scale;
}

static void f_eml_xaxpy(int n, double a, const double x[8], int ix0, double y[64],
  int iy0)
{
  int ix;
  int iy;
  int k;
  if (a == 0.0) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

void b_svd(const double A[64], double U[8])
{
  double b_A[64];
  double s[8];
  double e[8];
  double work[8];
  int i;
  int q;
  int qs;
  boolean_T apply_transform;
  double ztest0;
  int qjj;
  int m;
  double ztest;
  double rt;
  int iter;
  double snorm;
  int32_T exitg3;
  boolean_T exitg2;
  double f;
  double varargin_1[5];
  double mtmp;
  boolean_T exitg1;
  double sqds;
  memcpy(&b_A[0], &A[0], sizeof(double) << 6);
  for (i = 0; i < 8; i++) {
    s[i] = 0.0;
    e[i] = 0.0;
    work[i] = 0.0;
  }

  for (q = 0; q < 7; q++) {
    qs = q + (q << 3);
    apply_transform = false;
    ztest0 = d_eml_xnrm2(8 - q, b_A, qs + 1);
    if (ztest0 > 0.0) {
      apply_transform = true;
      if (b_A[qs] < 0.0) {
        s[q] = -ztest0;
      } else {
        s[q] = ztest0;
      }

      if (fabs(s[q]) >= 1.0020841800044864E-292) {
        ztest0 = 1.0 / s[q];
        i = (qs - q) + 8;
        for (qjj = qs; qjj + 1 <= i; qjj++) {
          b_A[qjj] *= ztest0;
        }
      } else {
        i = (qs - q) + 8;
        for (qjj = qs; qjj + 1 <= i; qjj++) {
          b_A[qjj] /= s[q];
        }
      }

      b_A[qs]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0;
    }

    for (i = q + 1; i + 1 < 9; i++) {
      qjj = q + (i << 3);
      if (apply_transform) {
        d_eml_xaxpy(8 - q, -(b_eml_xdotc(8 - q, b_A, qs + 1, b_A, qjj + 1) /
                             b_A[q + (q << 3)]), qs + 1, b_A, qjj + 1);
      }

      e[i] = b_A[qjj];
    }

    if (q + 1 <= 6) {
      ztest0 = b_eml_xnrm2(7 - q, e, q + 2);
      if (ztest0 == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -ztest0;
        } else {
          e[q] = ztest0;
        }

        ztest0 = e[q];
        if (fabs(e[q]) >= 1.0020841800044864E-292) {
          ztest0 = 1.0 / e[q];
          for (qjj = q + 1; qjj + 1 < 9; qjj++) {
            e[qjj] *= ztest0;
          }
        } else {
          for (qjj = q + 1; qjj + 1 < 9; qjj++) {
            e[qjj] /= ztest0;
          }
        }

        e[q + 1]++;
        e[q] = -e[q];
        for (i = q + 1; i + 1 < 9; i++) {
          work[i] = 0.0;
        }

        for (i = q + 1; i + 1 < 9; i++) {
          e_eml_xaxpy(7 - q, e[i], b_A, (q + (i << 3)) + 2, work, q + 2);
        }

        for (i = q + 1; i + 1 < 9; i++) {
          f_eml_xaxpy(7 - q, -e[i] / e[q + 1], work, q + 2, b_A, (q + (i << 3))
                      + 2);
        }
      }
    }
  }

  m = 6;
  s[7] = b_A[63];
  e[6] = b_A[62];
  e[7] = 0.0;
  for (q = 0; q < 8; q++) {
    ztest = e[q];
    if (s[q] != 0.0) {
      rt = fabs(s[q]);
      ztest0 = s[q] / rt;
      s[q] = rt;
      if (q + 1 < 8) {
        ztest = e[q] / ztest0;
      }
    }

    if ((q + 1 < 8) && (ztest != 0.0)) {
      rt = fabs(ztest);
      ztest0 = ztest;
      ztest = rt;
      s[q + 1] *= rt / ztest0;
    }

    e[q] = ztest;
  }

  iter = 0;
  snorm = 0.0;
  for (i = 0; i < 8; i++) {
    ztest0 = fabs(s[i]);
    ztest = fabs(e[i]);
    if ((ztest0 >= ztest) || rtIsNaN(ztest)) {
    } else {
      ztest0 = ztest;
    }

    if ((snorm >= ztest0) || rtIsNaN(ztest0)) {
    } else {
      snorm = ztest0;
    }
  }

  while ((m + 2 > 0) && (!(iter >= 75))) {
    i = m;
    do {
      exitg3 = 0;
      q = i + 1;
      if (i + 1 == 0) {
        exitg3 = 1;
      } else {
        ztest0 = fabs(e[i]);
        if ((ztest0 <= 2.2204460492503131E-16 * (fabs(s[i]) + fabs(s[i + 1]))) ||
            (ztest0 <= 1.0020841800044864E-292) || ((iter > 20) && (ztest0 <=
              2.2204460492503131E-16 * snorm))) {
          e[i] = 0.0;
          exitg3 = 1;
        } else {
          i--;
        }
      }
    } while (exitg3 == 0);

    if (i + 1 == m + 1) {
      i = 4;
    } else {
      qs = m + 2;
      qjj = m + 2;
      exitg2 = false;
      while ((!exitg2) && (qjj >= i + 1)) {
        qs = qjj;
        if (qjj == i + 1) {
          exitg2 = true;
        } else {
          ztest0 = 0.0;
          if (qjj < m + 2) {
            ztest0 = fabs(e[qjj - 1]);
          }

          if (qjj > i + 2) {
            ztest0 += fabs(e[qjj - 2]);
          }

          ztest = fabs(s[qjj - 1]);
          if ((ztest <= 2.2204460492503131E-16 * ztest0) || (ztest <=
               1.0020841800044864E-292)) {
            s[qjj - 1] = 0.0;
            exitg2 = true;
          } else {
            qjj--;
          }
        }
      }

      if (qs == i + 1) {
        i = 3;
      } else if (qs == m + 2) {
        i = 1;
      } else {
        i = 2;
        q = qs;
      }
    }

    switch (i) {
     case 1:
      f = e[m];
      e[m] = 0.0;
      for (qjj = m; qjj + 1 >= q + 1; qjj--) {
        ztest0 = s[qjj];
        eml_xrotg(&ztest0, &f, &ztest, &rt);
        s[qjj] = ztest0;
        if (qjj + 1 > q + 1) {
          f = -rt * e[qjj - 1];
          e[qjj - 1] *= ztest;
        }
      }
      break;

     case 2:
      f = e[q - 1];
      e[q - 1] = 0.0;
      while (q + 1 <= m + 2) {
        eml_xrotg(&s[q], &f, &ztest, &rt);
        f = -rt * e[q];
        e[q] *= ztest;
        q++;
      }
      break;

     case 3:
      varargin_1[0] = fabs(s[m + 1]);
      varargin_1[1] = fabs(s[m]);
      varargin_1[2] = fabs(e[m]);
      varargin_1[3] = fabs(s[q]);
      varargin_1[4] = fabs(e[q]);
      i = 1;
      mtmp = varargin_1[0];
      if (rtIsNaN(varargin_1[0])) {
        qjj = 2;
        exitg1 = false;
        while ((!exitg1) && (qjj < 6)) {
          i = qjj;
          if (!rtIsNaN(varargin_1[qjj - 1])) {
            mtmp = varargin_1[qjj - 1];
            exitg1 = true;
          } else {
            qjj++;
          }
        }
      }

      if (i < 5) {
        while (i + 1 < 6) {
          if (varargin_1[i] > mtmp) {
            mtmp = varargin_1[i];
          }

          i++;
        }
      }

      f = s[m + 1] / mtmp;
      ztest0 = s[m] / mtmp;
      ztest = e[m] / mtmp;
      sqds = s[q] / mtmp;
      rt = ((ztest0 + f) * (ztest0 - f) + ztest * ztest) / 2.0;
      ztest0 = f * ztest;
      ztest0 *= ztest0;
      if ((rt != 0.0) || (ztest0 != 0.0)) {
        ztest = sqrt(rt * rt + ztest0);
        if (rt < 0.0) {
          ztest = -ztest;
        }

        ztest = ztest0 / (rt + ztest);
      } else {
        ztest = 0.0;
      }

      f = (sqds + f) * (sqds - f) + ztest;
      ztest0 = sqds * (e[q] / mtmp);
      for (qjj = q + 1; qjj <= m + 1; qjj++) {
        eml_xrotg(&f, &ztest0, &ztest, &rt);
        if (qjj > q + 1) {
          e[qjj - 2] = f;
        }

        f = ztest * s[qjj - 1] + rt * e[qjj - 1];
        e[qjj - 1] = ztest * e[qjj - 1] - rt * s[qjj - 1];
        ztest0 = rt * s[qjj];
        s[qjj] *= ztest;
        s[qjj - 1] = f;
        eml_xrotg(&s[qjj - 1], &ztest0, &ztest, &rt);
        f = ztest * e[qjj - 1] + rt * s[qjj];
        s[qjj] = -rt * e[qjj - 1] + ztest * s[qjj];
        ztest0 = rt * e[qjj];
        e[qjj] *= ztest;
      }

      e[m] = f;
      iter++;
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
      }

      i = q + 1;
      while ((q + 1 < 8) && (s[q] < s[i])) {
        rt = s[q];
        s[q] = s[i];
        s[i] = rt;
        q = i;
        i++;
      }

      iter = 0;
      m--;
      break;
    }
  }

  memcpy(&U[0], &s[0], sizeof(double) << 3);
}

void svd(const double A[128], double U[8])
{
  double b_A[128];
  double s[8];
  double e[8];
  int i;
  double work[16];
  int q;
  int qs;
  boolean_T apply_transform;
  double ztest0;
  int qjj;
  int m;
  double ztest;
  double rt;
  int iter;
  double snorm;
  int32_T exitg3;
  boolean_T exitg2;
  double f;
  double varargin_1[5];
  double mtmp;
  boolean_T exitg1;
  double sqds;
  memcpy(&b_A[0], &A[0], sizeof(double) << 7);
  for (i = 0; i < 8; i++) {
    s[i] = 0.0;
    e[i] = 0.0;
  }

  memset(&work[0], 0, sizeof(double) << 4);
  for (q = 0; q < 8; q++) {
    qs = q + (q << 4);
    apply_transform = false;
    ztest0 = eml_xnrm2(16 - q, b_A, qs + 1);
    if (ztest0 > 0.0) {
      apply_transform = true;
      if (b_A[qs] < 0.0) {
        s[q] = -ztest0;
      } else {
        s[q] = ztest0;
      }

      if (fabs(s[q]) >= 1.0020841800044864E-292) {
        ztest0 = 1.0 / s[q];
        i = (qs - q) + 16;
        for (qjj = qs; qjj + 1 <= i; qjj++) {
          b_A[qjj] *= ztest0;
        }
      } else {
        i = (qs - q) + 16;
        for (qjj = qs; qjj + 1 <= i; qjj++) {
          b_A[qjj] /= s[q];
        }
      }

      b_A[qs]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0;
    }

    for (i = q + 1; i + 1 < 9; i++) {
      qjj = q + (i << 4);
      if (apply_transform) {
        eml_xaxpy(16 - q, -(eml_xdotc(16 - q, b_A, qs + 1, b_A, qjj + 1) / b_A[q
                            + (q << 4)]), qs + 1, b_A, qjj + 1);
      }

      e[i] = b_A[qjj];
    }

    if (q + 1 <= 6) {
      ztest0 = b_eml_xnrm2(7 - q, e, q + 2);
      if (ztest0 == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -ztest0;
        } else {
          e[q] = ztest0;
        }

        ztest0 = e[q];
        if (fabs(e[q]) >= 1.0020841800044864E-292) {
          ztest0 = 1.0 / e[q];
          for (qjj = q + 1; qjj + 1 < 9; qjj++) {
            e[qjj] *= ztest0;
          }
        } else {
          for (qjj = q + 1; qjj + 1 < 9; qjj++) {
            e[qjj] /= ztest0;
          }
        }

        e[q + 1]++;
        e[q] = -e[q];
        for (i = q + 1; i + 1 < 17; i++) {
          work[i] = 0.0;
        }

        for (i = q + 1; i + 1 < 9; i++) {
          b_eml_xaxpy(15 - q, e[i], b_A, (q + (i << 4)) + 2, work, q + 2);
        }

        for (i = q + 1; i + 1 < 9; i++) {
          c_eml_xaxpy(15 - q, -e[i] / e[q + 1], work, q + 2, b_A, (q + (i << 4))
                      + 2);
        }
      }
    }
  }

  m = 6;
  e[6] = b_A[118];
  e[7] = 0.0;
  for (q = 0; q < 8; q++) {
    ztest = e[q];
    if (s[q] != 0.0) {
      rt = fabs(s[q]);
      ztest0 = s[q] / rt;
      s[q] = rt;
      if (q + 1 < 8) {
        ztest = e[q] / ztest0;
      }
    }

    if ((q + 1 < 8) && (ztest != 0.0)) {
      rt = fabs(ztest);
      ztest0 = ztest;
      ztest = rt;
      s[q + 1] *= rt / ztest0;
    }

    e[q] = ztest;
  }

  iter = 0;
  snorm = 0.0;
  for (i = 0; i < 8; i++) {
    ztest0 = fabs(s[i]);
    ztest = fabs(e[i]);
    if ((ztest0 >= ztest) || rtIsNaN(ztest)) {
    } else {
      ztest0 = ztest;
    }

    if ((snorm >= ztest0) || rtIsNaN(ztest0)) {
    } else {
      snorm = ztest0;
    }
  }

  while ((m + 2 > 0) && (!(iter >= 75))) {
    i = m;
    do {
      exitg3 = 0;
      q = i + 1;
      if (i + 1 == 0) {
        exitg3 = 1;
      } else {
        ztest0 = fabs(e[i]);
        if ((ztest0 <= 2.2204460492503131E-16 * (fabs(s[i]) + fabs(s[i + 1]))) ||
            (ztest0 <= 1.0020841800044864E-292) || ((iter > 20) && (ztest0 <=
              2.2204460492503131E-16 * snorm))) {
          e[i] = 0.0;
          exitg3 = 1;
        } else {
          i--;
        }
      }
    } while (exitg3 == 0);

    if (i + 1 == m + 1) {
      i = 4;
    } else {
      qs = m + 2;
      qjj = m + 2;
      exitg2 = false;
      while ((!exitg2) && (qjj >= i + 1)) {
        qs = qjj;
        if (qjj == i + 1) {
          exitg2 = true;
        } else {
          ztest0 = 0.0;
          if (qjj < m + 2) {
            ztest0 = fabs(e[qjj - 1]);
          }

          if (qjj > i + 2) {
            ztest0 += fabs(e[qjj - 2]);
          }

          ztest = fabs(s[qjj - 1]);
          if ((ztest <= 2.2204460492503131E-16 * ztest0) || (ztest <=
               1.0020841800044864E-292)) {
            s[qjj - 1] = 0.0;
            exitg2 = true;
          } else {
            qjj--;
          }
        }
      }

      if (qs == i + 1) {
        i = 3;
      } else if (qs == m + 2) {
        i = 1;
      } else {
        i = 2;
        q = qs;
      }
    }

    switch (i) {
     case 1:
      f = e[m];
      e[m] = 0.0;
      for (qjj = m; qjj + 1 >= q + 1; qjj--) {
        ztest0 = s[qjj];
        eml_xrotg(&ztest0, &f, &ztest, &rt);
        s[qjj] = ztest0;
        if (qjj + 1 > q + 1) {
          f = -rt * e[qjj - 1];
          e[qjj - 1] *= ztest;
        }
      }
      break;

     case 2:
      f = e[q - 1];
      e[q - 1] = 0.0;
      while (q + 1 <= m + 2) {
        eml_xrotg(&s[q], &f, &ztest, &rt);
        f = -rt * e[q];
        e[q] *= ztest;
        q++;
      }
      break;

     case 3:
      varargin_1[0] = fabs(s[m + 1]);
      varargin_1[1] = fabs(s[m]);
      varargin_1[2] = fabs(e[m]);
      varargin_1[3] = fabs(s[q]);
      varargin_1[4] = fabs(e[q]);
      i = 1;
      mtmp = varargin_1[0];
      if (rtIsNaN(varargin_1[0])) {
        qjj = 2;
        exitg1 = false;
        while ((!exitg1) && (qjj < 6)) {
          i = qjj;
          if (!rtIsNaN(varargin_1[qjj - 1])) {
            mtmp = varargin_1[qjj - 1];
            exitg1 = true;
          } else {
            qjj++;
          }
        }
      }

      if (i < 5) {
        while (i + 1 < 6) {
          if (varargin_1[i] > mtmp) {
            mtmp = varargin_1[i];
          }

          i++;
        }
      }

      f = s[m + 1] / mtmp;
      ztest0 = s[m] / mtmp;
      ztest = e[m] / mtmp;
      sqds = s[q] / mtmp;
      rt = ((ztest0 + f) * (ztest0 - f) + ztest * ztest) / 2.0;
      ztest0 = f * ztest;
      ztest0 *= ztest0;
      if ((rt != 0.0) || (ztest0 != 0.0)) {
        ztest = sqrt(rt * rt + ztest0);
        if (rt < 0.0) {
          ztest = -ztest;
        }

        ztest = ztest0 / (rt + ztest);
      } else {
        ztest = 0.0;
      }

      f = (sqds + f) * (sqds - f) + ztest;
      ztest0 = sqds * (e[q] / mtmp);
      for (qjj = q + 1; qjj <= m + 1; qjj++) {
        eml_xrotg(&f, &ztest0, &ztest, &rt);
        if (qjj > q + 1) {
          e[qjj - 2] = f;
        }

        f = ztest * s[qjj - 1] + rt * e[qjj - 1];
        e[qjj - 1] = ztest * e[qjj - 1] - rt * s[qjj - 1];
        ztest0 = rt * s[qjj];
        s[qjj] *= ztest;
        s[qjj - 1] = f;
        eml_xrotg(&s[qjj - 1], &ztest0, &ztest, &rt);
        f = ztest * e[qjj - 1] + rt * s[qjj];
        s[qjj] = -rt * e[qjj - 1] + ztest * s[qjj];
        ztest0 = rt * e[qjj];
        e[qjj] *= ztest;
      }

      e[m] = f;
      iter++;
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
      }

      i = q + 1;
      while ((q + 1 < 8) && (s[q] < s[i])) {
        rt = s[q];
        s[q] = s[i];
        s[i] = rt;
        q = i;
        i++;
      }

      iter = 0;
      m--;
      break;
    }
  }

  memcpy(&U[0], &s[0], sizeof(double) << 3);
}

/* End of code generation (svd.c) */
