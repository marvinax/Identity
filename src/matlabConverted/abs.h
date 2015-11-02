/*
 * abs.h
 *
 * Code generation for function 'abs'
 *
 */

#ifndef __ABS_H__
#define __ABS_H__

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
extern void b_abs(const emxArray_real_T *x, emxArray_real_T *y);
extern void c_abs(const double x[8], double y[8]);
extern void d_abs(const double x[16], double y[16]);
extern void e_abs(const double x[169], double y[169]);

#endif

/* End of code generation (abs.h) */
