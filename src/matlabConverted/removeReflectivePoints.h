/*
 * removeReflectivePoints.h
 *
 * Code generation for function 'removeReflectivePoints'
 *
 */

#ifndef __REMOVEREFLECTIVEPOINTS_H__
#define __REMOVEREFLECTIVEPOINTS_H__

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
extern void c_eml_li_find(const boolean_T x[40000], emxArray_int32_T *y);
extern void removeReflectivePoints(const double img[40000], const boolean_T
  mask[40000], boolean_T mask_reflective[40000], double *thres, double
  *cnt_reflectivePts);

#endif

/* End of code generation (removeReflectivePoints.h) */
