/*
 * groupParallelLines.h
 *
 * Code generation for function 'groupParallelLines'
 *
 */

#ifndef __GROUPPARALLELLINES_H__
#define __GROUPPARALLELLINES_H__

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
extern void b_eml_null_assignment(e_struct_T x_data[], int x_size[2], double idx);
extern void groupParallelLines(e_struct_T lines_data[], int lines_size[2],
  f_struct_T group_data[], int group_size[1], double groupOrientation_data[],
  int groupOrientation_size[1]);

#endif

/* End of code generation (groupParallelLines.h) */
