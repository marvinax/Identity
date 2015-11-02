/*
 * imwarp.h
 *
 * Code generation for function 'imwarp'
 *
 */

#ifndef __IMWARP_H__
#define __IMWARP_H__

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
extern void b_imwarp(const emxArray_uint8_T *varargin_1, const double
                     varargin_3_T[9], const double varargin_6_ImageSize[2],
                     emxArray_uint8_T *outputImage);
extern void c_imwarp(const emxArray_real_T *varargin_1, const double
                     varargin_3_T[9], const double varargin_6_ImageSize[2],
                     emxArray_real_T *outputImage);
extern void imwarp(const emxArray_uint8_T *varargin_1, const double
                   varargin_3_T[9], const double varargin_6_ImageSize[2],
                   emxArray_uint8_T *outputImage);

#endif

/* End of code generation (imwarp.h) */
