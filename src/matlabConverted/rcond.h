/*
 * rcond.h
 *
 * Code generation for function 'rcond'
 *
 */

#ifndef __RCOND_H__
#define __RCOND_H__

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
extern double b_rcond(const double A[9]);
extern double rcond(const double A[36]);

#endif

/* End of code generation (rcond.h) */
