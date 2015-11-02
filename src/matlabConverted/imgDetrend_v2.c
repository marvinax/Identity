/*
 * imgDetrend_v2.c
 *
 * Code generation for function 'imgDetrend_v2'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "imgDetrend_v2.h"
#include "median.h"
#include "getPowderAndQr_emxutil.h"
#include "rdivide.h"
#include "mean.h"
#include "power.h"
#include "ransacFit_quad.h"
#include "meshgrid.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void b_eml_xgemm(int m, int n, const emxArray_real_T *A, int lda, const double
                 B_data[], emxArray_real_T *C, int ldc)
{
  int ar;
  int ic;
  int br;
  int ib;
  int ia;
  if ((m == 0) || (n == 0)) {
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
        if (B_data[ib] != 0.0) {
          ia = ar;
          for (ic = 0; ic + 1 <= m; ic++) {
            ia++;
            C->data[ic] += B_data[ib] * A->data[ia];
          }
        }

        ar += lda;
      }

      br += 6;
      ar = ldc;
    }
  }
}

void imgDetrend_v2(const emxArray_real_T *img, emxArray_real_T *diffPlane,
                   emxArray_real_T *scalerPlane, emxArray_real_T *fittedPlane,
                   double *minErr)
{
  int n;
  int apnd;
  int ndbl;
  int cdiff;
  int absb;
  double yRange_topLeft_data[156];
  int b_n;
  double xRange_topLeft_data[156];
  emxArray_real_T *imgF;
  int i3;
  int idxY;
  emxArray_real_T *b_img;
  emxArray_real_T *c_img;
  double y;
  int idxX;
  int img_idx_0;
  int unnamed_idx_0;
  int i4;
  double val;
  int idx_y_size[2];
  double idx_y_data[156];
  int idx_x_size[2];
  double idx_x_data[156];
  emxArray_real_T *gx;
  emxArray_real_T *gy;
  emxArray_real_T b_idx_x_data;
  emxArray_real_T b_idx_y_data;
  emxArray_real_T *b_y;
  emxArray_real_T *c_y;
  emxArray_real_T *maskF;
  emxArray_real_T *r0;
  emxArray_real_T *gx_full;
  emxArray_real_T *gy_full;
  int best_beta_hat_size[2];
  double best_beta_hat_data[6];
  emxArray_real_T *r1;
  emxArray_real_T *b_gx_full;
  int c_gx_full[1];
  emxArray_real_T *r2;
  emxArray_real_T *r3;
  emxArray_real_T *b_gy_full;
  int c_gy_full[1];
  emxArray_real_T *r4;
  emxArray_real_T *r5;
  emxArray_real_T *r6;
  emxArray_real_T *a;
  emxArray_real_T *y_hat;
  short sz_idx_0;
  short sz_idx_1;
  int b_fittedPlane[1];
  boolean_T exitg1;
  emxArray_real_T *r7;

  /*  Detrend the input image */
  /*  Chau-Wai Wong, Nov. 2014 */
  /*  Const def */
  if (img->size[0] - 63 < 1) {
    n = -1;
    apnd = img->size[0] - 63;
  } else {
    ndbl = (int)floor(((((double)img->size[0] - 64.0) + 1.0) - 1.0) / 64.0 + 0.5);
    apnd = (ndbl << 6) + 1;
    cdiff = (apnd - img->size[0]) + 63;
    absb = (int)fabs(((double)img->size[0] - 64.0) + 1.0);
    if (1 >= absb) {
      absb = 1;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * (double)absb) {
      ndbl++;
      apnd = img->size[0] - 63;
    } else if (cdiff > 0) {
      apnd = 1 + ((ndbl - 1) << 6);
    } else {
      ndbl++;
    }

    n = ndbl - 1;
  }

  if (n + 1 > 0) {
    yRange_topLeft_data[0] = 1.0;
    if (n + 1 > 1) {
      yRange_topLeft_data[n] = apnd;
      ndbl = n / 2;
      for (absb = 1; absb < ndbl; absb++) {
        cdiff = absb << 6;
        yRange_topLeft_data[absb] = 1.0 + (double)cdiff;
        yRange_topLeft_data[n - absb] = apnd - cdiff;
      }

      if (ndbl << 1 == n) {
        yRange_topLeft_data[ndbl] = (1.0 + (double)apnd) / 2.0;
      } else {
        cdiff = ndbl << 6;
        yRange_topLeft_data[ndbl] = 1.0 + (double)cdiff;
        yRange_topLeft_data[ndbl + 1] = apnd - cdiff;
      }
    }
  }

  if (img->size[1] - 63 < 1) {
    b_n = -1;
    apnd = img->size[1] - 63;
  } else {
    ndbl = (int)floor(((((double)img->size[1] - 64.0) + 1.0) - 1.0) / 64.0 + 0.5);
    apnd = (ndbl << 6) + 1;
    cdiff = (apnd - img->size[1]) + 63;
    absb = (int)fabs(((double)img->size[1] - 64.0) + 1.0);
    if (1 >= absb) {
      absb = 1;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * (double)absb) {
      ndbl++;
      apnd = img->size[1] - 63;
    } else if (cdiff > 0) {
      apnd = 1 + ((ndbl - 1) << 6);
    } else {
      ndbl++;
    }

    b_n = ndbl - 1;
  }

  if (b_n + 1 > 0) {
    xRange_topLeft_data[0] = 1.0;
    if (b_n + 1 > 1) {
      xRange_topLeft_data[b_n] = apnd;
      ndbl = b_n / 2;
      for (absb = 1; absb < ndbl; absb++) {
        cdiff = absb << 6;
        xRange_topLeft_data[absb] = 1.0 + (double)cdiff;
        xRange_topLeft_data[b_n - absb] = apnd - cdiff;
      }

      if (ndbl << 1 == b_n) {
        xRange_topLeft_data[ndbl] = (1.0 + (double)apnd) / 2.0;
      } else {
        cdiff = ndbl << 6;
        xRange_topLeft_data[ndbl] = 1.0 + (double)cdiff;
        xRange_topLeft_data[ndbl + 1] = apnd - cdiff;
      }
    }
  }

  emxInit_real_T(&imgF, 2);
  i3 = imgF->size[0] * imgF->size[1];
  imgF->size[0] = n + 1;
  emxEnsureCapacity((emxArray__common *)imgF, i3, (int)sizeof(double));
  i3 = imgF->size[0] * imgF->size[1];
  imgF->size[1] = b_n + 1;
  emxEnsureCapacity((emxArray__common *)imgF, i3, (int)sizeof(double));
  ndbl = (n + 1) * (b_n + 1);
  for (i3 = 0; i3 < ndbl; i3++) {
    imgF->data[i3] = 0.0;
  }

  /*  for y = yRange_topLeft */
  idxY = 0;
  b_emxInit_real_T(&b_img, 1);
  emxInit_real_T(&c_img, 2);
  while (idxY <= n) {
    y = yRange_topLeft_data[idxY];

    /* for x = xRange_topLeft */
    for (idxX = 0; idxX <= b_n; idxX++) {
      if (y > (y + 64.0) - 1.0) {
        i3 = 0;
        absb = 0;
      } else {
        i3 = (int)y - 1;
        absb = (int)y + 63;
      }

      if (xRange_topLeft_data[idxX] > (xRange_topLeft_data[idxX] + 64.0) - 1.0)
      {
        img_idx_0 = 0;
        apnd = 0;
      } else {
        img_idx_0 = (int)xRange_topLeft_data[idxX] - 1;
        apnd = (int)((xRange_topLeft_data[idxX] + 64.0) - 1.0);
      }

      unnamed_idx_0 = c_img->size[0] * c_img->size[1];
      c_img->size[0] = absb - i3;
      c_img->size[1] = apnd - img_idx_0;
      emxEnsureCapacity((emxArray__common *)c_img, unnamed_idx_0, (int)sizeof
                        (double));
      ndbl = apnd - img_idx_0;
      for (unnamed_idx_0 = 0; unnamed_idx_0 < ndbl; unnamed_idx_0++) {
        cdiff = absb - i3;
        for (i4 = 0; i4 < cdiff; i4++) {
          c_img->data[i4 + c_img->size[0] * unnamed_idx_0] = img->data[(i3 + i4)
            + img->size[0] * (img_idx_0 + unnamed_idx_0)];
        }
      }

      unnamed_idx_0 = (absb - i3) * (apnd - img_idx_0);
      i3 = b_img->size[0];
      b_img->size[0] = unnamed_idx_0;
      emxEnsureCapacity((emxArray__common *)b_img, i3, (int)sizeof(double));
      for (i3 = 0; i3 < unnamed_idx_0; i3++) {
        b_img->data[i3] = c_img->data[i3];
      }

      val = median(b_img);
      imgF->data[idxY + imgF->size[0] * idxX] = val;
    }

    idxY++;
  }

  emxFree_real_T(&c_img);
  emxFree_real_T(&b_img);
  idx_y_size[0] = 1;
  idx_y_size[1] = n + 1;
  ndbl = n + 1;
  for (i3 = 0; i3 < ndbl; i3++) {
    idx_y_data[i3] = yRange_topLeft_data[i3] + 31.5;
  }

  idx_x_size[0] = 1;
  idx_x_size[1] = b_n + 1;
  ndbl = b_n + 1;
  for (i3 = 0; i3 < ndbl; i3++) {
    idx_x_data[i3] = xRange_topLeft_data[i3] + 31.5;
  }

  emxInit_real_T(&gx, 2);
  emxInit_real_T(&gy, 2);
  b_idx_x_data.data = (double *)&idx_x_data;
  b_idx_x_data.size = (int *)&idx_x_size;
  b_idx_x_data.allocatedSize = 156;
  b_idx_x_data.numDimensions = 2;
  b_idx_x_data.canFreeData = false;
  b_idx_y_data.data = (double *)&idx_y_data;
  b_idx_y_data.size = (int *)&idx_y_size;
  b_idx_y_data.allocatedSize = 156;
  b_idx_y_data.numDimensions = 2;
  b_idx_y_data.canFreeData = false;
  meshgrid(&b_idx_x_data, &b_idx_y_data, gx, gy);
  if (img->size[1] < 1) {
    n = -1;
    apnd = 0;
  } else {
    ndbl = (int)floor(((double)img->size[1] - 1.0) + 0.5);
    apnd = ndbl + 1;
    cdiff = (ndbl - img->size[1]) + 1;
    absb = img->size[1];
    if (fabs(cdiff) < 4.4408920985006262E-16 * (double)absb) {
      ndbl++;
      apnd = img->size[1];
    } else if (cdiff > 0) {
      apnd = ndbl;
    } else {
      ndbl++;
    }

    n = ndbl - 1;
  }

  emxInit_real_T(&b_y, 2);
  i3 = b_y->size[0] * b_y->size[1];
  b_y->size[0] = 1;
  b_y->size[1] = n + 1;
  emxEnsureCapacity((emxArray__common *)b_y, i3, (int)sizeof(double));
  if (n + 1 > 0) {
    b_y->data[0] = 1.0;
    if (n + 1 > 1) {
      b_y->data[n] = apnd;
      ndbl = n / 2;
      for (absb = 1; absb < ndbl; absb++) {
        b_y->data[absb] = 1.0 + (double)absb;
        b_y->data[n - absb] = apnd - absb;
      }

      if (ndbl << 1 == n) {
        b_y->data[ndbl] = (1.0 + (double)apnd) / 2.0;
      } else {
        b_y->data[ndbl] = 1.0 + (double)ndbl;
        b_y->data[ndbl + 1] = apnd - ndbl;
      }
    }
  }

  if (img->size[0] < 1) {
    n = -1;
    apnd = 0;
  } else {
    ndbl = (int)floor(((double)img->size[0] - 1.0) + 0.5);
    apnd = ndbl + 1;
    cdiff = (ndbl - img->size[0]) + 1;
    absb = img->size[0];
    if (fabs(cdiff) < 4.4408920985006262E-16 * (double)absb) {
      ndbl++;
      apnd = img->size[0];
    } else if (cdiff > 0) {
      apnd = ndbl;
    } else {
      ndbl++;
    }

    n = ndbl - 1;
  }

  emxInit_real_T(&c_y, 2);
  i3 = c_y->size[0] * c_y->size[1];
  c_y->size[0] = 1;
  c_y->size[1] = n + 1;
  emxEnsureCapacity((emxArray__common *)c_y, i3, (int)sizeof(double));
  if (n + 1 > 0) {
    c_y->data[0] = 1.0;
    if (n + 1 > 1) {
      c_y->data[n] = apnd;
      ndbl = n / 2;
      for (absb = 1; absb < ndbl; absb++) {
        c_y->data[absb] = 1.0 + (double)absb;
        c_y->data[n - absb] = apnd - absb;
      }

      if (ndbl << 1 == n) {
        c_y->data[ndbl] = (1.0 + (double)apnd) / 2.0;
      } else {
        c_y->data[ndbl] = 1.0 + (double)ndbl;
        c_y->data[ndbl + 1] = apnd - ndbl;
      }
    }
  }

  emxInit_real_T(&maskF, 2);
  b_emxInit_real_T(&r0, 1);
  emxInit_real_T(&gx_full, 2);
  emxInit_real_T(&gy_full, 2);
  meshgrid(b_y, c_y, gx_full, gy_full);
  ransacFit_quad(gx, gy, imgF, maskF, best_beta_hat_data, best_beta_hat_size,
                 minErr);
  i3 = r0->size[0];
  r0->size[0] = gx_full->size[0] * gx_full->size[1];
  emxEnsureCapacity((emxArray__common *)r0, i3, (int)sizeof(double));
  ndbl = gx_full->size[0] * gx_full->size[1];
  emxFree_real_T(&c_y);
  emxFree_real_T(&b_y);
  emxFree_real_T(&gy);
  emxFree_real_T(&maskF);
  emxFree_real_T(&imgF);
  for (i3 = 0; i3 < ndbl; i3++) {
    r0->data[i3] = gx_full->data[i3];
  }

  b_emxInit_real_T(&r1, 1);
  i3 = r1->size[0];
  r1->size[0] = gy_full->size[0] * gy_full->size[1];
  emxEnsureCapacity((emxArray__common *)r1, i3, (int)sizeof(double));
  ndbl = gy_full->size[0] * gy_full->size[1];
  for (i3 = 0; i3 < ndbl; i3++) {
    r1->data[i3] = gy_full->data[i3];
  }

  emxInit_real_T(&b_gx_full, 2);
  i3 = b_gx_full->size[0] * b_gx_full->size[1];
  b_gx_full->size[0] = gx_full->size[0];
  b_gx_full->size[1] = gx_full->size[1];
  emxEnsureCapacity((emxArray__common *)b_gx_full, i3, (int)sizeof(double));
  ndbl = gx_full->size[1];
  for (i3 = 0; i3 < ndbl; i3++) {
    cdiff = gx_full->size[0];
    for (absb = 0; absb < cdiff; absb++) {
      b_gx_full->data[absb + b_gx_full->size[0] * i3] = gx_full->data[absb +
        gx_full->size[0] * i3];
    }
  }

  b_emxInit_real_T(&r2, 1);
  b_emxInit_real_T(&r3, 1);
  c_gx_full[0] = gx_full->size[0] * gx_full->size[1];
  b_idx_x_data = *b_gx_full;
  b_idx_x_data.size = (int *)&c_gx_full;
  b_idx_x_data.numDimensions = 1;
  power(&b_idx_x_data, r3);
  i3 = r2->size[0];
  r2->size[0] = r3->size[0];
  emxEnsureCapacity((emxArray__common *)r2, i3, (int)sizeof(double));
  ndbl = r3->size[0];
  emxFree_real_T(&b_gx_full);
  for (i3 = 0; i3 < ndbl; i3++) {
    r2->data[i3] = r3->data[i3];
  }

  emxInit_real_T(&b_gy_full, 2);
  i3 = b_gy_full->size[0] * b_gy_full->size[1];
  b_gy_full->size[0] = gy_full->size[0];
  b_gy_full->size[1] = gy_full->size[1];
  emxEnsureCapacity((emxArray__common *)b_gy_full, i3, (int)sizeof(double));
  ndbl = gy_full->size[1];
  for (i3 = 0; i3 < ndbl; i3++) {
    cdiff = gy_full->size[0];
    for (absb = 0; absb < cdiff; absb++) {
      b_gy_full->data[absb + b_gy_full->size[0] * i3] = gy_full->data[absb +
        gy_full->size[0] * i3];
    }
  }

  b_emxInit_real_T(&r4, 1);
  c_gy_full[0] = gy_full->size[0] * gy_full->size[1];
  b_idx_x_data = *b_gy_full;
  b_idx_x_data.size = (int *)&c_gy_full;
  b_idx_x_data.numDimensions = 1;
  power(&b_idx_x_data, r3);
  i3 = r4->size[0];
  r4->size[0] = r3->size[0];
  emxEnsureCapacity((emxArray__common *)r4, i3, (int)sizeof(double));
  ndbl = r3->size[0];
  emxFree_real_T(&b_gy_full);
  for (i3 = 0; i3 < ndbl; i3++) {
    r4->data[i3] = r3->data[i3];
  }

  emxFree_real_T(&r3);
  b_emxInit_real_T(&r5, 1);
  i3 = r5->size[0];
  r5->size[0] = gx_full->size[0] * gx_full->size[1];
  emxEnsureCapacity((emxArray__common *)r5, i3, (int)sizeof(double));
  ndbl = gx_full->size[0] * gx_full->size[1];
  for (i3 = 0; i3 < ndbl; i3++) {
    r5->data[i3] = gx_full->data[i3] * gy_full->data[i3];
  }

  emxFree_real_T(&gy_full);
  emxFree_real_T(&gx_full);
  b_emxInit_real_T(&r6, 1);
  ndbl = img->size[0] * img->size[1];
  img_idx_0 = img->size[0] * img->size[1];
  i3 = r6->size[0];
  r6->size[0] = ndbl;
  emxEnsureCapacity((emxArray__common *)r6, i3, (int)sizeof(double));
  for (i3 = 0; i3 < ndbl; i3++) {
    r6->data[i3] = 1.0;
  }

  emxInit_real_T(&a, 2);
  unnamed_idx_0 = r0->size[0];
  ndbl = r1->size[0];
  cdiff = r2->size[0];
  absb = r4->size[0];
  apnd = r5->size[0];
  i3 = a->size[0] * a->size[1];
  a->size[0] = img_idx_0;
  a->size[1] = 6;
  emxEnsureCapacity((emxArray__common *)a, i3, (int)sizeof(double));
  for (i3 = 0; i3 < img_idx_0; i3++) {
    a->data[i3] = r6->data[i3];
  }

  emxFree_real_T(&r6);
  for (i3 = 0; i3 < unnamed_idx_0; i3++) {
    a->data[i3 + a->size[0]] = r0->data[i3];
  }

  emxFree_real_T(&r0);
  for (i3 = 0; i3 < ndbl; i3++) {
    a->data[i3 + (a->size[0] << 1)] = r1->data[i3];
  }

  emxFree_real_T(&r1);
  for (i3 = 0; i3 < cdiff; i3++) {
    a->data[i3 + a->size[0] * 3] = r2->data[i3];
  }

  emxFree_real_T(&r2);
  for (i3 = 0; i3 < absb; i3++) {
    a->data[i3 + (a->size[0] << 2)] = r4->data[i3];
  }

  emxFree_real_T(&r4);
  for (i3 = 0; i3 < apnd; i3++) {
    a->data[i3 + a->size[0] * 5] = r5->data[i3];
  }

  emxFree_real_T(&r5);
  emxInit_real_T(&y_hat, 2);
  if (best_beta_hat_size[0] == 1) {
    i3 = y_hat->size[0] * y_hat->size[1];
    y_hat->size[0] = a->size[0];
    y_hat->size[1] = best_beta_hat_size[1];
    emxEnsureCapacity((emxArray__common *)y_hat, i3, (int)sizeof(double));
    ndbl = a->size[0];
    for (i3 = 0; i3 < ndbl; i3++) {
      cdiff = best_beta_hat_size[1];
      for (absb = 0; absb < cdiff; absb++) {
        y_hat->data[i3 + y_hat->size[0] * absb] = 0.0;
        for (img_idx_0 = 0; img_idx_0 < 6; img_idx_0++) {
          y_hat->data[i3 + y_hat->size[0] * absb] += a->data[i3 + a->size[0] *
            img_idx_0] * best_beta_hat_data[img_idx_0 + absb];
        }
      }
    }
  } else {
    unnamed_idx_0 = a->size[0];
    i3 = y_hat->size[0] * y_hat->size[1];
    y_hat->size[0] = unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *)y_hat, i3, (int)sizeof(double));
    i3 = y_hat->size[0] * y_hat->size[1];
    y_hat->size[1] = best_beta_hat_size[1];
    emxEnsureCapacity((emxArray__common *)y_hat, i3, (int)sizeof(double));
    ndbl = unnamed_idx_0 * best_beta_hat_size[1];
    for (i3 = 0; i3 < ndbl; i3++) {
      y_hat->data[i3] = 0.0;
    }

    b_eml_xgemm(a->size[0], best_beta_hat_size[1], a, a->size[0],
                best_beta_hat_data, y_hat, a->size[0]);
  }

  emxFree_real_T(&a);
  ndbl = y_hat->size[0] * y_hat->size[1];
  sz_idx_0 = (short)img->size[0];
  sz_idx_1 = (short)img->size[1];
  i3 = fittedPlane->size[0] * fittedPlane->size[1];
  fittedPlane->size[0] = sz_idx_0;
  fittedPlane->size[1] = sz_idx_1;
  emxEnsureCapacity((emxArray__common *)fittedPlane, i3, (int)sizeof(double));
  for (absb = 0; absb + 1 <= ndbl; absb++) {
    fittedPlane->data[absb] = y_hat->data[absb];
  }

  emxFree_real_T(&y_hat);
  i3 = gx->size[0] * gx->size[1];
  gx->size[0] = fittedPlane->size[0];
  gx->size[1] = fittedPlane->size[1];
  emxEnsureCapacity((emxArray__common *)gx, i3, (int)sizeof(double));
  b_fittedPlane[0] = fittedPlane->size[0] * fittedPlane->size[1];
  b_idx_x_data = *fittedPlane;
  b_idx_x_data.size = (int *)&b_fittedPlane;
  b_idx_x_data.numDimensions = 1;
  y = mean(&b_idx_x_data);
  ndbl = fittedPlane->size[0] * fittedPlane->size[1];
  for (i3 = 0; i3 < ndbl; i3++) {
    gx->data[i3] = -fittedPlane->data[i3] + y;
  }

  ndbl = gx->size[0] * gx->size[1];
  sz_idx_0 = (short)img->size[0];
  sz_idx_1 = (short)img->size[1];
  i3 = diffPlane->size[0] * diffPlane->size[1];
  diffPlane->size[0] = sz_idx_0;
  diffPlane->size[1] = sz_idx_1;
  emxEnsureCapacity((emxArray__common *)diffPlane, i3, (int)sizeof(double));
  for (absb = 0; absb + 1 <= ndbl; absb++) {
    diffPlane->data[absb] = gx->data[absb];
  }

  cdiff = 1;
  absb = fittedPlane->size[0] * fittedPlane->size[1];
  y = fittedPlane->data[0];
  ndbl = fittedPlane->size[0] * fittedPlane->size[1];
  if (ndbl > 1) {
    if (rtIsNaN(fittedPlane->data[0])) {
      ndbl = 2;
      exitg1 = false;
      while ((!exitg1) && (ndbl <= absb)) {
        cdiff = ndbl;
        if (!rtIsNaN(fittedPlane->data[ndbl - 1])) {
          y = fittedPlane->data[ndbl - 1];
          exitg1 = true;
        } else {
          ndbl++;
        }
      }
    }

    ndbl = fittedPlane->size[0] * fittedPlane->size[1];
    if (cdiff < ndbl) {
      while (cdiff + 1 <= absb) {
        if (fittedPlane->data[cdiff] < y) {
          y = fittedPlane->data[cdiff];
        }

        cdiff++;
      }
    }
  }

  emxInit_real_T(&r7, 2);
  rdivide(y, fittedPlane, r7);
  i3 = gx->size[0] * gx->size[1];
  gx->size[0] = r7->size[0];
  gx->size[1] = r7->size[1];
  emxEnsureCapacity((emxArray__common *)gx, i3, (int)sizeof(double));
  ndbl = r7->size[0] * r7->size[1];
  for (i3 = 0; i3 < ndbl; i3++) {
    gx->data[i3] = r7->data[i3];
  }

  emxFree_real_T(&r7);
  ndbl = gx->size[0] * gx->size[1];
  sz_idx_0 = (short)img->size[0];
  sz_idx_1 = (short)img->size[1];
  i3 = scalerPlane->size[0] * scalerPlane->size[1];
  scalerPlane->size[0] = sz_idx_0;
  scalerPlane->size[1] = sz_idx_1;
  emxEnsureCapacity((emxArray__common *)scalerPlane, i3, (int)sizeof(double));
  for (absb = 0; absb + 1 <= ndbl; absb++) {
    scalerPlane->data[absb] = gx->data[absb];
  }

  emxFree_real_T(&gx);

  /* %% The threshold below can create problematic detrending scalar plane. */
  /* %% Use with caution. */
  /*  % thres = 70; */
  /*  % interestedMask = fittedPlane>thres; */
  /*  % fittedPlane(~interestedMask) = thres; % prevent the quadratic surface to be too down to near 0 */
  /*  % scalerPlane = reshape ( 1 ./ fittedPlane   , [h w] ); */
  /*  figure, surf(imgF); */
  /*  hold on; surf(lowResPlane); hold off */
}

/* End of code generation (imgDetrend_v2.c) */
