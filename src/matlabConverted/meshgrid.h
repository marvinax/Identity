/*
 * meshgrid.h
 *
 * Code generation for function 'meshgrid'
 *
 */

#ifndef __MESHGRID_H__
#define __MESHGRID_H__

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
extern void b_meshgrid(const double x[13], const double y[13], double xx[169],
  double yy[169]);
extern void c_meshgrid(const double x[200], const double y[200], double xx[40000],
  double yy[40000]);
extern void meshgrid(const emxArray_real_T *x, const emxArray_real_T *y,
                     emxArray_real_T *xx, emxArray_real_T *yy);

#endif

/* End of code generation (meshgrid.h) */
