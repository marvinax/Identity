/*
 * ransacFit_quad.h
 *
 * Code generation for function 'ransacFit_quad'
 *
 */

#ifndef __RANSACFIT_QUAD_H__
#define __RANSACFIT_QUAD_H__

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
extern void ransacFit_quad(const emxArray_real_T *gx, const emxArray_real_T *gy,
  const emxArray_real_T *val, emxArray_real_T *val_fitted, double
  best_beta_hat_data[], int best_beta_hat_size[2], double *minErr);

#endif

/* End of code generation (ransacFit_quad.h) */
