/*
 * repmat.h
 *
 * Code generation for function 'repmat'
 *
 */

#ifndef __REPMAT_H__
#define __REPMAT_H__

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
extern void repmat(const double a_data[], const int a_size[1], double b_data[],
                   int b_size[2]);

#endif

/* End of code generation (repmat.h) */