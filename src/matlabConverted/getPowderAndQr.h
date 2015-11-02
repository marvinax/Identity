/*
 * getPowderAndQr.h
 *
 * Code generation for function 'getPowderAndQr'
 *
 */

#ifndef __GETPOWDERANDQR_H__
#define __GETPOWDERANDQR_H__

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
extern void getPowderAndQr(const emxArray_real_T *reducedSizeImg, const
  emxArray_boolean_T *reducedSizeMask, double edgeLength, unsigned char
  debugMode, emxArray_real_T *imgPowder, emxArray_real_T *imgQr, boolean_T
  *successFlag);

#endif

/* End of code generation (getPowderAndQr.h) */
