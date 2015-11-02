/*
 * patchCorr.h
 *
 * Code generation for function 'patchCorr'
 *
 */

#ifndef __PATCHCORR_H__
#define __PATCHCORR_H__

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
extern void b_patchCorr(const emxArray_uint8_T *trueImg, const unsigned char
  testImg_data[], const int testImg_size[2], double sWinSize, double
  *corrVal_max, double *bestMatchedPoint_x, double *bestMatchedPoint_y,
  emxArray_real_T *corrMap_val, emxArray_real_T *corrMap_x, emxArray_real_T
  *corrMap_y);
extern void patchCorr(const emxArray_uint8_T *trueImg, const unsigned char
                      testImg_data[], const int testImg_size[2], double
                      *corrVal_max, double *bestMatchedPoint_x, double
                      *bestMatchedPoint_y, double corrMap_val[441], double
                      corrMap_x[441], double corrMap_y[441]);

#endif

/* End of code generation (patchCorr.h) */
