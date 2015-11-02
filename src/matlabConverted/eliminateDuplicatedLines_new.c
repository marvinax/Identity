/*
 * eliminateDuplicatedLines_new.c
 *
 * Code generation for function 'eliminateDuplicatedLines_new'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "eliminateDuplicatedLines_new.h"
#include "norm.h"
#include "groupParallelLines.h"
#include "median.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void eliminateDuplicatedLines_new(const e_struct_T lines_in_data[], const int
  lines_in_size[2], e_struct_T lines_ret_data[], int lines_ret_size[2], double
  *lineCnt_ret)
{
  int segmentLengths_size[1];
  int removalIdx;
  int i15;
  double segmentLengths_data[30];
  int i;
  double vec1[2];
  emxArray_real_T b_segmentLengths_data;
  double medianSegmentLengths;
  double thres_dist;
  int lineCnt_old;
  int lineCnt;
  boolean_T exitg1;
  int32_T exitg3;
  int j;
  int32_T exitg2;
  int b_j;
  double vec2[2];
  double d0;
  boolean_T guard1 = false;
  double x[4];

  /*  */
  /*  iteratively remove duplicated lines, and remove one dumplicated version */
  /*  in iteration. */
  /*  Chau-Wai Wong, Nov. 2014. */
  /* % determine threshold for considering as the same line or different lines */
  segmentLengths_size[0] = lines_in_size[1];
  removalIdx = lines_in_size[1];
  for (i15 = 0; i15 < removalIdx; i15++) {
    segmentLengths_data[i15] = 0.0;
  }

  for (i = 0; i < lines_in_size[1]; i++) {
    for (i15 = 0; i15 < 2; i15++) {
      vec1[i15] = lines_in_data[i].point1[i15] - lines_in_data[i].point2[i15];
    }

    segmentLengths_data[i] = b_norm(vec1);
  }

  b_segmentLengths_data.data = (double *)&segmentLengths_data;
  b_segmentLengths_data.size = (int *)&segmentLengths_size;
  b_segmentLengths_data.allocatedSize = 30;
  b_segmentLengths_data.numDimensions = 1;
  b_segmentLengths_data.canFreeData = false;
  medianSegmentLengths = median(&b_segmentLengths_data);
  thres_dist = 0.03 * medianSegmentLengths;

  /* % */
  lines_ret_size[0] = 1;
  lines_ret_size[1] = lines_in_size[1];
  removalIdx = lines_in_size[0] * lines_in_size[1];
  for (i15 = 0; i15 < removalIdx; i15++) {
    lines_ret_data[i15] = lines_in_data[i15];
  }

  lineCnt_old = 1000;
  lineCnt = lines_in_size[1];
  exitg1 = false;
  while ((!exitg1) && (lineCnt_old > lineCnt)) {
    lineCnt_old = lineCnt;

    /* % */
    lineCnt = lines_ret_size[1] - 1;
    i = 0;
    do {
      exitg3 = 0;
      if (i <= lineCnt) {
        j = 0;
        do {
          exitg2 = 0;
          if (j <= (lineCnt - i) - 1) {
            b_j = (i + j) + 1;
            for (i15 = 0; i15 < 2; i15++) {
              vec1[i15] = lines_ret_data[i].point1[i15] - lines_ret_data[i].
                point2[i15];
            }

            for (i15 = 0; i15 < 2; i15++) {
              vec2[i15] = lines_ret_data[b_j].point1[i15] - lines_ret_data[b_j].
                point2[i15];
            }

            medianSegmentLengths = 0.0;
            for (i15 = 0; i15 < 2; i15++) {
              medianSegmentLengths += vec1[i15] * vec2[i15];
            }

            medianSegmentLengths = fabs(acos(medianSegmentLengths / (b_norm(vec1)
              * b_norm(vec2))) / 3.1415926535897931 * 180.0);
            if ((180.0 - medianSegmentLengths <= medianSegmentLengths) ||
                rtIsNaN(medianSegmentLengths)) {
              d0 = 180.0 - medianSegmentLengths;
            } else {
              d0 = medianSegmentLengths;
            }

            guard1 = false;
            if (d0 < 10.0) {
              x[0] = fabs((lines_ret_data[b_j].param.alpha_hat *
                           lines_ret_data[i].point1[0] + lines_ret_data[b_j].
                           param.beta_hat * lines_ret_data[i].point1[1]) +
                          lines_ret_data[b_j].param.gamma_hat) / sqrt
                (lines_ret_data[b_j].param.alpha_hat * lines_ret_data[b_j].
                 param.alpha_hat + lines_ret_data[b_j].param.beta_hat *
                 lines_ret_data[b_j].param.beta_hat);
              x[1] = fabs((lines_ret_data[b_j].param.alpha_hat *
                           lines_ret_data[i].point2[0] + lines_ret_data[b_j].
                           param.beta_hat * lines_ret_data[i].point2[1]) +
                          lines_ret_data[b_j].param.gamma_hat) / sqrt
                (lines_ret_data[b_j].param.alpha_hat * lines_ret_data[b_j].
                 param.alpha_hat + lines_ret_data[b_j].param.beta_hat *
                 lines_ret_data[b_j].param.beta_hat);
              x[2] = fabs((lines_ret_data[i].param.alpha_hat *
                           lines_ret_data[b_j].point1[0] + lines_ret_data[i].
                           param.beta_hat * lines_ret_data[b_j].point1[1]) +
                          lines_ret_data[i].param.gamma_hat) / sqrt
                (lines_ret_data[i].param.alpha_hat * lines_ret_data[i].
                 param.alpha_hat + lines_ret_data[i].param.beta_hat *
                 lines_ret_data[i].param.beta_hat);
              x[3] = fabs((lines_ret_data[i].param.alpha_hat *
                           lines_ret_data[b_j].point2[0] + lines_ret_data[i].
                           param.beta_hat * lines_ret_data[b_j].point2[1]) +
                          lines_ret_data[i].param.gamma_hat) / sqrt
                (lines_ret_data[i].param.alpha_hat * lines_ret_data[i].
                 param.alpha_hat + lines_ret_data[i].param.beta_hat *
                 lines_ret_data[i].param.beta_hat);
              medianSegmentLengths = x[0];
              for (removalIdx = 0; removalIdx < 3; removalIdx++) {
                medianSegmentLengths += x[removalIdx + 1];
              }

              if (medianSegmentLengths / 4.0 < thres_dist) {
                /*  if two lines are the same, then remove the shorter one */
                for (i15 = 0; i15 < 2; i15++) {
                  vec1[i15] = lines_ret_data[i].point1[i15] - lines_ret_data[i].
                    point2[i15];
                }

                for (i15 = 0; i15 < 2; i15++) {
                  vec2[i15] = lines_ret_data[b_j].point1[i15] -
                    lines_ret_data[b_j].point2[i15];
                }

                if (b_norm(vec1) < b_norm(vec2)) {
                  removalIdx = i;
                } else {
                  removalIdx = b_j;
                }

                exitg2 = 2;
              } else {
                guard1 = true;
              }
            } else {
              guard1 = true;
            }

            if (guard1) {
              j++;
            }
          } else {
            i++;
            exitg2 = 1;
          }
        } while (exitg2 == 0);

        if (exitg2 == 1) {
        } else {
          exitg3 = 1;
        }
      } else {
        removalIdx = -2;
        exitg3 = 1;
      }
    } while (exitg3 == 0);

    if (removalIdx + 1 == -1) {
      exitg1 = true;
    } else {
      /*  no more dumplicated lines, return. */
      b_eml_null_assignment(lines_ret_data, lines_ret_size, removalIdx + 1);
      lineCnt = lines_ret_size[1];
    }
  }

  *lineCnt_ret = lines_ret_size[1];
}

/* End of code generation (eliminateDuplicatedLines_new.c) */
