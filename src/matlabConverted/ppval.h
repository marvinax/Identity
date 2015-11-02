/*
 * ppval.h
 *
 * Code generation for function 'ppval'
 *
 */

#ifndef __PPVAL_H__
#define __PPVAL_H__

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
extern void ppval(const emxArray_real_T *pp_breaks, const emxArray_real_T
                  *pp_coefs, double x, emxArray_real_T *v);

#endif

/* End of code generation (ppval.h) */
