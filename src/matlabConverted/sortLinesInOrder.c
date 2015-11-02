/*
 * sortLinesInOrder.c
 *
 * Code generation for function 'sortLinesInOrder'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "sortLinesInOrder.h"
#include "norm.h"
#include "det.h"
#include "eml_sort.h"
#include "mean.h"
#include "getPowderAndQr_rtwutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void c_sortLinesAccordingToIntersect(e_struct_T ln_struct_data[], int
  ln_struct_size[1], e_struct_T ln_struct_ret_data[], int ln_struct_ret_size[1])
{
  int cnt;
  int i;
  double pc[2];
  double ln_struct[2];
  double theta;
  int ar;
  int abVec_arr_size[2];
  double abVec_arr_data[60];
  double abVec_tilde[2];
  int catArr2_size_idx_0;
  double catArr2_data[60];
  double b_abVec_arr_data[120];
  int b_abVec_arr_size[2];
  int br;
  double orthoLine_point2[2];
  double intersectedPointsSet_data[60];
  double b_ln_struct[4];
  double det_p2;
  double delta_x1;
  double delta_y1;
  double delta_x2;
  double delta_y2;
  double b_delta_x1[4];
  double deno;
  int projectedPositions_size[2];
  double projectedPositions_data[30];
  int ic;
  int ia;
  int iidx_data[30];
  double unusedU0_data[30];
  cnt = ln_struct_size[0];

  /*  unify the direction of the lines */
  for (i = 1; i - 1 <= cnt - 2; i++) {
    /*  change the direction of line 2 if line 1 and line 2 are greater than 90. */
    pc[0] = ln_struct_data[0].param.alpha_hat;
    pc[1] = ln_struct_data[0].param.beta_hat;
    ln_struct[0] = ln_struct_data[i].param.alpha_hat;
    ln_struct[1] = ln_struct_data[i].param.beta_hat;
    theta = 0.0;
    for (ar = 0; ar < 2; ar++) {
      theta += pc[ar] * ln_struct[ar];
    }

    if (theta < -theta) {
      ln_struct_data[i].param.alpha_hat = -ln_struct_data[i].param.alpha_hat;
      ln_struct_data[i].param.beta_hat = -ln_struct_data[i].param.beta_hat;
      ln_struct_data[i].param.gamma_hat = -ln_struct_data[i].param.gamma_hat;
    }
  }

  /*  obtain an averaged direction, quantified by a_tilde, b_tilde */
  abVec_arr_size[0] = ln_struct_size[0];
  abVec_arr_size[1] = 2;
  i = ln_struct_size[0] << 1;
  for (ar = 0; ar < i; ar++) {
    abVec_arr_data[ar] = 0.0;
  }

  for (i = 0; i < cnt; i++) {
    abVec_tilde[0] = ln_struct_data[i].param.alpha_hat;
    abVec_tilde[1] = ln_struct_data[i].param.beta_hat;
    theta = b_norm(abVec_tilde);
    for (ar = 0; ar < 2; ar++) {
      abVec_arr_data[i + cnt * ar] = abVec_tilde[ar] / theta;
    }
  }

  b_mean(abVec_arr_data, abVec_arr_size, abVec_tilde);

  /*  get a center - pc */
  /*  pc = mean([cat(1,ln_struct.point1); cat(1,ln_struct.point2)]); */
  abVec_arr_size[0] = ln_struct_size[0];
  i = ln_struct_size[0] << 1;
  for (ar = 0; ar < i; ar++) {
    abVec_arr_data[ar] = 0.0;
  }

  for (i = 0; i < ln_struct_size[0]; i++) {
    for (ar = 0; ar < 2; ar++) {
      abVec_arr_data[i + abVec_arr_size[0] * ar] = ln_struct_data[i].point1[ar];
    }
  }

  catArr2_size_idx_0 = ln_struct_size[0];
  i = ln_struct_size[0] << 1;
  for (ar = 0; ar < i; ar++) {
    catArr2_data[ar] = 0.0;
  }

  for (i = 0; i < ln_struct_size[0]; i++) {
    for (ar = 0; ar < 2; ar++) {
      catArr2_data[i + catArr2_size_idx_0 * ar] = ln_struct_data[i].point2[ar];
    }
  }

  b_abVec_arr_size[0] = ln_struct_size[0] + ln_struct_size[0];
  b_abVec_arr_size[1] = 2;
  for (ar = 0; ar < 2; ar++) {
    i = abVec_arr_size[0];
    for (br = 0; br < i; br++) {
      b_abVec_arr_data[br + b_abVec_arr_size[0] * ar] = abVec_arr_data[br +
        abVec_arr_size[0] * ar];
    }
  }

  for (ar = 0; ar < 2; ar++) {
    for (br = 0; br < catArr2_size_idx_0; br++) {
      b_abVec_arr_data[(br + abVec_arr_size[0]) + b_abVec_arr_size[0] * ar] =
        catArr2_data[br + catArr2_size_idx_0 * ar];
    }
  }

  b_mean(b_abVec_arr_data, b_abVec_arr_size, pc);

  /*  get another point - ps - along the line passing pc with a slope of */
  /*  b_tilde/a_tilde, we call it the orthogonal line */
  /*  ps_x = pc(1)+1; ps_y = abVec_tilde(2)/abVec_tilde(1)*(ps_x-pc(1)) + */
  /*  pc(2); this point has a problem when abVec_tilde(1)==0 */
  orthoLine_point2[0] = pc[0] + abVec_tilde[0];
  orthoLine_point2[1] = pc[1] + abVec_tilde[1];

  /*  solve for the intersections of the orthogonal line with the given lines */
  i = ln_struct_size[0] << 1;
  for (ar = 0; ar < i; ar++) {
    intersectedPointsSet_data[ar] = 0.0;
  }

  for (i = 0; i < cnt; i++) {
    /*  Derivations see my handwritten notes. All points are stored in column */
    /*  vector form. */
    /*  Chau-Wai Wong, Oct. 2014 */
    for (ar = 0; ar < 2; ar++) {
      b_ln_struct[ar] = ln_struct_data[i].point1[ar];
    }

    for (ar = 0; ar < 2; ar++) {
      b_ln_struct[2 + ar] = ln_struct_data[i].point2[ar];
    }

    theta = det(b_ln_struct);
    for (ar = 0; ar < 2; ar++) {
      b_ln_struct[ar] = pc[ar];
      b_ln_struct[2 + ar] = orthoLine_point2[ar];
    }

    det_p2 = det(b_ln_struct);
    delta_x1 = ln_struct_data[i].point1[0] - ln_struct_data[i].point2[0];
    delta_y1 = ln_struct_data[i].point1[1] - ln_struct_data[i].point2[1];
    delta_x2 = pc[0] - orthoLine_point2[0];
    delta_y2 = pc[1] - orthoLine_point2[1];
    b_delta_x1[0] = delta_x1;
    b_delta_x1[2] = delta_x2;
    b_delta_x1[1] = delta_y1;
    b_delta_x1[3] = delta_y2;
    deno = -det(b_delta_x1);
    intersectedPointsSet_data[i << 1] = -(theta * delta_x2 - det_p2 * delta_x1) /
      deno;
    intersectedPointsSet_data[1 + (i << 1)] = -(theta * delta_y2 - det_p2 *
      delta_y1) / deno;
  }

  /*  rotate the intersected points along the  orthogonal line to the x-axis */
  theta = rt_atan2d_snf(abVec_tilde[1], abVec_tilde[0]);
  abVec_tilde[0] = cos(theta);
  abVec_tilde[1] = sin(theta);
  projectedPositions_size[0] = 1;
  projectedPositions_size[1] = ln_struct_size[0];
  i = ln_struct_size[0];
  for (ar = 0; ar < i; ar++) {
    projectedPositions_data[ar] = 0.0;
  }

  for (i = 0; i < cnt; i++) {
    for (ic = i; ic + 1 <= i + 1; ic++) {
      projectedPositions_data[ic] = 0.0;
    }
  }

  br = 0;
  for (i = 0; i < cnt; i++) {
    ar = 0;
    for (catArr2_size_idx_0 = br; catArr2_size_idx_0 + 1 <= br + 2;
         catArr2_size_idx_0++) {
      if (intersectedPointsSet_data[catArr2_size_idx_0] != 0.0) {
        ia = ar;
        for (ic = i; ic + 1 <= i + 1; ic++) {
          ia++;
          projectedPositions_data[ic] +=
            intersectedPointsSet_data[catArr2_size_idx_0] * abVec_tilde[ia - 1];
        }
      }

      ar++;
    }

    br += 2;
  }

  /*  obtain the order of the given lines indicated by the projected positions */
  eml_sort(projectedPositions_data, projectedPositions_size, unusedU0_data,
           abVec_arr_size, iidx_data, b_abVec_arr_size);

  /*  reorder the given lines */
  ln_struct_ret_size[0] = b_abVec_arr_size[1];
  i = b_abVec_arr_size[1];
  for (ar = 0; ar < i; ar++) {
    ln_struct_ret_data[ar] = ln_struct_data[iidx_data[b_abVec_arr_size[0] * ar]
      - 1];
  }
}

/* End of code generation (sortLinesInOrder.c) */
