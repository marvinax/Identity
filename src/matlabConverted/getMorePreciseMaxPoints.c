/*
 * getMorePreciseMaxPoints.c
 *
 * Code generation for function 'getMorePreciseMaxPoints'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "getMorePreciseMaxPoints.h"
#include "interp2.h"
#include "getPowderAndQr_emxutil.h"
#include "meshgrid.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Declarations */
static void eml_null_assignment(emxArray_real_T *x, const emxArray_boolean_T
  *idx);

/* Function Definitions */
static void eml_null_assignment(emxArray_real_T *x, const emxArray_boolean_T
  *idx)
{
  int nxin;
  int k0;
  int k;
  int nxout;
  nxin = x->size[1];
  k0 = 0;
  for (k = 1; k <= idx->size[1]; k++) {
    k0 += idx->data[k - 1];
  }

  nxout = x->size[1] - k0;
  k0 = -1;
  for (k = 1; k <= nxin; k++) {
    if ((k > idx->size[1]) || (!idx->data[k - 1])) {
      k0++;
      x->data[k0] = x->data[k - 1];
    }
  }

  k0 = x->size[0] * x->size[1];
  if (1 > nxout) {
    x->size[1] = 0;
  } else {
    x->size[1] = nxout;
  }

  emxEnsureCapacity((emxArray__common *)x, k0, (int)sizeof(double));
}

void getMorePreciseMaxPoints(const emxArray_real_T *H, const double P_data[],
  const int P_size[2], double P_new_data[], int P_new_size[2])
{
  int width;
  int height;
  signed char iv1[2];
  int i9;
  int loop_ub;
  int i;
  emxArray_real_T *x_range;
  emxArray_real_T *y_range;
  emxArray_real_T *x_range_interp;
  emxArray_real_T *y_range_interp;
  emxArray_real_T *H_interp;
  emxArray_real_T *X_orig;
  emxArray_real_T *Y_orig;
  emxArray_real_T *X_interp;
  emxArray_real_T *Y_interp;
  emxArray_boolean_T *r13;
  emxArray_real_T *b_H;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  double absa;
  double absb;
  int nm1d2;
  int ixstart;
  int itmp;
  boolean_T exitg1;
  signed char tmp_data[2];
  double b_Y_interp[2];

  /*  Improve the precision of maximal points using cubic spline interpolation */
  /*  Oct. 2014, Chau-Wai Wong */
  width = H->size[1];
  height = H->size[0];
  for (i9 = 0; i9 < 2; i9++) {
    iv1[i9] = (signed char)P_size[i9];
  }

  P_new_size[0] = iv1[0];
  P_new_size[1] = iv1[1];
  loop_ub = iv1[0] * iv1[1];
  for (i9 = 0; i9 < loop_ub; i9++) {
    P_new_data[i9] = 0.0;
  }

  i = 0;
  emxInit_real_T(&x_range, 2);
  emxInit_real_T(&y_range, 2);
  emxInit_real_T(&x_range_interp, 2);
  emxInit_real_T(&y_range_interp, 2);
  emxInit_real_T(&H_interp, 2);
  emxInit_real_T(&X_orig, 2);
  emxInit_real_T(&Y_orig, 2);
  emxInit_real_T(&X_interp, 2);
  emxInit_real_T(&Y_interp, 2);
  emxInit_boolean_T(&r13, 2);
  emxInit_real_T(&b_H, 2);
  while (i <= P_size[0] - 1) {
    if (rtIsNaN(P_data[i + P_size[0]] - 10.0) || rtIsNaN(P_data[i + P_size[0]] +
         10.0)) {
      loop_ub = 0;
      anew = rtNaN;
      apnd = P_data[i + P_size[0]] + 10.0;
    } else if (P_data[i + P_size[0]] + 10.0 < P_data[i + P_size[0]] - 10.0) {
      loop_ub = -1;
      anew = P_data[i + P_size[0]] - 10.0;
      apnd = P_data[i + P_size[0]] + 10.0;
    } else if (rtIsInf(P_data[i + P_size[0]] - 10.0) || rtIsInf(P_data[i +
                P_size[0]] + 10.0)) {
      loop_ub = 0;
      anew = rtNaN;
      apnd = P_data[i + P_size[0]] + 10.0;
    } else {
      anew = P_data[i + P_size[0]] - 10.0;
      ndbl = floor(((P_data[i + P_size[0]] + 10.0) - (P_data[i + P_size[0]] -
        10.0)) + 0.5);
      apnd = (P_data[i + P_size[0]] - 10.0) + ndbl;
      cdiff = apnd - (P_data[i + P_size[0]] + 10.0);
      absa = fabs(P_data[i + P_size[0]] - 10.0);
      absb = fabs(P_data[i + P_size[0]] + 10.0);
      if ((absa >= absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = P_data[i + P_size[0]] + 10.0;
      } else if (cdiff > 0.0) {
        apnd = (P_data[i + P_size[0]] - 10.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        loop_ub = (int)ndbl - 1;
      } else {
        loop_ub = -1;
      }
    }

    i9 = x_range->size[0] * x_range->size[1];
    x_range->size[0] = 1;
    x_range->size[1] = loop_ub + 1;
    emxEnsureCapacity((emxArray__common *)x_range, i9, (int)sizeof(double));
    if (loop_ub + 1 > 0) {
      x_range->data[0] = anew;
      if (loop_ub + 1 > 1) {
        x_range->data[loop_ub] = apnd;
        nm1d2 = loop_ub / 2;
        for (ixstart = 1; ixstart < nm1d2; ixstart++) {
          x_range->data[ixstart] = anew + (double)ixstart;
          x_range->data[loop_ub - ixstart] = apnd - (double)ixstart;
        }

        if (nm1d2 << 1 == loop_ub) {
          x_range->data[nm1d2] = (anew + apnd) / 2.0;
        } else {
          x_range->data[nm1d2] = anew + (double)nm1d2;
          x_range->data[nm1d2 + 1] = apnd - (double)nm1d2;
        }
      }
    }

    if (rtIsNaN(P_data[i] - 20.0) || rtIsNaN(P_data[i] + 20.0)) {
      loop_ub = 0;
      anew = rtNaN;
      apnd = P_data[i] + 20.0;
    } else if (P_data[i] + 20.0 < P_data[i] - 20.0) {
      loop_ub = -1;
      anew = P_data[i] - 20.0;
      apnd = P_data[i] + 20.0;
    } else if (rtIsInf(P_data[i] - 20.0) || rtIsInf(P_data[i] + 20.0)) {
      loop_ub = 0;
      anew = rtNaN;
      apnd = P_data[i] + 20.0;
    } else {
      anew = P_data[i] - 20.0;
      ndbl = floor(((P_data[i] + 20.0) - (P_data[i] - 20.0)) + 0.5);
      apnd = (P_data[i] - 20.0) + ndbl;
      cdiff = apnd - (P_data[i] + 20.0);
      absa = fabs(P_data[i] - 20.0);
      absb = fabs(P_data[i] + 20.0);
      if ((absa >= absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = P_data[i] + 20.0;
      } else if (cdiff > 0.0) {
        apnd = (P_data[i] - 20.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        loop_ub = (int)ndbl - 1;
      } else {
        loop_ub = -1;
      }
    }

    i9 = y_range->size[0] * y_range->size[1];
    y_range->size[0] = 1;
    y_range->size[1] = loop_ub + 1;
    emxEnsureCapacity((emxArray__common *)y_range, i9, (int)sizeof(double));
    if (loop_ub + 1 > 0) {
      y_range->data[0] = anew;
      if (loop_ub + 1 > 1) {
        y_range->data[loop_ub] = apnd;
        nm1d2 = loop_ub / 2;
        for (ixstart = 1; ixstart < nm1d2; ixstart++) {
          y_range->data[ixstart] = anew + (double)ixstart;
          y_range->data[loop_ub - ixstart] = apnd - (double)ixstart;
        }

        if (nm1d2 << 1 == loop_ub) {
          y_range->data[nm1d2] = (anew + apnd) / 2.0;
        } else {
          y_range->data[nm1d2] = anew + (double)nm1d2;
          y_range->data[nm1d2 + 1] = apnd - (double)nm1d2;
        }
      }
    }

    i9 = r13->size[0] * r13->size[1];
    r13->size[0] = 1;
    r13->size[1] = x_range->size[1];
    emxEnsureCapacity((emxArray__common *)r13, i9, (int)sizeof(boolean_T));
    loop_ub = x_range->size[0] * x_range->size[1];
    for (i9 = 0; i9 < loop_ub; i9++) {
      r13->data[i9] = ((x_range->data[i9] < 1.0) || (x_range->data[i9] > width));
    }

    eml_null_assignment(x_range, r13);
    i9 = r13->size[0] * r13->size[1];
    r13->size[0] = 1;
    r13->size[1] = y_range->size[1];
    emxEnsureCapacity((emxArray__common *)r13, i9, (int)sizeof(boolean_T));
    loop_ub = y_range->size[0] * y_range->size[1];
    for (i9 = 0; i9 < loop_ub; i9++) {
      r13->data[i9] = ((y_range->data[i9] < 1.0) || (y_range->data[i9] > height));
    }

    eml_null_assignment(y_range, r13);
    meshgrid(x_range, y_range, X_orig, Y_orig);
    if (rtIsNaN(P_data[i + P_size[0]] - 10.0) || rtIsNaN(P_data[i + P_size[0]] +
         10.0)) {
      loop_ub = 0;
      anew = rtNaN;
      apnd = P_data[i + P_size[0]] + 10.0;
    } else if (P_data[i + P_size[0]] + 10.0 < P_data[i + P_size[0]] - 10.0) {
      loop_ub = -1;
      anew = P_data[i + P_size[0]] - 10.0;
      apnd = P_data[i + P_size[0]] + 10.0;
    } else if (rtIsInf(P_data[i + P_size[0]] - 10.0) || rtIsInf(P_data[i +
                P_size[0]] + 10.0)) {
      loop_ub = 0;
      anew = rtNaN;
      apnd = P_data[i + P_size[0]] + 10.0;
    } else {
      anew = P_data[i + P_size[0]] - 10.0;
      ndbl = floor(((P_data[i + P_size[0]] + 10.0) - (P_data[i + P_size[0]] -
        10.0)) / 0.03125 + 0.5);
      apnd = (P_data[i + P_size[0]] - 10.0) + ndbl * 0.03125;
      cdiff = apnd - (P_data[i + P_size[0]] + 10.0);
      absa = fabs(P_data[i + P_size[0]] - 10.0);
      absb = fabs(P_data[i + P_size[0]] + 10.0);
      if ((absa >= absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = P_data[i + P_size[0]] + 10.0;
      } else if (cdiff > 0.0) {
        apnd = (P_data[i + P_size[0]] - 10.0) + (ndbl - 1.0) * 0.03125;
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        loop_ub = (int)ndbl - 1;
      } else {
        loop_ub = -1;
      }
    }

    i9 = x_range_interp->size[0] * x_range_interp->size[1];
    x_range_interp->size[0] = 1;
    x_range_interp->size[1] = loop_ub + 1;
    emxEnsureCapacity((emxArray__common *)x_range_interp, i9, (int)sizeof(double));
    if (loop_ub + 1 > 0) {
      x_range_interp->data[0] = anew;
      if (loop_ub + 1 > 1) {
        x_range_interp->data[loop_ub] = apnd;
        nm1d2 = loop_ub / 2;
        for (ixstart = 1; ixstart < nm1d2; ixstart++) {
          ndbl = (double)ixstart * 0.03125;
          x_range_interp->data[ixstart] = anew + ndbl;
          x_range_interp->data[loop_ub - ixstart] = apnd - ndbl;
        }

        if (nm1d2 << 1 == loop_ub) {
          x_range_interp->data[nm1d2] = (anew + apnd) / 2.0;
        } else {
          ndbl = (double)nm1d2 * 0.03125;
          x_range_interp->data[nm1d2] = anew + ndbl;
          x_range_interp->data[nm1d2 + 1] = apnd - ndbl;
        }
      }
    }

    if (rtIsNaN(P_data[i] - 20.0) || rtIsNaN(P_data[i] + 20.0)) {
      loop_ub = 0;
      anew = rtNaN;
      apnd = P_data[i] + 20.0;
    } else if (P_data[i] + 20.0 < P_data[i] - 20.0) {
      loop_ub = -1;
      anew = P_data[i] - 20.0;
      apnd = P_data[i] + 20.0;
    } else if (rtIsInf(P_data[i] - 20.0) || rtIsInf(P_data[i] + 20.0)) {
      loop_ub = 0;
      anew = rtNaN;
      apnd = P_data[i] + 20.0;
    } else {
      anew = P_data[i] - 20.0;
      ndbl = floor(((P_data[i] + 20.0) - (P_data[i] - 20.0)) / 0.03125 + 0.5);
      apnd = (P_data[i] - 20.0) + ndbl * 0.03125;
      cdiff = apnd - (P_data[i] + 20.0);
      absa = fabs(P_data[i] - 20.0);
      absb = fabs(P_data[i] + 20.0);
      if ((absa >= absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = P_data[i] + 20.0;
      } else if (cdiff > 0.0) {
        apnd = (P_data[i] - 20.0) + (ndbl - 1.0) * 0.03125;
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        loop_ub = (int)ndbl - 1;
      } else {
        loop_ub = -1;
      }
    }

    i9 = y_range_interp->size[0] * y_range_interp->size[1];
    y_range_interp->size[0] = 1;
    y_range_interp->size[1] = loop_ub + 1;
    emxEnsureCapacity((emxArray__common *)y_range_interp, i9, (int)sizeof(double));
    if (loop_ub + 1 > 0) {
      y_range_interp->data[0] = anew;
      if (loop_ub + 1 > 1) {
        y_range_interp->data[loop_ub] = apnd;
        nm1d2 = loop_ub / 2;
        for (ixstart = 1; ixstart < nm1d2; ixstart++) {
          ndbl = (double)ixstart * 0.03125;
          y_range_interp->data[ixstart] = anew + ndbl;
          y_range_interp->data[loop_ub - ixstart] = apnd - ndbl;
        }

        if (nm1d2 << 1 == loop_ub) {
          y_range_interp->data[nm1d2] = (anew + apnd) / 2.0;
        } else {
          ndbl = (double)nm1d2 * 0.03125;
          y_range_interp->data[nm1d2] = anew + ndbl;
          y_range_interp->data[nm1d2 + 1] = apnd - ndbl;
        }
      }
    }

    i9 = r13->size[0] * r13->size[1];
    r13->size[0] = 1;
    r13->size[1] = x_range_interp->size[1];
    emxEnsureCapacity((emxArray__common *)r13, i9, (int)sizeof(boolean_T));
    loop_ub = x_range_interp->size[0] * x_range_interp->size[1];
    for (i9 = 0; i9 < loop_ub; i9++) {
      r13->data[i9] = ((x_range_interp->data[i9] < 1.0) || (x_range_interp->
        data[i9] > width));
    }

    eml_null_assignment(x_range_interp, r13);
    i9 = r13->size[0] * r13->size[1];
    r13->size[0] = 1;
    r13->size[1] = y_range_interp->size[1];
    emxEnsureCapacity((emxArray__common *)r13, i9, (int)sizeof(boolean_T));
    loop_ub = y_range_interp->size[0] * y_range_interp->size[1];
    for (i9 = 0; i9 < loop_ub; i9++) {
      r13->data[i9] = ((y_range_interp->data[i9] < 1.0) || (y_range_interp->
        data[i9] > height));
    }

    eml_null_assignment(y_range_interp, r13);
    meshgrid(x_range_interp, y_range_interp, X_interp, Y_interp);
    i9 = b_H->size[0] * b_H->size[1];
    b_H->size[0] = y_range->size[1];
    b_H->size[1] = x_range->size[1];
    emxEnsureCapacity((emxArray__common *)b_H, i9, (int)sizeof(double));
    loop_ub = x_range->size[1];
    for (i9 = 0; i9 < loop_ub; i9++) {
      nm1d2 = y_range->size[1];
      for (ixstart = 0; ixstart < nm1d2; ixstart++) {
        b_H->data[ixstart + b_H->size[0] * i9] = H->data[((int)y_range->
          data[y_range->size[0] * ixstart] + H->size[0] * ((int)x_range->
          data[x_range->size[0] * i9] - 1)) - 1];
      }
    }

    interp2(X_orig, Y_orig, b_H, X_interp, Y_interp, H_interp);
    ixstart = 1;
    loop_ub = H_interp->size[0] * H_interp->size[1];
    ndbl = H_interp->data[0];
    itmp = 0;
    nm1d2 = H_interp->size[0] * H_interp->size[1];
    if (nm1d2 > 1) {
      if (rtIsNaN(H_interp->data[0])) {
        nm1d2 = 2;
        exitg1 = false;
        while ((!exitg1) && (nm1d2 <= loop_ub)) {
          ixstart = nm1d2;
          if (!rtIsNaN(H_interp->data[nm1d2 - 1])) {
            ndbl = H_interp->data[nm1d2 - 1];
            itmp = nm1d2 - 1;
            exitg1 = true;
          } else {
            nm1d2++;
          }
        }
      }

      nm1d2 = H_interp->size[0] * H_interp->size[1];
      if (ixstart < nm1d2) {
        while (ixstart + 1 <= loop_ub) {
          if (H_interp->data[ixstart] > ndbl) {
            ndbl = H_interp->data[ixstart];
            itmp = ixstart;
          }

          ixstart++;
        }
      }
    }

    loop_ub = P_new_size[1];
    for (i9 = 0; i9 < loop_ub; i9++) {
      tmp_data[i9] = (signed char)i9;
    }

    b_Y_interp[0] = Y_interp->data[itmp];
    b_Y_interp[1] = X_interp->data[itmp];
    loop_ub = P_new_size[1];
    for (i9 = 0; i9 < loop_ub; i9++) {
      P_new_data[i + P_new_size[0] * tmp_data[i9]] = b_Y_interp[i9];
    }

    /* figure; imagesc(H_interp) */
    i++;
  }

  emxFree_real_T(&b_H);
  emxFree_boolean_T(&r13);
  emxFree_real_T(&Y_interp);
  emxFree_real_T(&X_interp);
  emxFree_real_T(&Y_orig);
  emxFree_real_T(&X_orig);
  emxFree_real_T(&H_interp);
  emxFree_real_T(&y_range_interp);
  emxFree_real_T(&x_range_interp);
  emxFree_real_T(&y_range);
  emxFree_real_T(&x_range);
}

/* End of code generation (getMorePreciseMaxPoints.c) */
