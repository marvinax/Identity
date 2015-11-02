/*
 * diff.c
 *
 * Code generation for function 'diff'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "diff.h"
#include "getPowderAndQr_emxutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void diff(const emxArray_real_T *x, emxArray_real_T *y)
{
  int dimSize;
  int ixStart;
  int iyStart;
  int r;
  int ixLead;
  int iyLead;
  double work;
  int m;
  double tmp2;
  dimSize = x->size[0];
  if (x->size[0] <= 1) {
    ixStart = y->size[0] * y->size[1];
    y->size[0] = 0;
    y->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)y, ixStart, (int)sizeof(double));
  } else {
    ixStart = y->size[0] * y->size[1];
    y->size[0] = x->size[0] - 1;
    y->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)y, ixStart, (int)sizeof(double));
    ixStart = 1;
    iyStart = 0;
    for (r = 0; r < 2; r++) {
      ixLead = ixStart;
      iyLead = iyStart;
      work = x->data[ixStart - 1];
      for (m = 2; m <= dimSize; m++) {
        tmp2 = work;
        work = x->data[ixLead];
        tmp2 = x->data[ixLead] - tmp2;
        ixLead++;
        y->data[iyLead] = tmp2;
        iyLead++;
      }

      ixStart += dimSize;
      iyStart = (iyStart + dimSize) - 1;
    }
  }
}

/* End of code generation (diff.c) */
