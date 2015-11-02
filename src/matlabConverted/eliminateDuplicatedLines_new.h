/*
 * eliminateDuplicatedLines_new.h
 *
 * Code generation for function 'eliminateDuplicatedLines_new'
 *
 */

#ifndef __ELIMINATEDUPLICATEDLINES_NEW_H__
#define __ELIMINATEDUPLICATEDLINES_NEW_H__

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
extern void eliminateDuplicatedLines_new(const e_struct_T lines_in_data[], const
  int lines_in_size[2], e_struct_T lines_ret_data[], int lines_ret_size[2],
  double *lineCnt_ret);

#endif

/* End of code generation (eliminateDuplicatedLines_new.h) */
