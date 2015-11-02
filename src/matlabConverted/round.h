/*
 * round.h
 *
 * Code generation for function 'round'
 *
 */

#ifndef __ROUND_H__
#define __ROUND_H__

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
extern void b_round(emxArray_real_T *x);
extern void c_round(double x[6000]);
extern void d_round(double x[3000]);

#endif

/* End of code generation (round.h) */
