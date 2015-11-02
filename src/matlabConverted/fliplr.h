/*
 * fliplr.h
 *
 * Code generation for function 'fliplr'
 *
 */

#ifndef __FLIPLR_H__
#define __FLIPLR_H__

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
extern void b_fliplr(boolean_T x[1024]);
extern void c_fliplr(boolean_T x[441]);
extern void fliplr(unsigned int x_data[], int x_size[2]);

#endif

/* End of code generation (fliplr.h) */
