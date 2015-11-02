/*
 * imgDetrend_v2.h
 *
 * Code generation for function 'imgDetrend_v2'
 *
 */

#ifndef __IMGDETREND_V2_H__
#define __IMGDETREND_V2_H__

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
extern void b_eml_xgemm(int m, int n, const emxArray_real_T *A, int lda, const
  double B_data[], emxArray_real_T *C, int ldc);
extern void imgDetrend_v2(const emxArray_real_T *img, emxArray_real_T *diffPlane,
  emxArray_real_T *scalerPlane, emxArray_real_T *fittedPlane, double *minErr);

#endif

/* End of code generation (imgDetrend_v2.h) */
