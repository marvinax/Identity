/*
 * power.h
 *
 * Code generation for function 'power'
 *
 */

#ifndef __POWER_H__
#define __POWER_H__

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
extern void b_power(const double a[6], double y[6]);
extern void c_power(const emxArray_real_T *a, emxArray_real_T *y);
extern void d_power(const double a[1024], double y[1024]);
extern void e_power(const emxArray_real32_T *a, emxArray_real32_T *y);
extern void power(const emxArray_real_T *a, emxArray_real_T *y);

#endif

/* End of code generation (power.h) */
