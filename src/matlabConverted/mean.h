/*
 * mean.h
 *
 * Code generation for function 'mean'
 *
 */

#ifndef __MEAN_H__
#define __MEAN_H__

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
extern void b_mean(const double x_data[], const int x_size[2], double y[2]);
extern double c_mean(const double x[16]);
extern double d_mean(const double x[8]);
extern double e_mean(const double x[169]);
extern double mean(const emxArray_real_T *x);

#endif

/* End of code generation (mean.h) */
