/*
 * imref2d.h
 *
 * Code generation for function 'imref2d'
 *
 */

#ifndef __IMREF2D_H__
#define __IMREF2D_H__

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
extern void imref2d_imref2d(const double imageSizeIn[2], double
  obj_XWorldLimits[2], double obj_YWorldLimits[2], double obj_ImageSize[2],
  double *obj_PixelExtentInWorldX, double *obj_PixelExtentInWorldY);
extern void imref2d_worldToIntrinsic(const emxArray_real_T *xWorld, const
  emxArray_real_T *yWorld, emxArray_real_T *xi, emxArray_real_T *yi);

#endif

/* End of code generation (imref2d.h) */
