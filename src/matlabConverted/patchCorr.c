/*
 * patchCorr.c
 *
 * Code generation for function 'patchCorr'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "patchCorr.h"
#include "calcPearsonCorr.h"
#include "getPowderAndQr_emxutil.h"
#include "patchCorr_oneSearchMaskOnTheOther.h"
#include "meshgrid.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void b_patchCorr(const emxArray_uint8_T *trueImg, const unsigned char
                 testImg_data[], const int testImg_size[2], double sWinSize,
                 double *corrVal_max, double *bestMatchedPoint_x, double
                 *bestMatchedPoint_y, emxArray_real_T *corrMap_val,
                 emxArray_real_T *corrMap_x, emxArray_real_T *corrMap_y)
{
  int n;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  double absa;
  double absb;
  emxArray_real_T *y;
  int i30;
  int nm1d2;
  int k;
  emxArray_real_T *b_y;
  emxArray_real_T *corrVal;
  emxArray_real_T *vec_hori;
  emxArray_real_T *vec_vert;
  emxArray_real_T *im1;
  int32_T exitg2;
  int sz[2];
  double dv11[2];
  int iv7[2];
  int ix;
  double im2_data[2401];
  int b_im1[1];
  int im2[1];
  emxArray_real_T c_im1;
  emxArray_real_T b_im2_data;
  boolean_T exitg1;

  /*  This function calculates the correlation between two images that are not */
  /*  aligned but in the same scale. The precision of alignment is full pixel */
  /*  for now. */
  /*  Oct. 2014, Chau-Wai Wong */
  /* convertToIdx = @(range) range(1):range(2); */
  if (rtIsNaN(-sWinSize) || rtIsNaN(sWinSize)) {
    n = 0;
    anew = rtNaN;
    apnd = sWinSize;
  } else if (sWinSize < -sWinSize) {
    n = -1;
    anew = -sWinSize;
    apnd = sWinSize;
  } else if (rtIsInf(-sWinSize) || rtIsInf(sWinSize)) {
    n = 0;
    anew = rtNaN;
    apnd = sWinSize;
  } else {
    anew = -sWinSize;
    ndbl = floor((sWinSize - (-sWinSize)) + 0.5);
    apnd = -sWinSize + ndbl;
    cdiff = apnd - sWinSize;
    absa = fabs(-sWinSize);
    absb = fabs(sWinSize);
    if ((absa >= absb) || rtIsNaN(absb)) {
      absb = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      ndbl++;
      apnd = sWinSize;
    } else if (cdiff > 0.0) {
      apnd = -sWinSize + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl - 1;
    } else {
      n = -1;
    }
  }

  emxInit_real_T(&y, 2);
  i30 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n + 1;
  emxEnsureCapacity((emxArray__common *)y, i30, (int)sizeof(double));
  if (n + 1 > 0) {
    y->data[0] = anew;
    if (n + 1 > 1) {
      y->data[n] = apnd;
      nm1d2 = n / 2;
      for (k = 1; k < nm1d2; k++) {
        y->data[k] = anew + (double)k;
        y->data[n - k] = apnd - (double)k;
      }

      if (nm1d2 << 1 == n) {
        y->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        y->data[nm1d2] = anew + (double)nm1d2;
        y->data[nm1d2 + 1] = apnd - (double)nm1d2;
      }
    }
  }

  if (rtIsNaN(-sWinSize) || rtIsNaN(sWinSize)) {
    n = 0;
    anew = rtNaN;
    apnd = sWinSize;
  } else if (sWinSize < -sWinSize) {
    n = -1;
    anew = -sWinSize;
    apnd = sWinSize;
  } else if (rtIsInf(-sWinSize) || rtIsInf(sWinSize)) {
    n = 0;
    anew = rtNaN;
    apnd = sWinSize;
  } else {
    anew = -sWinSize;
    ndbl = floor((sWinSize - (-sWinSize)) + 0.5);
    apnd = -sWinSize + ndbl;
    cdiff = apnd - sWinSize;
    absa = fabs(-sWinSize);
    absb = fabs(sWinSize);
    if ((absa >= absb) || rtIsNaN(absb)) {
      absb = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      ndbl++;
      apnd = sWinSize;
    } else if (cdiff > 0.0) {
      apnd = -sWinSize + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl - 1;
    } else {
      n = -1;
    }
  }

  emxInit_real_T(&b_y, 2);
  i30 = b_y->size[0] * b_y->size[1];
  b_y->size[0] = 1;
  b_y->size[1] = n + 1;
  emxEnsureCapacity((emxArray__common *)b_y, i30, (int)sizeof(double));
  if (n + 1 > 0) {
    b_y->data[0] = anew;
    if (n + 1 > 1) {
      b_y->data[n] = apnd;
      nm1d2 = n / 2;
      for (k = 1; k < nm1d2; k++) {
        b_y->data[k] = anew + (double)k;
        b_y->data[n - k] = apnd - (double)k;
      }

      if (nm1d2 << 1 == n) {
        b_y->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        b_y->data[nm1d2] = anew + (double)nm1d2;
        b_y->data[nm1d2 + 1] = apnd - (double)nm1d2;
      }
    }
  }

  b_emxInit_real_T(&corrVal, 1);
  emxInit_real_T(&vec_hori, 2);
  emxInit_real_T(&vec_vert, 2);
  meshgrid(y, b_y, vec_hori, vec_vert);
  nm1d2 = vec_hori->size[0] * vec_hori->size[1];
  i30 = corrVal->size[0];
  corrVal->size[0] = nm1d2;
  emxEnsureCapacity((emxArray__common *)corrVal, i30, (int)sizeof(double));
  for (i30 = 0; i30 < nm1d2; i30++) {
    corrVal->data[i30] = 0.0;
  }

  n = 0;
  emxInit_real_T(&im1, 2);
  do {
    exitg2 = 0;
    nm1d2 = vec_hori->size[0] * vec_hori->size[1];
    if (n <= nm1d2 - 1) {
      anew = vec_hori->data[n] + sWinSize;
      ndbl = vec_vert->data[n] + sWinSize;
      sz[0] = 1;
      sz[1] = testImg_size[0];
      for (i30 = 0; i30 < 2; i30++) {
        dv11[i30] = (double)sz[i30] + ndbl;
      }

      convertToIdx(dv11, y);
      iv7[0] = 1;
      iv7[1] = testImg_size[1];
      for (i30 = 0; i30 < 2; i30++) {
        dv11[i30] = (double)iv7[i30] + anew;
      }

      convertToIdx(dv11, b_y);
      i30 = im1->size[0] * im1->size[1];
      im1->size[0] = y->size[1];
      im1->size[1] = b_y->size[1];
      emxEnsureCapacity((emxArray__common *)im1, i30, (int)sizeof(double));
      nm1d2 = b_y->size[1];
      for (i30 = 0; i30 < nm1d2; i30++) {
        k = y->size[1];
        for (ix = 0; ix < k; ix++) {
          im1->data[ix + im1->size[0] * i30] = trueImg->data[((int)y->data
            [y->size[0] * ix] + trueImg->size[0] * ((int)b_y->data[b_y->size[0] *
            i30] - 1)) - 1];
        }
      }

      nm1d2 = testImg_size[0] * testImg_size[1];
      for (i30 = 0; i30 < nm1d2; i30++) {
        im2_data[i30] = testImg_data[i30];
      }

      /*  corrVal(sIdx) = corr(im1(:), im2(:), 'type', 'Pearson'); */
      b_im1[0] = im1->size[0] * im1->size[1];
      im2[0] = testImg_size[0] * testImg_size[1];
      c_im1 = *im1;
      c_im1.size = (int *)&b_im1;
      c_im1.numDimensions = 1;
      b_im2_data.data = (double *)&im2_data;
      b_im2_data.size = (int *)&im2;
      b_im2_data.allocatedSize = 2401;
      b_im2_data.numDimensions = 1;
      b_im2_data.canFreeData = false;
      corrVal->data[n] = calcPearsonCorr(&c_im1, &b_im2_data);

      /*  30% faster */
      n++;
    } else {
      exitg2 = 1;
    }
  } while (exitg2 == 0);

  emxFree_real_T(&b_y);
  emxFree_real_T(&y);
  emxFree_real_T(&im1);

  /* surf(vec_hori, vec_vert, reshape(corrVal, size(vec_hori))); */
  /* plot(sort(corrVal, 'descend'), 'o') */
  nm1d2 = 1;
  n = corrVal->size[0];
  anew = corrVal->data[0];
  k = 0;
  if (corrVal->size[0] > 1) {
    if (rtIsNaN(corrVal->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        nm1d2 = ix;
        if (!rtIsNaN(corrVal->data[ix - 1])) {
          anew = corrVal->data[ix - 1];
          k = ix - 1;
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (nm1d2 < corrVal->size[0]) {
      while (nm1d2 + 1 <= n) {
        if (corrVal->data[nm1d2] > anew) {
          anew = corrVal->data[nm1d2];
          k = nm1d2;
        }

        nm1d2++;
      }
    }
  }

  *bestMatchedPoint_x = vec_hori->data[k];
  *bestMatchedPoint_y = vec_vert->data[k];
  for (i30 = 0; i30 < 2; i30++) {
    sz[i30] = vec_hori->size[i30];
  }

  i30 = corrMap_val->size[0] * corrMap_val->size[1];
  corrMap_val->size[0] = sz[0];
  corrMap_val->size[1] = sz[1];
  emxEnsureCapacity((emxArray__common *)corrMap_val, i30, (int)sizeof(double));
  for (k = 0; k + 1 <= corrVal->size[0]; k++) {
    corrMap_val->data[k] = corrVal->data[k];
  }

  emxFree_real_T(&corrVal);
  i30 = corrMap_x->size[0] * corrMap_x->size[1];
  corrMap_x->size[0] = vec_hori->size[0];
  corrMap_x->size[1] = vec_hori->size[1];
  emxEnsureCapacity((emxArray__common *)corrMap_x, i30, (int)sizeof(double));
  nm1d2 = vec_hori->size[0] * vec_hori->size[1];
  for (i30 = 0; i30 < nm1d2; i30++) {
    corrMap_x->data[i30] = vec_hori->data[i30];
  }

  emxFree_real_T(&vec_hori);
  i30 = corrMap_y->size[0] * corrMap_y->size[1];
  corrMap_y->size[0] = vec_vert->size[0];
  corrMap_y->size[1] = vec_vert->size[1];
  emxEnsureCapacity((emxArray__common *)corrMap_y, i30, (int)sizeof(double));
  nm1d2 = vec_vert->size[0] * vec_vert->size[1];
  for (i30 = 0; i30 < nm1d2; i30++) {
    corrMap_y->data[i30] = vec_vert->data[i30];
  }

  emxFree_real_T(&vec_vert);
  *corrVal_max = anew;
}

void patchCorr(const emxArray_uint8_T *trueImg, const unsigned char
               testImg_data[], const int testImg_size[2], double *corrVal_max,
               double *bestMatchedPoint_x, double *bestMatchedPoint_y, double
               corrMap_val[441], double corrMap_x[441], double corrMap_y[441])
{
  emxArray_real_T *im1;
  emxArray_real_T *r22;
  emxArray_real_T *r23;
  double im2_data[2401];
  double corrVal[441];
  int ixstart;
  signed char iv3[2];
  double dv10[2];
  int itmp;
  static const signed char iv4[441] = { -10, -9, -8, -7, -6, -5, -4, -3, -2, -1,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0,
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1,
    2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2,
    3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3,
    4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4,
    5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5,
    6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10 };

  signed char iv5[2];
  static const signed char iv6[441] = { -10, -10, -10, -10, -10, -10, -10, -10,
    -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -8,
    -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8,
    -8, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6,
    -6, -6, -6, -6, -6, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,
    -5, -5, -5, -5, -5, -5, -5, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4,
    -4, -4, -4, -4, -4, -4, -4, -4, -4, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3,
    -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };

  int ix;
  int loop_ub;
  int i28;
  int b_im1[1];
  int im2[1];
  emxArray_real_T c_im1;
  emxArray_real_T b_im2_data;
  boolean_T exitg1;
  static const signed char vec_hori[441] = { -10, -10, -10, -10, -10, -10, -10,
    -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8,
    -8, -8, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6,
    -6, -6, -6, -6, -6, -6, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,
    -5, -5, -5, -5, -5, -5, -5, -5, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4,
    -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -3, -3, -3, -3, -3, -3, -3, -3, -3,
    -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10 };

  static const signed char vec_vert[441] = { -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  /*  This function calculates the correlation between two images that are not */
  /*  aligned but in the same scale. The precision of alignment is full pixel */
  /*  for now. */
  /*  Oct. 2014, Chau-Wai Wong */
  /* convertToIdx = @(range) range(1):range(2); */
  emxInit_real_T(&im1, 2);
  emxInit_real_T(&r22, 2);
  emxInit_real_T(&r23, 2);
  for (ixstart = 0; ixstart < 441; ixstart++) {
    iv3[0] = 1;
    iv3[1] = (signed char)testImg_size[0];
    for (itmp = 0; itmp < 2; itmp++) {
      dv10[itmp] = (signed char)((iv3[itmp] + iv4[ixstart]) + 10);
    }

    convertToIdx(dv10, r22);
    iv5[0] = 1;
    iv5[1] = (signed char)testImg_size[1];
    for (itmp = 0; itmp < 2; itmp++) {
      dv10[itmp] = (signed char)((iv5[itmp] + iv6[ixstart]) + 10);
    }

    convertToIdx(dv10, r23);
    itmp = im1->size[0] * im1->size[1];
    im1->size[0] = r22->size[1];
    im1->size[1] = r23->size[1];
    emxEnsureCapacity((emxArray__common *)im1, itmp, (int)sizeof(double));
    ix = r23->size[1];
    for (itmp = 0; itmp < ix; itmp++) {
      loop_ub = r22->size[1];
      for (i28 = 0; i28 < loop_ub; i28++) {
        im1->data[i28 + im1->size[0] * itmp] = trueImg->data[((int)r22->data
          [r22->size[0] * i28] + trueImg->size[0] * ((int)r23->data[r23->size[0]
          * itmp] - 1)) - 1];
      }
    }

    ix = testImg_size[0] * testImg_size[1];
    for (itmp = 0; itmp < ix; itmp++) {
      im2_data[itmp] = testImg_data[itmp];
    }

    /*  corrVal(sIdx) = corr(im1(:), im2(:), 'type', 'Pearson'); */
    b_im1[0] = im1->size[0] * im1->size[1];
    im2[0] = testImg_size[0] * testImg_size[1];
    c_im1 = *im1;
    c_im1.size = (int *)&b_im1;
    c_im1.numDimensions = 1;
    b_im2_data.data = (double *)&im2_data;
    b_im2_data.size = (int *)&im2;
    b_im2_data.allocatedSize = 2401;
    b_im2_data.numDimensions = 1;
    b_im2_data.canFreeData = false;
    corrVal[ixstart] = calcPearsonCorr(&c_im1, &b_im2_data);

    /*  30% faster */
  }

  emxFree_real_T(&r23);
  emxFree_real_T(&r22);
  emxFree_real_T(&im1);

  /* surf(vec_hori, vec_vert, reshape(corrVal, size(vec_hori))); */
  /* plot(sort(corrVal, 'descend'), 'o') */
  ixstart = 1;
  *corrVal_max = corrVal[0];
  itmp = 0;
  if (rtIsNaN(corrVal[0])) {
    ix = 1;
    exitg1 = false;
    while ((!exitg1) && (ix + 1 < 442)) {
      ixstart = ix + 1;
      if (!rtIsNaN(corrVal[ix])) {
        *corrVal_max = corrVal[ix];
        itmp = ix;
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 441) {
    while (ixstart + 1 < 442) {
      if (corrVal[ixstart] > *corrVal_max) {
        *corrVal_max = corrVal[ixstart];
        itmp = ixstart;
      }

      ixstart++;
    }
  }

  *bestMatchedPoint_x = iv6[itmp];
  *bestMatchedPoint_y = iv4[itmp];
  for (ixstart = 0; ixstart < 441; ixstart++) {
    corrMap_val[ixstart] = corrVal[ixstart];
    corrMap_x[ixstart] = vec_hori[ixstart];
    corrMap_y[ixstart] = vec_vert[ixstart];
  }
}

/* End of code generation (patchCorr.c) */
