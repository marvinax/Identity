/*
 * rdivide.c
 *
 * Code generation for function 'rdivide'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "rdivide.h"
#include "getPowderAndQr_emxutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void b_rdivide(const emxArray_real_T *x, const emxArray_real_T *y,
               emxArray_real_T *z)
{
  int i23;
  int loop_ub;
  i23 = z->size[0] * z->size[1];
  z->size[0] = x->size[0];
  z->size[1] = x->size[1];
  emxEnsureCapacity((emxArray__common *)z, i23, (int)sizeof(double));
  loop_ub = x->size[0] * x->size[1];
  for (i23 = 0; i23 < loop_ub; i23++) {
    z->data[i23] = x->data[i23] / y->data[i23];
  }
}

void c_rdivide(double x, const double y[40000], double z[40000])
{
  int i43;
  for (i43 = 0; i43 < 40000; i43++) {
    z[i43] = x / y[i43];
  }
}

void rdivide(double x, const emxArray_real_T *y, emxArray_real_T *z)
{
  int i7;
  int loop_ub;
  i7 = z->size[0] * z->size[1];
  z->size[0] = y->size[0];
  z->size[1] = y->size[1];
  emxEnsureCapacity((emxArray__common *)z, i7, (int)sizeof(double));
  loop_ub = y->size[0] * y->size[1];
  for (i7 = 0; i7 < loop_ub; i7++) {
    z->data[i7] = x / y->data[i7];
  }
}

/* End of code generation (rdivide.c) */
