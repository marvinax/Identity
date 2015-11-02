/*
 * SystemCore.h
 *
 * Code generation for function 'SystemCore'
 *
 */

#ifndef __SYSTEMCORE_H__
#define __SYSTEMCORE_H__

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
extern void SystemCore_step(visioncodegen_Autothresholder *obj, const
  emxArray_uint8_T *varargin_1, emxArray_boolean_T *varargout_1, unsigned char
  *varargout_2);
extern void b_SystemCore_step(visioncodegen_LocalMaximaFinder *obj, const
  emxArray_real_T *varargin_1, unsigned int varargout_1_data[], int
  varargout_1_size[2]);
extern void c_SystemCore_step(visioncodegen_BlobAnalysis *obj, const boolean_T
  varargin_1[40000], int varargout_1_data[], int varargout_1_size[2], float
  varargout_2_data[], int varargout_2_size[2]);

#endif

/* End of code generation (SystemCore.h) */
