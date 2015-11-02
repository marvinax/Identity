/*
 * interp2d.h
 *
 * Code generation for function 'interp2d'
 *
 */

#ifndef __INTERP2D_H__
#define __INTERP2D_H__

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
extern void interp2d(const emxArray_real_T *inputImage, emxArray_real_T *X,
                     emxArray_real_T *Y, emxArray_real_T *outputImage);

#endif

/* End of code generation (interp2d.h) */
