/*
 * round.c
 *
 * Code generation for function 'round'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "round.h"
#include "getPowderAndQr_rtwutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void b_round(emxArray_real_T *x)
{
  int i44;
  int k;
  i44 = x->size[0] * x->size[1];
  for (k = 0; k < i44; k++) {
    x->data[k] = rt_roundd_snf(x->data[k]);
  }
}

void c_round(double x[6000])
{
  int k;
  for (k = 0; k < 6000; k++) {
    x[k] = rt_roundd_snf(x[k]);
  }
}

void d_round(double x[3000])
{
  int k;
  for (k = 0; k < 3000; k++) {
    x[k] = rt_roundd_snf(x[k]);
  }
}

/* End of code generation (round.c) */
