/*
 * removeReflectivePoints.c
 *
 * Code generation for function 'removeReflectivePoints'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "removeReflectivePoints.h"
#include "getPowderAndQr_emxutil.h"
#include "sum.h"
#include "hist.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Declarations */
static int c_compute_nones(const boolean_T x[40000]);

/* Function Definitions */
static int c_compute_nones(const boolean_T x[40000])
{
  int k;
  int i;
  k = 0;
  for (i = 0; i < 40000; i++) {
    if (x[i]) {
      k++;
    }
  }

  return k;
}

void c_eml_li_find(const boolean_T x[40000], emxArray_int32_T *y)
{
  int j;
  int i;
  j = y->size[0];
  y->size[0] = c_compute_nones(x);
  emxEnsureCapacity((emxArray__common *)y, j, (int)sizeof(int));
  j = 0;
  for (i = 0; i < 40000; i++) {
    if (x[i]) {
      y->data[j] = i + 1;
      j++;
    }
  }
}

void removeReflectivePoints(const double img[40000], const boolean_T mask[40000],
  boolean_T mask_reflective[40000], double *thres, double *cnt_reflectivePts)
{
  emxArray_real_T *imgLinear;
  emxArray_int32_T *r29;
  int j;
  int n;
  emxArray_real_T *histImg;
  short outsz[2];
  double extremum_data[256];
  int iindx_data[256];
  int vstride;
  int ix;
  int iy;
  int ixstart;
  int ixstop;
  double cntThres;
  int itmp;
  int cindx;
  int b_ix;
  boolean_T exitg2;
  int indx_data[256];
  emxArray_real_T *r30;
  double diffHist_data[256];
  boolean_T exitg1;
  double i;
  b_emxInit_real_T(&imgLinear, 1);
  emxInit_int32_T(&r29, 1);

  /*  This function identify reflective points and indicate them by a mask */
  /*  Reflective points corresponds to the rising tail of histogram of */
  /*  luminance channel of the image. */
  /*  Chau-Wai Wong, Nov. 2014 */
  c_eml_li_find(mask, r29);
  j = imgLinear->size[0];
  imgLinear->size[0] = r29->size[0];
  emxEnsureCapacity((emxArray__common *)imgLinear, j, (int)sizeof(double));
  n = r29->size[0];
  for (j = 0; j < n; j++) {
    imgLinear->data[j] = img[r29->data[j] - 1];
  }

  emxFree_int32_T(&r29);
  emxInit_real_T(&histImg, 2);
  hist(imgLinear, histImg);
  emxFree_real_T(&imgLinear);
  for (j = 0; j < 2; j++) {
    outsz[j] = (short)histImg->size[j];
  }

  n = outsz[0];
  for (j = 0; j < n; j++) {
    iindx_data[j] = 1;
  }

  n = histImg->size[1];
  vstride = histImg->size[0];
  ix = 0;
  iy = -1;
  for (j = 1; j <= vstride; j++) {
    ix++;
    ixstart = ix;
    ixstop = ix + (n - 1) * vstride;
    cntThres = histImg->data[ix - 1];
    itmp = 1;
    if (n > 1) {
      cindx = 1;
      if (rtIsNaN(histImg->data[ix - 1])) {
        b_ix = ix + vstride;
        exitg2 = false;
        while ((!exitg2) && (b_ix <= ixstop)) {
          cindx++;
          ixstart = b_ix;
          if (!rtIsNaN(histImg->data[b_ix - 1])) {
            cntThres = histImg->data[b_ix - 1];
            itmp = cindx;
            exitg2 = true;
          } else {
            b_ix += vstride;
          }
        }
      }

      if (ixstart < ixstop) {
        for (b_ix = ixstart + vstride; b_ix <= ixstop; b_ix += vstride) {
          cindx++;
          if (histImg->data[b_ix - 1] > cntThres) {
            cntThres = histImg->data[b_ix - 1];
            itmp = cindx;
          }
        }
      }
    }

    iy++;
    extremum_data[iy] = cntThres;
    iindx_data[iy] = itmp;
  }

  n = outsz[0];
  for (j = 0; j < n; j++) {
    indx_data[j] = iindx_data[j];
  }

  j = histImg->size[0] * histImg->size[1];
  if (2 > j) {
    vstride = 0;
    j = 0;
  } else {
    vstride = 1;
  }

  emxInit_real_T(&r30, 2);
  ix = r30->size[0] * r30->size[1];
  r30->size[0] = 1;
  r30->size[1] = (j - vstride) + 1;
  emxEnsureCapacity((emxArray__common *)r30, ix, (int)sizeof(double));
  n = j - vstride;
  for (ix = 0; ix < n; ix++) {
    r30->data[r30->size[0] * ix] = histImg->data[vstride + ix];
  }

  r30->data[r30->size[0] * (j - vstride)] = histImg->data[histImg->size[0] *
    histImg->size[1] - 1];
  n = r30->size[0] * r30->size[1];
  for (j = 0; j < n; j++) {
    diffHist_data[j] = r30->data[j] - histImg->data[j];
  }

  emxFree_real_T(&r30);
  cntThres = 0.1 * extremum_data[outsz[0] - 1];
  if ((double)indx_data[outsz[0] - 1] - 1.0 == 255.0) {
    /*  if no tail to be cut */
    *thres = 255.0;
    memcpy(&mask_reflective[0], &mask[0], 40000U * sizeof(boolean_T));
    *cnt_reflectivePts = 0.0;
  } else {
    /*  cut the tail starting from the right point of the peak point */
    ix = 0;
    iy = -1;
    if ((0 == histImg->size[0]) || (0 == histImg->size[1])) {
      vstride = 0;
    } else {
      n = histImg->size[0];
      vstride = histImg->size[1];
      if (n >= vstride) {
        vstride = n;
      }
    }

    j = (int)((double)vstride + (1.0 - ((double)indx_data[outsz[0] - 1] + 1.0)));
    n = 0;
    exitg1 = false;
    while ((!exitg1) && (n <= j - 1)) {
      i = ((double)indx_data[outsz[0] - 1] + 1.0) + (double)n;
      if ((histImg->data[(int)i - 1] < cntThres) && ((diffHist_data[(int)i - 1] >
            0.0) || (histImg->data[(int)i - 1] == 0.0))) {
        ix = 1;
        iy = (int)i;
        exitg1 = true;
      } else {
        n++;
      }
    }

    if (ix == 1) {
      *thres = (double)iy - 1.0;
      for (j = 0; j < 40000; j++) {
        mask_reflective[j] = ((img[j] <= (double)iy - 1.0) && mask[j]);
      }

      *cnt_reflectivePts = c_sum(mask) - c_sum(mask_reflective);
    } else {
      *thres = 255.0;
      memcpy(&mask_reflective[0], &mask[0], 40000U * sizeof(boolean_T));
      *cnt_reflectivePts = 0.0;
    }
  }

  emxFree_real_T(&histImg);
}

/* End of code generation (removeReflectivePoints.c) */
