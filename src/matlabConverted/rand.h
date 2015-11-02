/*
 * rand.h
 *
 * Code generation for function 'rand'
 *
 */

#ifndef __RAND_H__
#define __RAND_H__

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
extern void b_rand(double r[6000]);
extern void c_rand(double varargin_1, emxArray_real_T *r);
extern void d_rand(double r[3000]);

#endif

/* End of code generation (rand.h) */
