/*
 * pickOutAPossiblePairOfGroups.h
 *
 * Code generation for function 'pickOutAPossiblePairOfGroups'
 *
 */

#ifndef __PICKOUTAPOSSIBLEPAIROFGROUPS_H__
#define __PICKOUTAPOSSIBLEPAIROFGROUPS_H__

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
extern void pickOutAPossiblePairOfGroups(const f_struct_T group_data[], const
  double groupOrientation_data[], const int groupOrientation_size[1], e_struct_T
  groupPair_groupA_data[], int groupPair_groupA_size[1], e_struct_T
  groupPair_groupB_data[], int groupPair_groupB_size[1], boolean_T *success);

#endif

/* End of code generation (pickOutAPossiblePairOfGroups.h) */
