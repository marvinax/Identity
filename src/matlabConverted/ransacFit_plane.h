/*
 * ransacFit_plane.h
 *
 * Code generation for function 'ransacFit_plane'
 *
 */

#ifndef __RANSACFIT_PLANE_H__
#define __RANSACFIT_PLANE_H__

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
extern void ransacFit_plane(const double gx[169], const double gy[169], const
  double val[169], double val_fitted[169], double best_beta_hat_data[], int
  best_beta_hat_size[2], double *minErr);

#endif

/* End of code generation (ransacFit_plane.h) */
