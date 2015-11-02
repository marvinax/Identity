/*
 * imwarp.c
 *
 * Code generation for function 'imwarp'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "imwarp.h"
#include "round.h"
#include "getPowderAndQr_emxutil.h"
#include "interp2d.h"
#include "imref2d.h"
#include "inv.h"
#include "meshgrid.h"
#include "projective2d.h"
#include "getPowderAndQr_rtwutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void b_imwarp(const emxArray_uint8_T *varargin_1, const double varargin_3_T[9],
              const double varargin_6_ImageSize[2], emxArray_uint8_T
              *outputImage)
{
  int n;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  emxArray_real_T *y;
  int k;
  int nm1d2;
  emxArray_real_T *b_y;
  emxArray_real_T *dstXIntrinsic;
  emxArray_real_T *dstYIntrinsic;
  double tinv[9];
  static const signed char iv16[3] = { 0, 0, 1 };

  emxArray_real_T *b_tinv;
  emxArray_real_T *c_tinv;
  emxArray_real_T *b_varargin_1;
  emxArray_real_T *b_outputImage;
  unsigned char u1;
  if (rtIsNaN(varargin_6_ImageSize[1])) {
    n = 0;
    anew = rtNaN;
    apnd = varargin_6_ImageSize[1];
  } else if (varargin_6_ImageSize[1] < 1.0) {
    n = -1;
    anew = 1.0;
    apnd = 0.0;
  } else if (rtIsInf(varargin_6_ImageSize[1])) {
    n = 0;
    anew = rtNaN;
    apnd = varargin_6_ImageSize[1];
  } else {
    anew = 1.0;
    ndbl = floor((varargin_6_ImageSize[1] - 1.0) + 0.5);
    apnd = 1.0 + ndbl;
    cdiff = (1.0 + ndbl) - varargin_6_ImageSize[1];
    if (fabs(cdiff) < 4.4408920985006262E-16 * varargin_6_ImageSize[1]) {
      ndbl++;
      apnd = varargin_6_ImageSize[1];
    } else if (cdiff > 0.0) {
      apnd = 1.0 + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    n = (int)ndbl - 1;
  }

  emxInit_real_T(&y, 2);
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n + 1;
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(double));
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

  if (rtIsNaN(varargin_6_ImageSize[0])) {
    n = 0;
    anew = rtNaN;
    apnd = varargin_6_ImageSize[0];
  } else if (varargin_6_ImageSize[0] < 1.0) {
    n = -1;
    anew = 1.0;
    apnd = 0.0;
  } else if (rtIsInf(varargin_6_ImageSize[0])) {
    n = 0;
    anew = rtNaN;
    apnd = varargin_6_ImageSize[0];
  } else {
    anew = 1.0;
    ndbl = floor((varargin_6_ImageSize[0] - 1.0) + 0.5);
    apnd = 1.0 + ndbl;
    cdiff = (1.0 + ndbl) - varargin_6_ImageSize[0];
    if (fabs(cdiff) < 4.4408920985006262E-16 * varargin_6_ImageSize[0]) {
      ndbl++;
      apnd = varargin_6_ImageSize[0];
    } else if (cdiff > 0.0) {
      apnd = 1.0 + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    n = (int)ndbl - 1;
  }

  emxInit_real_T(&b_y, 2);
  k = b_y->size[0] * b_y->size[1];
  b_y->size[0] = 1;
  b_y->size[1] = n + 1;
  emxEnsureCapacity((emxArray__common *)b_y, k, (int)sizeof(double));
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

  emxInit_real_T(&dstXIntrinsic, 2);
  emxInit_real_T(&dstYIntrinsic, 2);
  meshgrid(y, b_y, dstXIntrinsic, dstYIntrinsic);
  k = dstXIntrinsic->size[0] * dstXIntrinsic->size[1];
  emxEnsureCapacity((emxArray__common *)dstXIntrinsic, k, (int)sizeof(double));
  nm1d2 = dstXIntrinsic->size[0];
  k = dstXIntrinsic->size[1];
  nm1d2 *= k;
  emxFree_real_T(&b_y);
  emxFree_real_T(&y);
  for (k = 0; k < nm1d2; k++) {
    dstXIntrinsic->data[k] = 0.5 + (dstXIntrinsic->data[k] - 0.5);
  }

  k = dstYIntrinsic->size[0] * dstYIntrinsic->size[1];
  emxEnsureCapacity((emxArray__common *)dstYIntrinsic, k, (int)sizeof(double));
  nm1d2 = dstYIntrinsic->size[0];
  k = dstYIntrinsic->size[1];
  nm1d2 *= k;
  for (k = 0; k < nm1d2; k++) {
    dstYIntrinsic->data[k] = 0.5 + (dstYIntrinsic->data[k] - 0.5);
  }

  inv(varargin_3_T, tinv);
  for (k = 0; k < 3; k++) {
    tinv[6 + k] = iv16[k];
  }

  emxInit_real_T(&b_tinv, 2);
  k = b_tinv->size[0] * b_tinv->size[1];
  b_tinv->size[0] = dstXIntrinsic->size[0];
  b_tinv->size[1] = dstXIntrinsic->size[1];
  emxEnsureCapacity((emxArray__common *)b_tinv, k, (int)sizeof(double));
  nm1d2 = dstXIntrinsic->size[0] * dstXIntrinsic->size[1];
  for (k = 0; k < nm1d2; k++) {
    b_tinv->data[k] = (tinv[0] * dstXIntrinsic->data[k] + tinv[1] *
                       dstYIntrinsic->data[k]) + tinv[2];
  }

  emxInit_real_T(&c_tinv, 2);
  k = c_tinv->size[0] * c_tinv->size[1];
  c_tinv->size[0] = dstXIntrinsic->size[0];
  c_tinv->size[1] = dstXIntrinsic->size[1];
  emxEnsureCapacity((emxArray__common *)c_tinv, k, (int)sizeof(double));
  nm1d2 = dstXIntrinsic->size[0] * dstXIntrinsic->size[1];
  for (k = 0; k < nm1d2; k++) {
    c_tinv->data[k] = (tinv[3] * dstXIntrinsic->data[k] + tinv[4] *
                       dstYIntrinsic->data[k]) + tinv[5];
  }

  emxInit_real_T(&b_varargin_1, 2);
  imref2d_worldToIntrinsic(b_tinv, c_tinv, dstXIntrinsic, dstYIntrinsic);
  k = b_varargin_1->size[0] * b_varargin_1->size[1];
  b_varargin_1->size[0] = varargin_1->size[0];
  b_varargin_1->size[1] = varargin_1->size[1];
  emxEnsureCapacity((emxArray__common *)b_varargin_1, k, (int)sizeof(double));
  nm1d2 = varargin_1->size[0] * varargin_1->size[1];
  emxFree_real_T(&c_tinv);
  emxFree_real_T(&b_tinv);
  for (k = 0; k < nm1d2; k++) {
    b_varargin_1->data[k] = varargin_1->data[k];
  }

  emxInit_real_T(&b_outputImage, 2);
  interp2d(b_varargin_1, dstXIntrinsic, dstYIntrinsic, b_outputImage);
  k = outputImage->size[0] * outputImage->size[1];
  outputImage->size[0] = b_outputImage->size[0];
  outputImage->size[1] = b_outputImage->size[1];
  emxEnsureCapacity((emxArray__common *)outputImage, k, (int)sizeof(unsigned
    char));
  nm1d2 = b_outputImage->size[0] * b_outputImage->size[1];
  emxFree_real_T(&b_varargin_1);
  emxFree_real_T(&dstYIntrinsic);
  emxFree_real_T(&dstXIntrinsic);
  for (k = 0; k < nm1d2; k++) {
    anew = rt_roundd_snf(b_outputImage->data[k]);
    if (anew < 256.0) {
      if (anew >= 0.0) {
        u1 = (unsigned char)anew;
      } else {
        u1 = 0;
      }
    } else if (anew >= 256.0) {
      u1 = MAX_uint8_T;
    } else {
      u1 = 0;
    }

    outputImage->data[k] = u1;
  }

  emxFree_real_T(&b_outputImage);
}

void c_imwarp(const emxArray_real_T *varargin_1, const double varargin_3_T[9],
              const double varargin_6_ImageSize[2], emxArray_real_T *outputImage)
{
  int n;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  emxArray_real_T *y;
  int k;
  int nm1d2;
  emxArray_real_T *b_y;
  emxArray_real_T *dstXIntrinsic;
  emxArray_real_T *dstYIntrinsic;
  emxArray_real_T *r26;
  emxArray_real_T *r27;
  emxArray_real_T *srcXWorld;
  emxArray_real_T *srcYWorld;
  emxArray_real_T *r28;
  if (rtIsNaN(varargin_6_ImageSize[1])) {
    n = 0;
    anew = rtNaN;
    apnd = varargin_6_ImageSize[1];
  } else if (varargin_6_ImageSize[1] < 1.0) {
    n = -1;
    anew = 1.0;
    apnd = 0.0;
  } else if (rtIsInf(varargin_6_ImageSize[1])) {
    n = 0;
    anew = rtNaN;
    apnd = varargin_6_ImageSize[1];
  } else {
    anew = 1.0;
    ndbl = floor((varargin_6_ImageSize[1] - 1.0) + 0.5);
    apnd = 1.0 + ndbl;
    cdiff = (1.0 + ndbl) - varargin_6_ImageSize[1];
    if (fabs(cdiff) < 4.4408920985006262E-16 * varargin_6_ImageSize[1]) {
      ndbl++;
      apnd = varargin_6_ImageSize[1];
    } else if (cdiff > 0.0) {
      apnd = 1.0 + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    n = (int)ndbl - 1;
  }

  emxInit_real_T(&y, 2);
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n + 1;
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(double));
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

  if (rtIsNaN(varargin_6_ImageSize[0])) {
    n = 0;
    anew = rtNaN;
    apnd = varargin_6_ImageSize[0];
  } else if (varargin_6_ImageSize[0] < 1.0) {
    n = -1;
    anew = 1.0;
    apnd = 0.0;
  } else if (rtIsInf(varargin_6_ImageSize[0])) {
    n = 0;
    anew = rtNaN;
    apnd = varargin_6_ImageSize[0];
  } else {
    anew = 1.0;
    ndbl = floor((varargin_6_ImageSize[0] - 1.0) + 0.5);
    apnd = 1.0 + ndbl;
    cdiff = (1.0 + ndbl) - varargin_6_ImageSize[0];
    if (fabs(cdiff) < 4.4408920985006262E-16 * varargin_6_ImageSize[0]) {
      ndbl++;
      apnd = varargin_6_ImageSize[0];
    } else if (cdiff > 0.0) {
      apnd = 1.0 + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    n = (int)ndbl - 1;
  }

  emxInit_real_T(&b_y, 2);
  k = b_y->size[0] * b_y->size[1];
  b_y->size[0] = 1;
  b_y->size[1] = n + 1;
  emxEnsureCapacity((emxArray__common *)b_y, k, (int)sizeof(double));
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

  emxInit_real_T(&dstXIntrinsic, 2);
  emxInit_real_T(&dstYIntrinsic, 2);
  emxInit_real_T(&r26, 2);
  meshgrid(y, b_y, dstXIntrinsic, dstYIntrinsic);
  k = r26->size[0] * r26->size[1];
  r26->size[0] = dstXIntrinsic->size[0];
  r26->size[1] = dstXIntrinsic->size[1];
  emxEnsureCapacity((emxArray__common *)r26, k, (int)sizeof(double));
  nm1d2 = dstXIntrinsic->size[0] * dstXIntrinsic->size[1];
  emxFree_real_T(&b_y);
  emxFree_real_T(&y);
  for (k = 0; k < nm1d2; k++) {
    r26->data[k] = 0.5 + (dstXIntrinsic->data[k] - 0.5);
  }

  emxInit_real_T(&r27, 2);
  k = r27->size[0] * r27->size[1];
  r27->size[0] = dstYIntrinsic->size[0];
  r27->size[1] = dstYIntrinsic->size[1];
  emxEnsureCapacity((emxArray__common *)r27, k, (int)sizeof(double));
  nm1d2 = dstYIntrinsic->size[0] * dstYIntrinsic->size[1];
  for (k = 0; k < nm1d2; k++) {
    r27->data[k] = 0.5 + (dstYIntrinsic->data[k] - 0.5);
  }

  emxInit_real_T(&srcXWorld, 2);
  emxInit_real_T(&srcYWorld, 2);
  emxInit_real_T(&r28, 2);
  c_projective2d_transformPointsI(varargin_3_T, r26, r27, srcXWorld, srcYWorld);
  imref2d_worldToIntrinsic(srcXWorld, srcYWorld, dstXIntrinsic, dstYIntrinsic);
  interp2d(varargin_1, dstXIntrinsic, dstYIntrinsic, r28);
  k = outputImage->size[0] * outputImage->size[1];
  outputImage->size[0] = r28->size[0];
  outputImage->size[1] = r28->size[1];
  emxEnsureCapacity((emxArray__common *)outputImage, k, (int)sizeof(double));
  nm1d2 = r28->size[0] * r28->size[1];
  emxFree_real_T(&r27);
  emxFree_real_T(&r26);
  emxFree_real_T(&dstYIntrinsic);
  emxFree_real_T(&dstXIntrinsic);
  emxFree_real_T(&srcYWorld);
  emxFree_real_T(&srcXWorld);
  for (k = 0; k < nm1d2; k++) {
    outputImage->data[k] = r28->data[k];
  }

  emxFree_real_T(&r28);
}

void imwarp(const emxArray_uint8_T *varargin_1, const double varargin_3_T[9],
            const double varargin_6_ImageSize[2], emxArray_uint8_T *outputImage)
{
  int n;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  emxArray_real_T *y;
  int k;
  int nm1d2;
  emxArray_real_T *b_y;
  emxArray_real_T *dstXIntrinsic;
  emxArray_real_T *dstYIntrinsic;
  emxArray_real_T *r19;
  emxArray_real_T *r20;
  emxArray_real_T *b_outputImage;
  emxArray_real_T *srcYWorld;
  emxArray_real_T *b_varargin_1;
  emxArray_real_T *r21;
  unsigned char u0;
  if (rtIsNaN(varargin_6_ImageSize[1])) {
    n = 0;
    anew = rtNaN;
    apnd = varargin_6_ImageSize[1];
  } else if (varargin_6_ImageSize[1] < 1.0) {
    n = -1;
    anew = 1.0;
    apnd = 0.0;
  } else if (rtIsInf(varargin_6_ImageSize[1])) {
    n = 0;
    anew = rtNaN;
    apnd = varargin_6_ImageSize[1];
  } else {
    anew = 1.0;
    ndbl = floor((varargin_6_ImageSize[1] - 1.0) + 0.5);
    apnd = 1.0 + ndbl;
    cdiff = (1.0 + ndbl) - varargin_6_ImageSize[1];
    if (fabs(cdiff) < 4.4408920985006262E-16 * varargin_6_ImageSize[1]) {
      ndbl++;
      apnd = varargin_6_ImageSize[1];
    } else if (cdiff > 0.0) {
      apnd = 1.0 + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    n = (int)ndbl - 1;
  }

  emxInit_real_T(&y, 2);
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n + 1;
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(double));
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

  if (rtIsNaN(varargin_6_ImageSize[0])) {
    n = 0;
    anew = rtNaN;
    apnd = varargin_6_ImageSize[0];
  } else if (varargin_6_ImageSize[0] < 1.0) {
    n = -1;
    anew = 1.0;
    apnd = 0.0;
  } else if (rtIsInf(varargin_6_ImageSize[0])) {
    n = 0;
    anew = rtNaN;
    apnd = varargin_6_ImageSize[0];
  } else {
    anew = 1.0;
    ndbl = floor((varargin_6_ImageSize[0] - 1.0) + 0.5);
    apnd = 1.0 + ndbl;
    cdiff = (1.0 + ndbl) - varargin_6_ImageSize[0];
    if (fabs(cdiff) < 4.4408920985006262E-16 * varargin_6_ImageSize[0]) {
      ndbl++;
      apnd = varargin_6_ImageSize[0];
    } else if (cdiff > 0.0) {
      apnd = 1.0 + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    n = (int)ndbl - 1;
  }

  emxInit_real_T(&b_y, 2);
  k = b_y->size[0] * b_y->size[1];
  b_y->size[0] = 1;
  b_y->size[1] = n + 1;
  emxEnsureCapacity((emxArray__common *)b_y, k, (int)sizeof(double));
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

  emxInit_real_T(&dstXIntrinsic, 2);
  emxInit_real_T(&dstYIntrinsic, 2);
  emxInit_real_T(&r19, 2);
  meshgrid(y, b_y, dstXIntrinsic, dstYIntrinsic);
  k = r19->size[0] * r19->size[1];
  r19->size[0] = dstXIntrinsic->size[0];
  r19->size[1] = dstXIntrinsic->size[1];
  emxEnsureCapacity((emxArray__common *)r19, k, (int)sizeof(double));
  nm1d2 = dstXIntrinsic->size[0] * dstXIntrinsic->size[1];
  emxFree_real_T(&b_y);
  emxFree_real_T(&y);
  for (k = 0; k < nm1d2; k++) {
    r19->data[k] = 0.5 + (dstXIntrinsic->data[k] - 0.5);
  }

  emxInit_real_T(&r20, 2);
  k = r20->size[0] * r20->size[1];
  r20->size[0] = dstYIntrinsic->size[0];
  r20->size[1] = dstYIntrinsic->size[1];
  emxEnsureCapacity((emxArray__common *)r20, k, (int)sizeof(double));
  nm1d2 = dstYIntrinsic->size[0] * dstYIntrinsic->size[1];
  for (k = 0; k < nm1d2; k++) {
    r20->data[k] = 0.5 + (dstYIntrinsic->data[k] - 0.5);
  }

  emxInit_real_T(&b_outputImage, 2);
  emxInit_real_T(&srcYWorld, 2);
  emxInit_real_T(&b_varargin_1, 2);
  c_projective2d_transformPointsI(varargin_3_T, r19, r20, b_outputImage,
    srcYWorld);
  imref2d_worldToIntrinsic(b_outputImage, srcYWorld, dstXIntrinsic,
    dstYIntrinsic);
  k = b_varargin_1->size[0] * b_varargin_1->size[1];
  b_varargin_1->size[0] = varargin_1->size[0];
  b_varargin_1->size[1] = varargin_1->size[1];
  emxEnsureCapacity((emxArray__common *)b_varargin_1, k, (int)sizeof(double));
  nm1d2 = varargin_1->size[0] * varargin_1->size[1];
  emxFree_real_T(&r20);
  emxFree_real_T(&r19);
  emxFree_real_T(&srcYWorld);
  for (k = 0; k < nm1d2; k++) {
    b_varargin_1->data[k] = varargin_1->data[k];
  }

  emxInit_real_T(&r21, 2);
  interp2d(b_varargin_1, dstXIntrinsic, dstYIntrinsic, r21);
  k = b_outputImage->size[0] * b_outputImage->size[1];
  b_outputImage->size[0] = r21->size[0];
  b_outputImage->size[1] = r21->size[1];
  emxEnsureCapacity((emxArray__common *)b_outputImage, k, (int)sizeof(double));
  nm1d2 = r21->size[0] * r21->size[1];
  emxFree_real_T(&b_varargin_1);
  emxFree_real_T(&dstYIntrinsic);
  emxFree_real_T(&dstXIntrinsic);
  for (k = 0; k < nm1d2; k++) {
    b_outputImage->data[k] = r21->data[k];
  }

  emxFree_real_T(&r21);
  k = outputImage->size[0] * outputImage->size[1];
  outputImage->size[0] = b_outputImage->size[0];
  outputImage->size[1] = b_outputImage->size[1];
  emxEnsureCapacity((emxArray__common *)outputImage, k, (int)sizeof(unsigned
    char));
  nm1d2 = b_outputImage->size[0] * b_outputImage->size[1];
  for (k = 0; k < nm1d2; k++) {
    anew = rt_roundd_snf(b_outputImage->data[k]);
    if (anew < 256.0) {
      if (anew >= 0.0) {
        u0 = (unsigned char)anew;
      } else {
        u0 = 0;
      }
    } else if (anew >= 256.0) {
      u0 = MAX_uint8_T;
    } else {
      u0 = 0;
    }

    outputImage->data[k] = u0;
  }

  emxFree_real_T(&b_outputImage);
}

/* End of code generation (imwarp.c) */
