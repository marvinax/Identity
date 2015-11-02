/*
 * histc.h
 *
 * Code generation for function 'histc'
 *
 */

#ifndef __HISTC_H__
#define __HISTC_H__

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
extern void histc(const emxArray_real_T *X, const double edges[257], double N
                  [257]);

#endif

/* End of code generation (histc.h) */
