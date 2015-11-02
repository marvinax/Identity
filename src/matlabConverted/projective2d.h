/*
 * projective2d.h
 *
 * Code generation for function 'projective2d'
 *
 */

#ifndef __PROJECTIVE2D_H__
#define __PROJECTIVE2D_H__

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
extern void c_projective2d_transformPointsI(const double self_T[9], const
  emxArray_real_T *varargin_1, const emxArray_real_T *varargin_2,
  emxArray_real_T *varargout_1, emxArray_real_T *varargout_2);
extern void d_projective2d_transformPointsI(const double self_T[9], const double
  varargin_1[16], double varargout_1_data[], int varargout_1_size[2]);
extern void e_projective2d_transformPointsI(const double self_T[9], const double
  varargin_1[8], double varargout_1_data[], int varargout_1_size[2]);
extern void projective2d_projective2d(const double A[9], double
  *self_Dimensionality, double self_T[9]);

#endif

/* End of code generation (projective2d.h) */
