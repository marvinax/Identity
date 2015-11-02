/*
 * groupParallelLines.c
 *
 * Code generation for function 'groupParallelLines'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "groupParallelLines.h"
#include "norm.h"
#include "sortLinesInOrder.h"
#include "getPowderAndQr_emxutil.h"
#include "getPowderAndQr_rtwutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Declarations */
static void c_eml_null_assignment(f_struct_T x_data[], int x_size[1], const
  double idx_data[], const int idx_size[2]);
static double getAngleOfTwoUndirectedLines(double ln_param_alpha_hat, double
  ln_param_beta_hat, double angleInDegree);
static double getAveGroupOrient(const e_struct_T ln_struct_data[], const int
  ln_struct_size[1]);
static double getLineOrient(double singleLine_param_alpha_hat, double
  singleLine_param_beta_hat);

/* Function Definitions */
static void c_eml_null_assignment(f_struct_T x_data[], int x_size[1], const
  double idx_data[], const int idx_size[2])
{
  int k;
  emxArray_struct_T_10 x;
  boolean_T b_data[30];
  int n;
  int k0;
  if (idx_size[1] == 1) {
    for (k = (int)idx_data[0]; k < 10; k++) {
      x_data[k - 1] = x_data[k];
    }

    for (k = 0; k < 9; k++) {
      x.data[k] = x_data[k];
    }

    x_size[0] = 9;
    for (k = 0; k < 9; k++) {
      x_data[k] = x.data[k];
    }
  } else {
    for (k = 0; k < 10; k++) {
      b_data[k] = false;
    }

    for (k = 1; k <= idx_size[1]; k++) {
      b_data[(int)idx_data[k - 1] - 1] = true;
    }

    n = 0;
    for (k = 1; k < 11; k++) {
      n += b_data[k - 1];
    }

    k0 = -1;
    for (k = 0; k < 10; k++) {
      if (!b_data[k]) {
        k0++;
        x_data[k0] = x_data[k];
      }
    }

    if (1 > 10 - n) {
      n = 0;
    } else {
      n = 10 - n;
    }

    for (k = 0; k < n; k++) {
      x.data[k] = x_data[k];
    }

    x_size[0] = n;
    for (k = 0; k < n; k++) {
      x_data[k] = x.data[k];
    }
  }
}

static double getAngleOfTwoUndirectedLines(double ln_param_alpha_hat, double
  ln_param_beta_hat, double angleInDegree)
{
  double vecLn[2];
  double B;
  double angleInRad;
  double dv2[2];
  int i16;
  vecLn[0] = ln_param_beta_hat;
  vecLn[1] = ln_param_alpha_hat;
  B = c_norm(vecLn);
  angleInRad = angleInDegree / 180.0 * 3.1415926535897931;
  dv2[0] = cos(angleInRad);
  dv2[1] = sin(angleInRad);
  angleInRad = 0.0;
  for (i16 = 0; i16 < 2; i16++) {
    angleInRad += vecLn[i16] / B * dv2[i16];
  }

  return acos(fabs(angleInRad)) / 3.1415926535897931 * 180.0;
}

static double getAveGroupOrient(const e_struct_T ln_struct_data[], const int
  ln_struct_size[1])
{
  double orient;
  int loop_ub;
  int i17;
  creal_T complexNum_data[30];
  double vec1[2];
  double B;
  double vec_i[2];
  double vectorSign;
  double im;

  /*  angle unit in degree */
  loop_ub = ln_struct_size[0];
  for (i17 = 0; i17 < loop_ub; i17++) {
    complexNum_data[i17].re = 0.0;
    complexNum_data[i17].im = 0.0;
  }

  vec1[0] = ln_struct_data[0].param.beta_hat;
  vec1[1] = ln_struct_data[0].param.alpha_hat;
  B = c_norm(vec1);
  for (i17 = 0; i17 < 2; i17++) {
    vec1[i17] /= B;
  }

  for (loop_ub = 0; loop_ub < ln_struct_size[0]; loop_ub++) {
    vec_i[0] = ln_struct_data[loop_ub].param.beta_hat;
    vec_i[1] = ln_struct_data[loop_ub].param.alpha_hat;
    B = c_norm(vec_i);
    vectorSign = 0.0;
    for (i17 = 0; i17 < 2; i17++) {
      im = vec_i[i17] / B;
      vectorSign += vec1[i17] * im;
      vec_i[i17] = im;
    }

    if (vectorSign < 0.0) {
      vectorSign = -1.0;
    } else if (vectorSign > 0.0) {
      vectorSign = 1.0;
    } else {
      if (vectorSign == 0.0) {
        vectorSign = 0.0;
      }
    }

    if (vectorSign == 0.0) {
      vectorSign = 1.0;
    }

    B = 0.0;
    im = 0.0;
    for (i17 = 0; i17 < 2; i17++) {
      B += (1.0 - (double)i17) * vec_i[i17];
      im += (double)i17 * vec_i[i17];
    }

    complexNum_data[loop_ub].re = vectorSign * B;
    complexNum_data[loop_ub].im = vectorSign * im;

    /*  the direction of line_i's should be acute angle */
  }

  B = complexNum_data[0].re;
  vectorSign = complexNum_data[0].im;
  for (loop_ub = 2; loop_ub <= ln_struct_size[0]; loop_ub++) {
    B += complexNum_data[loop_ub - 1].re;
    vectorSign += complexNum_data[loop_ub - 1].im;
  }

  if (vectorSign == 0.0) {
    B /= (double)ln_struct_size[0];
    vectorSign = 0.0;
  } else if (B == 0.0) {
    B = 0.0;
    vectorSign /= (double)ln_struct_size[0];
  } else {
    B /= (double)ln_struct_size[0];
    vectorSign /= (double)ln_struct_size[0];
  }

  orient = rt_atan2d_snf(vectorSign, B) / 3.1415926535897931 * 180.0;
  if (orient > 90.0) {
    orient -= 180.0;
  }

  return orient;
}

static double getLineOrient(double singleLine_param_alpha_hat, double
  singleLine_param_beta_hat)
{
  /*  angle unit in degree */
  return rt_atan2d_snf(singleLine_param_alpha_hat, singleLine_param_beta_hat) /
    3.1415926535897931 * 180.0;
}

void b_eml_null_assignment(e_struct_T x_data[], int x_size[2], double idx)
{
  int loop_ub;
  int i50;
  e_struct_T b_x_data[30];
  e_struct_T c_x_data[30];
  loop_ub = x_size[0] * x_size[1];
  for (i50 = 0; i50 < loop_ub; i50++) {
    b_x_data[i50] = x_data[i50];
  }

  for (loop_ub = (int)idx; loop_ub < x_size[1]; loop_ub++) {
    b_x_data[loop_ub - 1] = b_x_data[loop_ub];
  }

  if (1 > x_size[1] - 1) {
    loop_ub = 0;
  } else {
    loop_ub = x_size[1] - 1;
  }

  for (i50 = 0; i50 < loop_ub; i50++) {
    c_x_data[i50] = b_x_data[i50];
  }

  for (i50 = 0; i50 < loop_ub; i50++) {
    b_x_data[i50] = c_x_data[i50];
  }

  x_size[0] = 1;
  x_size[1] = loop_ub;
  for (i50 = 0; i50 < loop_ub; i50++) {
    x_data[x_size[0] * i50] = b_x_data[i50];
  }
}

void groupParallelLines(e_struct_T lines_data[], int lines_size[2], f_struct_T
  group_data[], int group_size[1], double groupOrientation_data[], int
  groupOrientation_size[1])
{
  f_struct_T y[10];
  int k0;
  int k;
  int groupSize;
  emxArray_real_T *angleArr;
  int nxout;
  int n;
  double mtmp;
  boolean_T exitg1;
  double b_groupOrientation_data[10];
  double groupSize_data[9];
  int groupSize_size[2];
  int c_groupRemovalIndexList_size_id;
  double groupRemovalIndexList_data[10];
  emxArray_struct_T_10 r16;
  emxArray_struct_T_10 r17;
  int unnamed_idx_1;
  boolean_T b_data[10];
  int loop_ub;
  double tmp_data[10];

  /* % Group lines using 1-nearest neighbor, and remove single-line groups */
  /*   Chau-Wai Wong, Feb. 2015 */
  /* groupOrientation = zeros(1,0); */
  /* group = {}; */
  /*  put the first line to the first group */
  groupOrientation_size[0] = 1;
  groupOrientation_data[0] = getLineOrient(lines_data[lines_size[1] - 1].
    param.alpha_hat, lines_data[lines_size[1] - 1].param.beta_hat);

  /*  normally 2 */
  for (k0 = 0; k0 < 10; k0++) {
    y[k0].data.size[0] = 1;
    y[k0].data.data[0] = lines_data[lines_size[1] - 1];
  }

  group_size[0] = 10;
  for (k = 0; k < 10; k++) {
    group_data[k] = y[k];
  }

  groupSize = 0;

  /*  normally 6 */
  b_eml_null_assignment(lines_data, lines_size, lines_size[1]);

  /*  starting from the 2nd line, assign to an old group or a new group */
  b_emxInit_real_T(&angleArr, 1);
  while (!(lines_size[1] == 0)) {
    k = angleArr->size[0];
    angleArr->size[0] = groupOrientation_size[0];
    emxEnsureCapacity((emxArray__common *)angleArr, k, (int)sizeof(double));
    nxout = groupOrientation_size[0];
    for (k = 0; k < nxout; k++) {
      angleArr->data[k] = 0.0;
    }

    for (k0 = 0; k0 < groupOrientation_size[0]; k0++) {
      angleArr->data[k0] = getAngleOfTwoUndirectedLines(lines_data[lines_size[1]
        - 1].param.alpha_hat, lines_data[lines_size[1] - 1].param.beta_hat,
        groupOrientation_data[k0]);
    }

    k0 = 1;
    n = angleArr->size[0];
    mtmp = angleArr->data[0];
    k = 0;
    if (angleArr->size[0] > 1) {
      if (rtIsNaN(angleArr->data[0])) {
        nxout = 1;
        exitg1 = false;
        while ((!exitg1) && (nxout + 1 <= n)) {
          k0 = nxout + 1;
          if (!rtIsNaN(angleArr->data[nxout])) {
            mtmp = angleArr->data[nxout];
            k = nxout;
            exitg1 = true;
          } else {
            nxout++;
          }
        }
      }

      if (k0 < angleArr->size[0]) {
        while (k0 + 1 <= n) {
          if (angleArr->data[k0] < mtmp) {
            mtmp = angleArr->data[k0];
            k = k0;
          }

          k0++;
        }
      }
    }

    if (mtmp < 15.0) {
      /*  angle different in degree */
      /*  if angle between the test line and mean direction of current group is */
      /*  similar, then set the line to the current group. */
      k0 = group_data[k].data.size[0];
      group_data[k].data.size[0] = k0 + 1;
      group_data[k].data.data[k0] = lines_data[lines_size[1] - 1];
      groupOrientation_data[k] = getAveGroupOrient(group_data[k].data.data,
        group_data[k].data.size);
    } else {
      /*  if not, set the test line to a new group. */
      /* group(end+1).data = ln; */
      groupSize++;
      group_data[groupSize].data.size[0] = 1;
      group_data[groupSize].data.data[0] = lines_data[lines_size[1] - 1];

      /*  angle unit in degree */
      k0 = groupOrientation_size[0] + 1;
      nxout = groupOrientation_size[0];
      for (k = 0; k < nxout; k++) {
        b_groupOrientation_data[k] = groupOrientation_data[k];
      }

      b_groupOrientation_data[groupOrientation_size[0]] = rt_atan2d_snf
        (lines_data[lines_size[1] - 1].param.alpha_hat, lines_data[lines_size[1]
         - 1].param.beta_hat) / 3.1415926535897931 * 180.0;
      groupOrientation_size[0] = k0;
      for (k = 0; k < k0; k++) {
        groupOrientation_data[k] = b_groupOrientation_data[k];
      }
    }

    b_eml_null_assignment(lines_data, lines_size, lines_size[1]);
  }

  emxFree_real_T(&angleArr);

  /*  remove extra group elments that are pre-assigned */
  if (groupSize + 2 <= 10) {
    groupSize_size[0] = 1;
    groupSize_size[1] = (int)(10.0 - ((double)(groupSize + 1) + 1.0)) + 1;
    nxout = (int)(10.0 - ((double)(groupSize + 1) + 1.0));
    for (k = 0; k <= nxout; k++) {
      groupSize_data[k] = ((double)(groupSize + 1) + 1.0) + (double)k;
    }

    c_eml_null_assignment(group_data, group_size, groupSize_data, groupSize_size);
  }

  /*  remove one-element group (one-element group cannot intersect with another */
  /*  group to have at least 4 corner points) */
  c_groupRemovalIndexList_size_id = 0;
  for (k0 = 0; k0 <= groupSize; k0++) {
    if (group_data[k0].data.size[0] < 2) {
      /* groupRemovalIndexList(end+1) = i; */
      nxout = c_groupRemovalIndexList_size_id;
      c_groupRemovalIndexList_size_id++;
      groupRemovalIndexList_data[nxout] = 1.0 + (double)k0;
    }
  }

  if (!(c_groupRemovalIndexList_size_id == 0)) {
    r16.size[0] = group_size[0];
    nxout = group_size[0];
    for (k = 0; k < nxout; k++) {
      r16.data[k] = group_data[k];
    }

    groupSize = group_size[0];
    if (c_groupRemovalIndexList_size_id == 1) {
      for (k = (int)groupRemovalIndexList_data[0]; k < groupSize; k++) {
        r16.data[k - 1] = r16.data[k];
      }

      if (r16.size[0] != 1) {
        if (1 > group_size[0] - 1) {
          nxout = 0;
        } else {
          nxout = group_size[0] - 1;
        }

        for (k = 0; k < nxout; k++) {
          r17.data[k] = r16.data[k];
        }

        r16.size[0] = nxout;
        for (k = 0; k < nxout; k++) {
          r16.data[k] = r17.data[k];
        }
      } else {
        if (1 > group_size[0] - 1) {
          nxout = -1;
        } else {
          nxout = 0;
        }

        k = 0;
        while (k <= nxout) {
          r17.data[0] = r16.data[0];
          k = 1;
        }

        r16.size[0] = nxout + 1;
        nxout++;
        k = 0;
        while (k <= nxout - 1) {
          r16.data[0] = r17.data[0];
          k = 1;
        }
      }
    } else {
      unnamed_idx_1 = group_size[0];
      nxout = group_size[0];
      for (k = 0; k < nxout; k++) {
        b_data[k] = false;
      }

      for (k = 1; k <= c_groupRemovalIndexList_size_id; k++) {
        b_data[(int)groupRemovalIndexList_data[k - 1] - 1] = true;
      }

      n = 0;
      for (k = 1; k <= unnamed_idx_1; k++) {
        n += b_data[k - 1];
      }

      nxout = group_size[0] - n;
      k0 = -1;
      for (k = 1; k <= groupSize; k++) {
        if ((k > unnamed_idx_1) || (!b_data[k - 1])) {
          k0++;
          r16.data[k0] = r16.data[k - 1];
        }
      }

      if (r16.size[0] != 1) {
        if (1 > nxout) {
          nxout = 0;
        }

        for (k = 0; k < nxout; k++) {
          r17.data[k] = r16.data[k];
        }

        r16.size[0] = nxout;
        for (k = 0; k < nxout; k++) {
          r16.data[k] = r17.data[k];
        }
      } else {
        if (1 > nxout) {
          nxout = -1;
        } else {
          nxout = 0;
        }

        k = 0;
        while (k <= nxout) {
          r17.data[0] = r16.data[0];
          k = 1;
        }

        r16.size[0] = nxout + 1;
        nxout++;
        k = 0;
        while (k <= nxout - 1) {
          r16.data[0] = r17.data[0];
          k = 1;
        }
      }
    }

    group_size[0] = r16.size[0];
    nxout = r16.size[0];
    for (k = 0; k < nxout; k++) {
      group_data[k] = r16.data[k];
    }

    loop_ub = groupOrientation_size[0];
    nxout = groupOrientation_size[0];
    for (k = 0; k < nxout; k++) {
      tmp_data[k] = groupOrientation_data[k];
    }

    groupSize = groupOrientation_size[0];
    if (c_groupRemovalIndexList_size_id == 1) {
      for (k = (int)groupRemovalIndexList_data[0]; k < groupSize; k++) {
        tmp_data[k - 1] = tmp_data[k];
      }

      if (loop_ub != 1) {
        if (1 > groupOrientation_size[0] - 1) {
          loop_ub = 0;
        } else {
          loop_ub = groupOrientation_size[0] - 1;
        }

        for (k = 0; k < loop_ub; k++) {
          groupRemovalIndexList_data[k] = tmp_data[k];
        }

        for (k = 0; k < loop_ub; k++) {
          tmp_data[k] = groupRemovalIndexList_data[k];
        }
      } else {
        if (1 > groupOrientation_size[0] - 1) {
          nxout = -1;
        } else {
          nxout = 0;
        }

        k = 0;
        while (k <= nxout) {
          groupRemovalIndexList_data[0] = tmp_data[0];
          k = 1;
        }

        loop_ub = nxout + 1;
        nxout++;
        k = 0;
        while (k <= nxout - 1) {
          tmp_data[0] = groupRemovalIndexList_data[0];
          k = 1;
        }
      }
    } else {
      unnamed_idx_1 = groupOrientation_size[0];
      nxout = groupOrientation_size[0];
      for (k = 0; k < nxout; k++) {
        b_data[k] = false;
      }

      for (k = 1; k <= c_groupRemovalIndexList_size_id; k++) {
        b_data[(int)groupRemovalIndexList_data[k - 1] - 1] = true;
      }

      n = 0;
      for (k = 1; k <= unnamed_idx_1; k++) {
        n += b_data[k - 1];
      }

      nxout = groupOrientation_size[0] - n;
      k0 = -1;
      for (k = 1; k <= groupSize; k++) {
        if ((k > unnamed_idx_1) || (!b_data[k - 1])) {
          k0++;
          tmp_data[k0] = tmp_data[k - 1];
        }
      }

      if (loop_ub != 1) {
        if (1 > nxout) {
          loop_ub = 0;
        } else {
          loop_ub = nxout;
        }

        for (k = 0; k < loop_ub; k++) {
          groupRemovalIndexList_data[k] = tmp_data[k];
        }

        for (k = 0; k < loop_ub; k++) {
          tmp_data[k] = groupRemovalIndexList_data[k];
        }
      } else {
        if (1 > nxout) {
          nxout = -1;
        } else {
          nxout = 0;
        }

        k = 0;
        while (k <= nxout) {
          groupRemovalIndexList_data[0] = tmp_data[0];
          k = 1;
        }

        loop_ub = nxout + 1;
        nxout++;
        k = 0;
        while (k <= nxout - 1) {
          tmp_data[0] = groupRemovalIndexList_data[0];
          k = 1;
        }
      }
    }

    groupOrientation_size[0] = loop_ub;
    for (k = 0; k < loop_ub; k++) {
      groupOrientation_data[k] = tmp_data[k];
    }
  }
}

/* End of code generation (groupParallelLines.c) */
