/*
 * ppval.c
 *
 * Code generation for function 'ppval'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "ppval.h"
#include "getPowderAndQr_emxutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void ppval(const emxArray_real_T *pp_breaks, const emxArray_real_T *pp_coefs,
           double x, emxArray_real_T *v)
{
  int elementsPerPage;
  int coefStride;
  int low_ip1;
  int low_i;
  int high_i;
  int ic0;
  int icp;
  double xloc;
  elementsPerPage = pp_coefs->size[0];
  coefStride = pp_coefs->size[0] * (pp_breaks->size[1] - 1);
  low_ip1 = v->size[0];
  v->size[0] = pp_coefs->size[0];
  emxEnsureCapacity((emxArray__common *)v, low_ip1, (int)sizeof(double));
  if (rtIsNaN(x)) {
    for (low_ip1 = 1; low_ip1 <= elementsPerPage; low_ip1++) {
      v->data[low_ip1 - 1] = x;
    }
  } else {
    low_i = 1;
    low_ip1 = 2;
    high_i = pp_breaks->size[1];
    while (high_i > low_ip1) {
      ic0 = (low_i >> 1) + (high_i >> 1);
      if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
        ic0++;
      }

      if (x >= pp_breaks->data[ic0 - 1]) {
        low_i = ic0;
        low_ip1 = ic0 + 1;
      } else {
        high_i = ic0;
      }
    }

    icp = (low_i - 1) * pp_coefs->size[0];
    xloc = x - pp_breaks->data[low_i - 1];
    for (low_ip1 = 0; low_ip1 + 1 <= elementsPerPage; low_ip1++) {
      v->data[low_ip1] = pp_coefs->data[icp + low_ip1];
    }

    for (high_i = 2; high_i <= pp_coefs->size[2]; high_i++) {
      ic0 = icp + (high_i - 1) * coefStride;
      for (low_ip1 = 0; low_ip1 + 1 <= elementsPerPage; low_ip1++) {
        v->data[low_ip1] = xloc * v->data[low_ip1] + pp_coefs->data[ic0 +
          low_ip1];
      }
    }
  }
}

/* End of code generation (ppval.c) */
