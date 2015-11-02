/*
 * AlignWorker_v2.h
 *
 * Code generation for function 'AlignWorker_v2'
 *
 */

#ifndef __ALIGNWORKER_V2_H__
#define __ALIGNWORKER_V2_H__

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
extern void AlignWorker_v2_AlignWorker_v2(AlignWorker_v2 *obj);
extern boolean_T c_AlignWorker_v2_carryOutMatchi(AlignWorker_v2 *obj, const
  emxArray_real_T *triPatch, const emxArray_boolean_T *triPatchMask, double
  edgeLength);
extern void c_AlignWorker_v2_matchingIndivi(AlignWorker_v2 *obj);
extern void d_AlignWorker_v2_matchingIndivi(AlignWorker_v2 *obj);

#endif

/* End of code generation (AlignWorker_v2.h) */
