/*
 * sum.c
 *
 * Code generation for function 'sum'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "sum.h"
#include "getPowderAndQr_emxutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
double b_sum(const emxArray_real_T *x)
{
  double y;
  int k;
  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= x->size[0]; k++) {
      y += x->data[k - 1];
    }
  }

  return y;
}

double c_sum(const boolean_T x[40000])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 39999; k++) {
    y += (double)x[k + 1];
  }

  return y;
}

void sum(const emxArray_real_T *x, emxArray_real_T *y)
{
  unsigned int sz[2];
  int vstride;
  int iy;
  int ixstart;
  int j;
  double s;
  for (vstride = 0; vstride < 2; vstride++) {
    sz[vstride] = (unsigned int)x->size[vstride];
  }

  vstride = y->size[0];
  y->size[0] = (int)sz[0];
  emxEnsureCapacity((emxArray__common *)y, vstride, (int)sizeof(double));
  if (x->size[0] == 0) {
    vstride = y->size[0];
    y->size[0] = (int)sz[0];
    emxEnsureCapacity((emxArray__common *)y, vstride, (int)sizeof(double));
    iy = (int)sz[0];
    for (vstride = 0; vstride < iy; vstride++) {
      y->data[vstride] = 0.0;
    }
  } else {
    vstride = x->size[0];
    iy = -1;
    ixstart = -1;
    for (j = 1; j <= vstride; j++) {
      ixstart++;
      s = x->data[ixstart] + x->data[ixstart + vstride];
      iy++;
      y->data[iy] = s;
    }
  }
}

/* End of code generation (sum.c) */
