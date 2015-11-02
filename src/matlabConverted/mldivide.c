/*
 * mldivide.c
 *
 * Code generation for function 'mldivide'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "mldivide.h"
#include "normalizeControlPoints.h"
#include "getPowderAndQr_rtwutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Declarations */
static double c_eml_xnrm2(int n, const double x[128], int ix0);
static void eml_xswap(double x[128], int ix0, int iy0);

/* Function Definitions */
static double c_eml_xnrm2(int n, const double x[128], int ix0)
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

static void eml_xswap(double x[128], int ix0, int iy0)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 16; k++) {
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

void b_mldivide(const double A[9], const double B[9], double Y[9])
{
  double b_A[9];
  int r1;
  int r2;
  int r3;
  double maxval;
  double a21;
  int rtemp;
  memcpy(&b_A[0], &A[0], 9U * sizeof(double));
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = fabs(A[0]);
  a21 = fabs(A[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }

  if (fabs(A[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  b_A[r2] = A[r2] / A[r1];
  b_A[r3] /= b_A[r1];
  b_A[3 + r2] -= b_A[r2] * b_A[3 + r1];
  b_A[3 + r3] -= b_A[r3] * b_A[3 + r1];
  b_A[6 + r2] -= b_A[r2] * b_A[6 + r1];
  b_A[6 + r3] -= b_A[r3] * b_A[6 + r1];
  if (fabs(b_A[3 + r3]) > fabs(b_A[3 + r2])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  b_A[3 + r3] /= b_A[3 + r2];
  b_A[6 + r3] -= b_A[3 + r3] * b_A[6 + r2];
  for (rtemp = 0; rtemp < 3; rtemp++) {
    Y[3 * rtemp] = B[r1 + 3 * rtemp];
    Y[1 + 3 * rtemp] = B[r2 + 3 * rtemp] - Y[3 * rtemp] * b_A[r2];
    Y[2 + 3 * rtemp] = (B[r3 + 3 * rtemp] - Y[3 * rtemp] * b_A[r3]) - Y[1 + 3 *
      rtemp] * b_A[3 + r3];
    Y[2 + 3 * rtemp] /= b_A[6 + r3];
    Y[3 * rtemp] -= Y[2 + 3 * rtemp] * b_A[6 + r1];
    Y[1 + 3 * rtemp] -= Y[2 + 3 * rtemp] * b_A[6 + r2];
    Y[1 + 3 * rtemp] /= b_A[3 + r2];
    Y[3 * rtemp] -= Y[1 + 3 * rtemp] * b_A[3 + r1];
    Y[3 * rtemp] /= b_A[r1];
  }
}

void c_mldivide(const double A[9], const double B[3], double Y[3])
{
  double b_A[9];
  int r1;
  int r2;
  int r3;
  double maxval;
  double a21;
  int rtemp;
  memcpy(&b_A[0], &A[0], 9U * sizeof(double));
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = fabs(A[0]);
  a21 = fabs(A[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }

  if (fabs(A[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  b_A[r2] = A[r2] / A[r1];
  b_A[r3] /= b_A[r1];
  b_A[3 + r2] -= b_A[r2] * b_A[3 + r1];
  b_A[3 + r3] -= b_A[r3] * b_A[3 + r1];
  b_A[6 + r2] -= b_A[r2] * b_A[6 + r1];
  b_A[6 + r3] -= b_A[r3] * b_A[6 + r1];
  if (fabs(b_A[3 + r3]) > fabs(b_A[3 + r2])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  b_A[3 + r3] /= b_A[3 + r2];
  b_A[6 + r3] -= b_A[3 + r3] * b_A[6 + r2];
  Y[1] = B[r2] - B[r1] * b_A[r2];
  Y[2] = (B[r3] - B[r1] * b_A[r3]) - Y[1] * b_A[3 + r3];
  Y[2] /= b_A[6 + r3];
  Y[0] = B[r1] - Y[2] * b_A[6 + r1];
  Y[1] -= Y[2] * b_A[6 + r2];
  Y[1] /= b_A[3 + r2];
  Y[0] -= Y[1] * b_A[3 + r1];
  Y[0] /= b_A[r1];
}

void d_mldivide(const double A[36], double B[6])
{
  double b_A[36];
  signed char ipiv[6];
  int i45;
  int j;
  int c;
  int kAcol;
  int ix;
  double temp;
  int k;
  double s;
  int jy;
  int ijA;
  memcpy(&b_A[0], &A[0], 36U * sizeof(double));
  for (i45 = 0; i45 < 6; i45++) {
    ipiv[i45] = (signed char)(1 + i45);
  }

  for (j = 0; j < 5; j++) {
    c = j * 7;
    kAcol = 0;
    ix = c;
    temp = fabs(b_A[c]);
    for (k = 2; k <= 6 - j; k++) {
      ix++;
      s = fabs(b_A[ix]);
      if (s > temp) {
        kAcol = k - 1;
        temp = s;
      }
    }

    if (b_A[c + kAcol] != 0.0) {
      if (kAcol != 0) {
        ipiv[j] = (signed char)((j + kAcol) + 1);
        ix = j;
        kAcol += j;
        for (k = 0; k < 6; k++) {
          temp = b_A[ix];
          b_A[ix] = b_A[kAcol];
          b_A[kAcol] = temp;
          ix += 6;
          kAcol += 6;
        }
      }

      i45 = (c - j) + 6;
      for (jy = c + 1; jy + 1 <= i45; jy++) {
        b_A[jy] /= b_A[c];
      }
    }

    kAcol = c;
    jy = c + 6;
    for (k = 1; k <= 5 - j; k++) {
      temp = b_A[jy];
      if (b_A[jy] != 0.0) {
        ix = c + 1;
        i45 = (kAcol - j) + 12;
        for (ijA = 7 + kAcol; ijA + 1 <= i45; ijA++) {
          b_A[ijA] += b_A[ix] * -temp;
          ix++;
        }
      }

      jy += 6;
      kAcol += 6;
    }
  }

  for (kAcol = 0; kAcol < 5; kAcol++) {
    if (ipiv[kAcol] != kAcol + 1) {
      temp = B[kAcol];
      B[kAcol] = B[ipiv[kAcol] - 1];
      B[ipiv[kAcol] - 1] = temp;
    }
  }

  for (k = 0; k < 6; k++) {
    kAcol = 6 * k;
    if (B[k] != 0.0) {
      for (jy = k + 1; jy + 1 < 7; jy++) {
        B[jy] -= B[k] * b_A[jy + kAcol];
      }
    }
  }

  for (k = 5; k > -1; k += -1) {
    kAcol = 6 * k;
    if (B[k] != 0.0) {
      B[k] /= b_A[k + kAcol];
      for (jy = 0; jy + 1 <= k; jy++) {
        B[jy] -= B[k] * b_A[jy + kAcol];
      }
    }
  }
}

void e_mldivide(const double A[64], double B[8])
{
  double b_A[64];
  signed char ipiv[8];
  int i53;
  int j;
  int c;
  int kAcol;
  int ix;
  double temp;
  int k;
  double s;
  int jy;
  int ijA;
  memcpy(&b_A[0], &A[0], sizeof(double) << 6);
  for (i53 = 0; i53 < 8; i53++) {
    ipiv[i53] = (signed char)(1 + i53);
  }

  for (j = 0; j < 7; j++) {
    c = j * 9;
    kAcol = 0;
    ix = c;
    temp = fabs(b_A[c]);
    for (k = 1; k + 1 <= 8 - j; k++) {
      ix++;
      s = fabs(b_A[ix]);
      if (s > temp) {
        kAcol = k;
        temp = s;
      }
    }

    if (b_A[c + kAcol] != 0.0) {
      if (kAcol != 0) {
        ipiv[j] = (signed char)((j + kAcol) + 1);
        ix = j;
        kAcol += j;
        for (k = 0; k < 8; k++) {
          temp = b_A[ix];
          b_A[ix] = b_A[kAcol];
          b_A[kAcol] = temp;
          ix += 8;
          kAcol += 8;
        }
      }

      i53 = (c - j) + 8;
      for (jy = c + 1; jy + 1 <= i53; jy++) {
        b_A[jy] /= b_A[c];
      }
    }

    kAcol = c;
    jy = c + 8;
    for (k = 1; k <= 7 - j; k++) {
      temp = b_A[jy];
      if (b_A[jy] != 0.0) {
        ix = c + 1;
        i53 = (kAcol - j) + 16;
        for (ijA = 9 + kAcol; ijA + 1 <= i53; ijA++) {
          b_A[ijA] += b_A[ix] * -temp;
          ix++;
        }
      }

      jy += 8;
      kAcol += 8;
    }
  }

  for (kAcol = 0; kAcol < 7; kAcol++) {
    if (ipiv[kAcol] != kAcol + 1) {
      temp = B[kAcol];
      B[kAcol] = B[ipiv[kAcol] - 1];
      B[ipiv[kAcol] - 1] = temp;
    }
  }

  for (k = 0; k < 8; k++) {
    kAcol = k << 3;
    if (B[k] != 0.0) {
      for (jy = k + 1; jy + 1 < 9; jy++) {
        B[jy] -= B[k] * b_A[jy + kAcol];
      }
    }
  }

  for (k = 7; k > -1; k += -1) {
    kAcol = k << 3;
    if (B[k] != 0.0) {
      B[k] /= b_A[k + kAcol];
      for (jy = 0; jy + 1 <= k; jy++) {
        B[jy] -= B[k] * b_A[jy + kAcol];
      }
    }
  }
}

double eml_xnrm2(int n, const double x[128], int ix0)
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

void mldivide(const double A[128], const double B[16], double Y[8])
{
  double b_B[16];
  double b_A[128];
  double tau[8];
  signed char jpvt[8];
  double work[8];
  int i20;
  double vn1[8];
  double vn2[8];
  int k;
  int j;
  double tol;
  double rankR;
  int pvt;
  double absxk;
  double t;
  int i;
  int i_i;
  int ix;
  int i_ip1;
  int lastv;
  int lastc;
  boolean_T exitg2;
  int32_T exitg1;
  int ijA;
  memcpy(&b_B[0], &B[0], sizeof(double) << 4);
  memcpy(&b_A[0], &A[0], sizeof(double) << 7);
  for (i20 = 0; i20 < 8; i20++) {
    jpvt[i20] = (signed char)(1 + i20);
    work[i20] = 0.0;
  }

  k = 1;
  for (j = 0; j < 8; j++) {
    tol = 0.0;
    rankR = 2.2250738585072014E-308;
    for (pvt = k; pvt <= k + 15; pvt++) {
      absxk = fabs(A[pvt - 1]);
      if (absxk > rankR) {
        t = rankR / absxk;
        tol = 1.0 + tol * t * t;
        rankR = absxk;
      } else {
        t = absxk / rankR;
        tol += t * t;
      }
    }

    tol = rankR * sqrt(tol);
    vn1[j] = tol;
    vn2[j] = vn1[j];
    k += 16;
  }

  for (i = 0; i < 8; i++) {
    i_i = i + (i << 4);
    pvt = 0;
    if (8 - i > 1) {
      ix = i;
      tol = fabs(vn1[i]);
      for (k = 1; k + 1 <= 8 - i; k++) {
        ix++;
        rankR = fabs(vn1[ix]);
        if (rankR > tol) {
          pvt = k;
          tol = rankR;
        }
      }
    }

    pvt += i;
    if (pvt + 1 != i + 1) {
      eml_xswap(b_A, 1 + (pvt << 4), 1 + (i << 4));
      k = jpvt[pvt];
      jpvt[pvt] = jpvt[i];
      jpvt[i] = (signed char)k;
      vn1[pvt] = vn1[i];
      vn2[pvt] = vn2[i];
    }

    absxk = b_A[i_i];
    rankR = 0.0;
    tol = c_eml_xnrm2(15 - i, b_A, i_i + 2);
    if (tol != 0.0) {
      tol = rt_hypotd_snf(b_A[i_i], tol);
      if (b_A[i_i] >= 0.0) {
        tol = -tol;
      }

      if (fabs(tol) < 1.0020841800044864E-292) {
        pvt = 0;
        do {
          pvt++;
          i20 = i_i - i;
          for (k = i_i + 1; k + 1 <= i20 + 16; k++) {
            b_A[k] *= 9.9792015476736E+291;
          }

          tol *= 9.9792015476736E+291;
          absxk *= 9.9792015476736E+291;
        } while (!(fabs(tol) >= 1.0020841800044864E-292));

        tol = rt_hypotd_snf(absxk, c_eml_xnrm2(15 - i, b_A, i_i + 2));
        if (absxk >= 0.0) {
          tol = -tol;
        }

        rankR = (tol - absxk) / tol;
        absxk = 1.0 / (absxk - tol);
        i20 = i_i - i;
        for (k = i_i + 1; k + 1 <= i20 + 16; k++) {
          b_A[k] *= absxk;
        }

        for (k = 1; k <= pvt; k++) {
          tol *= 1.0020841800044864E-292;
        }

        absxk = tol;
      } else {
        rankR = (tol - b_A[i_i]) / tol;
        absxk = 1.0 / (b_A[i_i] - tol);
        i20 = i_i - i;
        for (k = i_i + 1; k + 1 <= i20 + 16; k++) {
          b_A[k] *= absxk;
        }

        absxk = tol;
      }
    }

    tau[i] = rankR;
    b_A[i_i] = absxk;
    if (i + 1 < 8) {
      absxk = b_A[i_i];
      b_A[i_i] = 1.0;
      i_ip1 = (i + ((i + 1) << 4)) + 1;
      if (tau[i] != 0.0) {
        lastv = 16 - i;
        pvt = i_i - i;
        while ((lastv > 0) && (b_A[pvt + 15] == 0.0)) {
          lastv--;
          pvt--;
        }

        lastc = 7 - i;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          pvt = i_ip1 + ((lastc - 1) << 4);
          j = pvt;
          do {
            exitg1 = 0;
            if (j <= (pvt + lastv) - 1) {
              if (b_A[j - 1] != 0.0) {
                exitg1 = 1;
              } else {
                j++;
              }
            } else {
              lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        lastc = 0;
      }

      if (lastv > 0) {
        if (lastc == 0) {
        } else {
          for (pvt = 1; pvt <= lastc; pvt++) {
            work[pvt - 1] = 0.0;
          }

          pvt = 0;
          i20 = i_ip1 + ((lastc - 1) << 4);
          for (k = i_ip1; k <= i20; k += 16) {
            ix = i_i;
            tol = 0.0;
            ijA = (k + lastv) - 1;
            for (j = k; j <= ijA; j++) {
              tol += b_A[j - 1] * b_A[ix];
              ix++;
            }

            work[pvt] += tol;
            pvt++;
          }
        }

        if (-tau[i] == 0.0) {
        } else {
          pvt = i_ip1 - 1;
          k = 0;
          for (j = 1; j <= lastc; j++) {
            if (work[k] != 0.0) {
              tol = work[k] * -tau[i];
              ix = i_i;
              i20 = lastv + pvt;
              for (ijA = pvt; ijA + 1 <= i20; ijA++) {
                b_A[ijA] += b_A[ix] * tol;
                ix++;
              }
            }

            k++;
            pvt += 16;
          }
        }
      }

      b_A[i_i] = absxk;
    }

    for (j = i + 1; j + 1 < 9; j++) {
      if (vn1[j] != 0.0) {
        tol = fabs(b_A[i + (j << 4)]) / vn1[j];
        tol = 1.0 - tol * tol;
        if (tol < 0.0) {
          tol = 0.0;
        }

        rankR = vn1[j] / vn2[j];
        rankR = tol * (rankR * rankR);
        if (rankR <= 1.4901161193847656E-8) {
          vn1[j] = eml_xnrm2(15 - i, b_A, (i + (j << 4)) + 2);
          vn2[j] = vn1[j];
        } else {
          vn1[j] *= sqrt(tol);
        }
      }
    }
  }

  rankR = 0.0;
  tol = 16.0 * fabs(b_A[0]) * 2.2204460492503131E-16;
  k = 0;
  while ((k < 8) && (!(fabs(b_A[k + (k << 4)]) <= tol))) {
    rankR++;
    k++;
  }

  memset(&Y[0], 0, sizeof(double) << 3);
  for (j = 0; j < 8; j++) {
    if (tau[j] != 0.0) {
      tol = b_B[j];
      for (i = 0; i <= 14 - j; i++) {
        pvt = (j + i) + 1;
        tol += b_A[pvt + (j << 4)] * b_B[pvt];
      }

      tol *= tau[j];
      if (tol != 0.0) {
        b_B[j] -= tol;
        for (i = 0; i <= 14 - j; i++) {
          pvt = (j + i) + 1;
          b_B[pvt] -= b_A[pvt + (j << 4)] * tol;
        }
      }
    }
  }

  for (i = 0; i < (int)rankR; i++) {
    Y[jpvt[i] - 1] = b_B[i];
  }

  for (j = 0; j < (int)-(1.0 + (-1.0 - rankR)); j++) {
    tol = rankR + -(double)j;
    Y[jpvt[(int)tol - 1] - 1] /= b_A[((int)tol + (((int)tol - 1) << 4)) - 1];
    for (i = 0; i <= (int)tol - 2; i++) {
      Y[jpvt[i] - 1] -= Y[jpvt[(int)tol - 1] - 1] * b_A[i + (((int)tol - 1) << 4)];
    }
  }
}

/* End of code generation (mldivide.c) */
