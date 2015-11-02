/*
 * abs.c
 *
 * Code generation for function 'abs'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "abs.h"
#include "getPowderAndQr_emxutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void b_abs(const emxArray_real_T *x, emxArray_real_T *y)
{
  int unnamed_idx_0;
  int i6;
  unnamed_idx_0 = x->size[0];
  i6 = y->size[0];
  y->size[0] = unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)y, i6, (int)sizeof(double));
  for (unnamed_idx_0 = 0; unnamed_idx_0 < x->size[0]; unnamed_idx_0++) {
    y->data[unnamed_idx_0] = fabs(x->data[unnamed_idx_0]);
  }
}

void c_abs(const double x[8], double y[8])
{
  int k;
  for (k = 0; k < 8; k++) {
    y[k] = fabs(x[k]);
  }
}

void d_abs(const double x[16], double y[16])
{
  int k;
  for (k = 0; k < 16; k++) {
    y[k] = fabs(x[k]);
  }
}

void e_abs(const double x[169], double y[169])
{
  int k;
  for (k = 0; k < 169; k++) {
    y[k] = fabs(x[k]);
  }
}

/* End of code generation (abs.c) */
