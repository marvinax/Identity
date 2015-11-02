/*
 * interp2.c
 *
 * Code generation for function 'interp2'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "interp2.h"
#include "getPowderAndQr_emxutil.h"
#include "TensorGriddedInterp.h"
#include "median.h"
#include "isplaid.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void interp2(const emxArray_real_T *varargin_1, const emxArray_real_T
             *varargin_2, const emxArray_real_T *varargin_3, const
             emxArray_real_T *varargin_4, const emxArray_real_T *varargin_5,
             emxArray_real_T *Vq)
{
  emxArray_real_T *v;
  int j;
  int khi;
  emxArray_real_T *b_v;
  unsigned int uv2[2];
  int k0;
  emxArray_real_T *b;
  emxArray_real_T *ix;
  int nInf;
  emxArray_real_T *b_b;
  emxArray_real_T *iy;
  int c_v[1];
  int d_v[1];
  emxArray_real_T b_varargin_5;
  emxArray_real_T e_v;
  emxArray_int32_T *ipos;
  emxArray_int32_T *idx;
  int c_varargin_5[1];
  int k;
  int nNaN;
  int nb;
  double x;
  int32_T exitg2;
  double absxk;
  int exponent;
  boolean_T p;
  int i10;
  int b_varargin_4[1];
  int32_T exitg1;
  int b_exponent;
  int i11;
  emxArray_real_T *uwi;
  int f_v[1];
  int g_v[1];
  emxInit_real_T(&v, 2);
  j = v->size[0] * v->size[1];
  v->size[0] = 1;
  v->size[1] = varargin_1->size[1];
  emxEnsureCapacity((emxArray__common *)v, j, (int)sizeof(double));
  for (khi = 0; khi + 1 <= varargin_1->size[1]; khi++) {
    v->data[khi] = varargin_1->data[varargin_1->size[0] * khi];
  }

  emxInit_real_T(&b_v, 2);
  j = b_v->size[0] * b_v->size[1];
  b_v->size[0] = 1;
  b_v->size[1] = varargin_2->size[0];
  emxEnsureCapacity((emxArray__common *)b_v, j, (int)sizeof(double));
  for (khi = 0; khi + 1 <= varargin_2->size[0]; khi++) {
    b_v->data[khi] = varargin_2->data[khi];
  }

  for (j = 0; j < 2; j++) {
    uv2[j] = (unsigned int)varargin_5->size[j];
  }

  j = Vq->size[0] * Vq->size[1];
  Vq->size[0] = (int)uv2[0];
  emxEnsureCapacity((emxArray__common *)Vq, j, (int)sizeof(double));
  j = Vq->size[0] * Vq->size[1];
  Vq->size[1] = (int)uv2[1];
  emxEnsureCapacity((emxArray__common *)Vq, j, (int)sizeof(double));
  k0 = (int)uv2[0] * (int)uv2[1];
  for (j = 0; j < k0; j++) {
    Vq->data[j] = 0.0;
  }

  if (isplaid(varargin_5, varargin_4)) {
    b_emxInit_real_T(&b, 1);
    b_emxInit_real_T(&ix, 1);
    k0 = varargin_5->size[0];
    khi = varargin_4->size[1];
    nInf = varargin_5->size[0];
    j = ix->size[0];
    ix->size[0] = nInf;
    emxEnsureCapacity((emxArray__common *)ix, j, (int)sizeof(double));
    for (j = 0; j < nInf; j++) {
      ix->data[j] = varargin_5->data[j];
    }

    j = b->size[0];
    b->size[0] = k0;
    emxEnsureCapacity((emxArray__common *)b, j, (int)sizeof(double));
    for (j = 0; j < k0; j++) {
      b->data[j] = ix->data[j];
    }

    emxFree_real_T(&ix);
    b_emxInit_real_T(&b_b, 1);
    emxInit_real_T(&iy, 2);
    k0 = varargin_4->size[1];
    j = iy->size[0] * iy->size[1];
    iy->size[0] = 1;
    iy->size[1] = k0;
    emxEnsureCapacity((emxArray__common *)iy, j, (int)sizeof(double));
    for (j = 0; j < k0; j++) {
      iy->data[iy->size[0] * j] = varargin_4->data[varargin_4->size[0] * j];
    }

    j = b_b->size[0];
    b_b->size[0] = khi;
    emxEnsureCapacity((emxArray__common *)b_b, j, (int)sizeof(double));
    for (j = 0; j < khi; j++) {
      b_b->data[j] = iy->data[j];
    }

    emxFree_real_T(&iy);
    c_v[0] = b_v->size[1];
    d_v[0] = v->size[1];
    b_varargin_5 = *b_v;
    b_varargin_5.size = (int *)&c_v;
    b_varargin_5.numDimensions = 1;
    e_v = *v;
    e_v.size = (int *)&d_v;
    e_v.numDimensions = 1;
    TensorGriddedInterp(&b_varargin_5, &e_v, varargin_3, b, b_b, Vq);
    emxFree_real_T(&b_b);
    emxFree_real_T(&b);
  } else {
    b_emxInit_real_T(&b, 1);
    emxInit_int32_T(&ipos, 1);
    emxInit_int32_T(&idx, 1);
    k0 = varargin_5->size[0] * varargin_5->size[1];
    khi = varargin_5->size[0] * varargin_5->size[1];
    j = ipos->size[0];
    ipos->size[0] = khi;
    emxEnsureCapacity((emxArray__common *)ipos, j, (int)sizeof(int));
    c_varargin_5[0] = varargin_5->size[0] * varargin_5->size[1];
    b_varargin_5 = *varargin_5;
    b_varargin_5.size = (int *)&c_varargin_5;
    b_varargin_5.numDimensions = 1;
    eml_sort_idx(&b_varargin_5, idx);
    khi = varargin_5->size[0] * varargin_5->size[1];
    j = b->size[0];
    b->size[0] = khi;
    emxEnsureCapacity((emxArray__common *)b, j, (int)sizeof(double));
    for (khi = 0; khi + 1 <= k0; khi++) {
      b->data[khi] = varargin_5->data[idx->data[khi] - 1];
    }

    khi = 0;
    while ((khi + 1 <= k0) && rtIsInf(b->data[khi]) && (b->data[khi] < 0.0)) {
      khi++;
    }

    k = khi;
    khi = varargin_5->size[0] * varargin_5->size[1];
    while ((khi >= 1) && rtIsNaN(b->data[khi - 1])) {
      khi--;
    }

    k0 = varargin_5->size[0] * varargin_5->size[1];
    nNaN = k0 - khi;
    while ((khi >= 1) && rtIsInf(b->data[khi - 1]) && (b->data[khi - 1] > 0.0))
    {
      khi--;
    }

    k0 = varargin_5->size[0] * varargin_5->size[1];
    nInf = (k0 - khi) - nNaN;
    nb = -1;
    if (k > 0) {
      nb = 0;
      for (j = 1; j <= k; j++) {
        ipos->data[idx->data[j - 1] - 1] = 1;
      }
    }

    khi = (k + khi) - k;
    while (k + 1 <= khi) {
      x = b->data[k];
      k0 = k;
      do {
        exitg2 = 0;
        k++;
        if (k + 1 > khi) {
          exitg2 = 1;
        } else {
          absxk = fabs(x / 2.0);
          if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
            if (absxk <= 2.2250738585072014E-308) {
              absxk = 4.94065645841247E-324;
            } else {
              frexp(absxk, &exponent);
              absxk = ldexp(1.0, exponent - 53);
            }
          } else {
            absxk = rtNaN;
          }

          if ((fabs(x - b->data[k]) < absxk) || (rtIsInf(b->data[k]) && rtIsInf
               (x) && ((b->data[k] > 0.0) == (x > 0.0)))) {
            p = true;
          } else {
            p = false;
          }

          if (!p) {
            exitg2 = 1;
          }
        }
      } while (exitg2 == 0);

      nb++;
      b->data[nb] = x;
      for (j = k0 + 1; j <= k; j++) {
        ipos->data[idx->data[j - 1] - 1] = nb + 1;
      }

      idx->data[nb] = idx->data[k0];
    }

    if (nInf > 0) {
      nb++;
      b->data[nb] = b->data[khi];
      for (j = 1; j <= nInf; j++) {
        ipos->data[idx->data[(khi + j) - 1] - 1] = nb + 1;
      }

      idx->data[nb] = idx->data[khi];
    }

    k = (khi + nInf) - 1;
    for (j = 1; j <= nNaN; j++) {
      nb++;
      b->data[nb] = b->data[k + j];
      ipos->data[idx->data[k + j] - 1] = nb + 1;
      idx->data[nb] = idx->data[k + j];
    }

    b_emxInit_real_T(&ix, 1);
    j = b->size[0];
    if (1 > nb + 1) {
      i10 = -1;
    } else {
      i10 = nb;
    }

    b->size[0] = i10 + 1;
    emxEnsureCapacity((emxArray__common *)b, j, (int)sizeof(double));
    j = ix->size[0];
    ix->size[0] = ipos->size[0];
    emxEnsureCapacity((emxArray__common *)ix, j, (int)sizeof(double));
    k0 = ipos->size[0];
    for (j = 0; j < k0; j++) {
      ix->data[j] = ipos->data[j];
    }

    b_emxInit_real_T(&b_b, 1);
    nInf = varargin_4->size[0] * varargin_4->size[1];
    khi = varargin_4->size[0] * varargin_4->size[1];
    j = ipos->size[0];
    ipos->size[0] = khi;
    emxEnsureCapacity((emxArray__common *)ipos, j, (int)sizeof(int));
    b_varargin_4[0] = varargin_4->size[0] * varargin_4->size[1];
    b_varargin_5 = *varargin_4;
    b_varargin_5.size = (int *)&b_varargin_4;
    b_varargin_5.numDimensions = 1;
    eml_sort_idx(&b_varargin_5, idx);
    khi = varargin_4->size[0] * varargin_4->size[1];
    j = b_b->size[0];
    b_b->size[0] = khi;
    emxEnsureCapacity((emxArray__common *)b_b, j, (int)sizeof(double));
    for (khi = 0; khi + 1 <= nInf; khi++) {
      b_b->data[khi] = varargin_4->data[idx->data[khi] - 1];
    }

    khi = 0;
    while ((khi + 1 <= nInf) && rtIsInf(b_b->data[khi]) && (b_b->data[khi] < 0.0))
    {
      khi++;
    }

    k = khi;
    khi = varargin_4->size[0] * varargin_4->size[1];
    while ((khi >= 1) && rtIsNaN(b_b->data[khi - 1])) {
      khi--;
    }

    nInf = varargin_4->size[0] * varargin_4->size[1];
    nNaN = nInf - khi;
    while ((khi >= 1) && rtIsInf(b_b->data[khi - 1]) && (b_b->data[khi - 1] >
            0.0)) {
      khi--;
    }

    nInf = varargin_4->size[0] * varargin_4->size[1];
    nInf = (nInf - khi) - nNaN;
    nb = -1;
    if (k > 0) {
      nb = 0;
      for (j = 1; j <= k; j++) {
        ipos->data[idx->data[j - 1] - 1] = 1;
      }
    }

    khi = (k + khi) - k;
    while (k + 1 <= khi) {
      x = b_b->data[k];
      k0 = k;
      do {
        exitg1 = 0;
        k++;
        if (k + 1 > khi) {
          exitg1 = 1;
        } else {
          absxk = fabs(x / 2.0);
          if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
            if (absxk <= 2.2250738585072014E-308) {
              absxk = 4.94065645841247E-324;
            } else {
              frexp(absxk, &b_exponent);
              absxk = ldexp(1.0, b_exponent - 53);
            }
          } else {
            absxk = rtNaN;
          }

          if ((fabs(x - b_b->data[k]) < absxk) || (rtIsInf(b_b->data[k]) &&
               rtIsInf(x) && ((b_b->data[k] > 0.0) == (x > 0.0)))) {
            p = true;
          } else {
            p = false;
          }

          if (!p) {
            exitg1 = 1;
          }
        }
      } while (exitg1 == 0);

      nb++;
      b_b->data[nb] = x;
      for (j = k0 + 1; j <= k; j++) {
        ipos->data[idx->data[j - 1] - 1] = nb + 1;
      }

      idx->data[nb] = idx->data[k0];
    }

    if (nInf > 0) {
      nb++;
      b_b->data[nb] = b_b->data[khi];
      for (j = 1; j <= nInf; j++) {
        ipos->data[idx->data[(khi + j) - 1] - 1] = nb + 1;
      }

      idx->data[nb] = idx->data[khi];
    }

    k = (khi + nInf) - 1;
    for (j = 1; j <= nNaN; j++) {
      nb++;
      b_b->data[nb] = b_b->data[k + j];
      ipos->data[idx->data[k + j] - 1] = nb + 1;
      idx->data[nb] = idx->data[k + j];
    }

    emxFree_int32_T(&idx);
    b_emxInit_real_T(&iy, 1);
    j = b_b->size[0];
    if (1 > nb + 1) {
      i11 = -1;
    } else {
      i11 = nb;
    }

    b_b->size[0] = i11 + 1;
    emxEnsureCapacity((emxArray__common *)b_b, j, (int)sizeof(double));
    j = iy->size[0];
    iy->size[0] = ipos->size[0];
    emxEnsureCapacity((emxArray__common *)iy, j, (int)sizeof(double));
    k0 = ipos->size[0];
    for (j = 0; j < k0; j++) {
      iy->data[j] = ipos->data[j];
    }

    emxFree_int32_T(&ipos);
    emxInit_real_T(&uwi, 2);
    f_v[0] = b_v->size[1];
    g_v[0] = v->size[1];
    b_varargin_5 = *b_v;
    b_varargin_5.size = (int *)&f_v;
    b_varargin_5.numDimensions = 1;
    e_v = *v;
    e_v.size = (int *)&g_v;
    e_v.numDimensions = 1;
    TensorGriddedInterp(&b_varargin_5, &e_v, varargin_3, b, b_b, uwi);
    j = (int)uv2[0] * (int)uv2[1];
    khi = 0;
    emxFree_real_T(&b_b);
    emxFree_real_T(&b);
    while (khi <= j - 1) {
      Vq->data[khi] = uwi->data[((int)ix->data[khi] + uwi->size[0] * ((int)
        iy->data[khi] - 1)) - 1];
      khi++;
    }

    emxFree_real_T(&uwi);
    emxFree_real_T(&iy);
    emxFree_real_T(&ix);
  }

  emxFree_real_T(&b_v);
  emxFree_real_T(&v);
}

/* End of code generation (interp2.c) */
