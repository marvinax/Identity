/*
 * findFourLines_v2.h
 *
 * Code generation for function 'findFourLines_v2'
 *
 */

#ifndef __FINDFOURLINES_V2_H__
#define __FINDFOURLINES_V2_H__

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
extern void findFourLines_v2(const emxArray_uint8_T *im, const
  emxArray_boolean_T *mask, double edgeLength, double thres, double *figIdx,
  e_struct_T lines_data[], int lines_size[2]);

#endif

/* End of code generation (findFourLines_v2.h) */
