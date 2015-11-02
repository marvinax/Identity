/*
 * sqrt.c
 *
 * Code generation for function 'sqrt'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "sqrt.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void b_sqrt(emxArray_real32_T *x)
{
  int i55;
  int k;
  i55 = x->size[0];
  for (k = 0; k < i55; k++) {
    x->data[k] = (real32_T)sqrt(x->data[k]);
  }
}

/* End of code generation (sqrt.c) */
