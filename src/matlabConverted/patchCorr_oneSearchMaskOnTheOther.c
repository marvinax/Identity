/*
 * patchCorr_oneSearchMaskOnTheOther.c
 *
 * Code generation for function 'patchCorr_oneSearchMaskOnTheOther'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "patchCorr_oneSearchMaskOnTheOther.h"
#include "getPowderAndQr_emxutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void convertToIdx(const double range[2], emxArray_real_T *ret)
{
  int n;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  double absa;
  double absb;
  int nm1d2;
  int k;
  if (rtIsNaN(range[0]) || rtIsNaN(range[1])) {
    n = 0;
    anew = rtNaN;
    apnd = range[1];
  } else if (range[1] < range[0]) {
    n = -1;
    anew = range[0];
    apnd = range[1];
  } else if (rtIsInf(range[0]) || rtIsInf(range[1])) {
    n = 0;
    anew = rtNaN;
    apnd = range[1];
  } else {
    anew = range[0];
    ndbl = floor((range[1] - range[0]) + 0.5);
    apnd = range[0] + ndbl;
    cdiff = apnd - range[1];
    absa = fabs(range[0]);
    absb = fabs(range[1]);
    if ((absa >= absb) || rtIsNaN(absb)) {
      absb = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      ndbl++;
      apnd = range[1];
    } else if (cdiff > 0.0) {
      apnd = range[0] + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl - 1;
    } else {
      n = -1;
    }
  }

  nm1d2 = ret->size[0] * ret->size[1];
  ret->size[0] = 1;
  ret->size[1] = n + 1;
  emxEnsureCapacity((emxArray__common *)ret, nm1d2, (int)sizeof(double));
  if (n + 1 > 0) {
    ret->data[0] = anew;
    if (n + 1 > 1) {
      ret->data[n] = apnd;
      nm1d2 = n / 2;
      for (k = 1; k < nm1d2; k++) {
        ret->data[k] = anew + (double)k;
        ret->data[n - k] = apnd - (double)k;
      }

      if (nm1d2 << 1 == n) {
        ret->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        ret->data[nm1d2] = anew + (double)nm1d2;
        ret->data[nm1d2 + 1] = apnd - (double)nm1d2;
      }
    }
  }
}

/* End of code generation (patchCorr_oneSearchMaskOnTheOther.c) */
