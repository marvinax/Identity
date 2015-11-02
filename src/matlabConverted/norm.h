/*
 * norm.h
 *
 * Code generation for function 'norm'
 *
 */

#ifndef __NORM_H__
#define __NORM_H__

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
extern double b_norm(const double x[2]);
extern double c_norm(const double x[2]);
extern double d_norm(const double x[9]);
extern double norm(const double x[36]);

#endif

/* End of code generation (norm.h) */
