/*
 * normalizeControlPoints.h
 *
 * Code generation for function 'normalizeControlPoints'
 *
 */

#ifndef __NORMALIZECONTROLPOINTS_H__
#define __NORMALIZECONTROLPOINTS_H__

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
extern void normalizeControlPoints(const double pts[8], double ptsNorm[8],
  double normMatrixInv[9]);

#endif

/* End of code generation (normalizeControlPoints.h) */
