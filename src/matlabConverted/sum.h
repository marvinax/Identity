/*
 * sum.h
 *
 * Code generation for function 'sum'
 *
 */

#ifndef __SUM_H__
#define __SUM_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "getPowderAndQr_types.h"

/* Function Declarations */
extern double b_sum(const emxArray_real_T *x);
extern double c_sum(const boolean_T x[40000]);
extern void sum(const emxArray_real_T *x, emxArray_real_T *y);

#endif

/* End of code generation (sum.h) */
