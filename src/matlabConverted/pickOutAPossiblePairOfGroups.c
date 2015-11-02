/*
 * pickOutAPossiblePairOfGroups.c
 *
 * Code generation for function 'pickOutAPossiblePairOfGroups'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "pickOutAPossiblePairOfGroups.h"
#include "getPowderAndQr_emxutil.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void pickOutAPossiblePairOfGroups(const f_struct_T group_data[], const double
  groupOrientation_data[], const int groupOrientation_size[1], e_struct_T
  groupPair_groupA_data[], int groupPair_groupA_size[1], e_struct_T
  groupPair_groupB_data[], int groupPair_groupB_size[1], boolean_T *success)
{
  int candidatePairs_size_idx_0;
  int cnt;
  int i;
  double refOrient_inDeg;
  double refOrient_inRad;
  double refVec[2];
  int i18;
  int j;
  int nx;
  double dv3[2];
  int idx;
  int tmp_size_idx_0;
  int ii;
  double candidatePairs_data[20];
  double tmp_data[22];
  double entry[2];
  boolean_T x_data[10];
  int cornerPointsCnt_data[10];
  emxArray_real_T *b_i;
  emxArray_boolean_T *x;
  emxArray_real_T *c_i;
  emxArray_int32_T *b_ii;
  boolean_T exitg5;
  boolean_T guard5 = false;
  boolean_T exitg4;
  boolean_T guard4 = false;
  boolean_T exitg3;
  boolean_T guard3 = false;
  emxArray_real_T *idxSet;
  boolean_T exitg2;
  boolean_T guard2 = false;
  boolean_T exitg1;
  boolean_T guard1 = false;

  /* % This function accepts various candidate groups and returns a pair of  */
  /*   groups which can form a "correct" grid of corner points. */
  /*  */
  /*   Chau-Wai Wong, Feb. 2015. */
  /*   Chau-Wai Wong, 6/13/2015 */
  candidatePairs_size_idx_0 = 0;

  /*  structure: each row is an pair consisting of two elements */
  /*             [pair1; pair2; ...; pair_N] */
  cnt = groupOrientation_size[0] - 2;

  /*  projected length of a unit vector at (90-15) degree */
  for (i = 0; i <= cnt + 1; i++) {
    refOrient_inDeg = groupOrientation_data[i];
    refOrient_inRad = groupOrientation_data[i] / 180.0 * 3.1415926535897931;
    refVec[0] = cos(refOrient_inRad);
    refVec[1] = sin(refOrient_inRad);
    i18 = cnt - i;
    for (j = 1; j - 1 <= i18; j++) {
      nx = i + j;
      refOrient_inRad = groupOrientation_data[i + j] / 180.0 *
        3.1415926535897931;

      /*  if two group are "roughly" orthogonal */
      dv3[0] = cos(refOrient_inRad);
      dv3[1] = sin(refOrient_inRad);
      refOrient_inRad = 0.0;
      for (idx = 0; idx < 2; idx++) {
        refOrient_inRad += refVec[idx] * dv3[idx];
      }

      if (fabs(refOrient_inRad) < 0.25881904510252074) {
        /*  the "rough" is quantified to be a +/-15 degree in range */
        tmp_size_idx_0 = candidatePairs_size_idx_0;
        ii = candidatePairs_size_idx_0 * 2;
        for (idx = 0; idx < ii; idx++) {
          tmp_data[idx] = candidatePairs_data[idx];
        }

        /* % for two 2-line pairs */
        /*  % % % % if isempty(cornerPointsCnt) */
        /*  % % % %     disp('candidatePairs should not be empty.'); */
        /*  % % % %     disp('need more intersected points...') */
        /*  % % % %     success = false; */
        /*  % % % %     groupPair = []; */
        /*  % % % % elseif prod(cornerPointsCnt>4)==1  % if all pairs have more than 4 intersected corner points */
        /*  % % % %     disp('cornerPointsCnt = ') */
        /*  % % % %     for i = length(cornerPointsCnt) */
        /*  % % % %         disp([int2str(cornerPointsCnt(i)) ' > 4']) */
        /*  % % % %     end */
        /*  % % % %     disp('need less intersected points...') */
        /*  % % % %     success = false; */
        /*  % % % %     groupPair = []; */
        /*  % % % % elseif prod(cornerPointsCnt<4)==1  % if all pairs have less than 4 intersected corner points */
        /*  % % % %     disp('cornerPointsCnt = ') */
        /*  % % % %     for i = length(cornerPointsCnt) */
        /*  % % % %         disp([int2str(cornerPointsCnt(i)) ' < 4']) */
        /*  % % % %     end */
        /*  % % % %     disp('need more intersected points...') */
        /*  % % % %     success = false; */
        /*  % % % %     groupPair = []; */
        /*  % % % % else  % if not all ... */
        /*  % % % %     % pick out those pairs with exactly 4 corner points */
        /*  % % % %     idxSet = find(cornerPointsCnt==4); */
        /*  % % % %     if isempty(idxSet) */
        /*  % % % %         disp('No pair gives 4 corner points: some give less than 4, others give more than 4 points.'); */
        /*  % % % %         groupPair = []; */
        /*  % % % %         success = false; */
        /*  % % % %     elseif length(idxSet)==1 */
        /*  % % % %         p = candidatePairs(idxSet,:); */
        /*  % % % %         groupPair.groupA = group{p(1)==groupOrientation}; */
        /*  % % % %         groupPair.groupB = group{p(2)==groupOrientation}; */
        /*  % % % %         success = true; */
        /*  % % % %     else */
        /*  % % % %         % Chau-Wai Wong, Feb. 2015. */
        /*  % % % %         % Here we have implemented a randomized selection. However, we can */
        /*  % % % %         % implement a criteria-based selection, e.g., a criterion based on */
        /*  % % % %         % the uniformity of the distances among points. We leave this more */
        /*  % % % %         % sophistically implementation to future, if needed. */
        /*  % % % %         idxRand = round(1+rand(1)*(length(idxSet)-1)); */
        /*  % % % %         p = candidatePairs(idxSet(idxRand),:); */
        /*  % % % %         groupPair.groupA = group{p(1)==groupOrientation}; */
        /*  % % % %         groupPair.groupB = group{p(2)==groupOrientation}; */
        /*  % % % %         success = true; */
        /*  % % % %         disp('The randomized selection method is used. If this message appears often,'); */
        /*  % % % %         disp('this randomized selection should be replaced with a criteria-based selection method.'); */
        /*  % % % %     end */
        /*  % % % % end */
        /*  arrange two elements in an entry in ascending order */
        if (refOrient_inDeg < groupOrientation_data[nx]) {
          entry[0] = refOrient_inDeg;
          entry[1] = groupOrientation_data[nx];
        } else {
          entry[0] = groupOrientation_data[nx];
          entry[1] = refOrient_inDeg;
        }

        refOrient_inRad = entry[0] * 100.0 + entry[1];
        for (idx = 0; idx < candidatePairs_size_idx_0; idx++) {
          x_data[idx] = (refOrient_inRad == candidatePairs_data[idx] * 100.0 +
                         candidatePairs_data[idx + candidatePairs_size_idx_0]);
        }

        if (candidatePairs_size_idx_0 == 0) {
          refOrient_inRad = 0.0;
        } else {
          refOrient_inRad = x_data[0];
          for (ii = 2; ii <= candidatePairs_size_idx_0; ii++) {
            refOrient_inRad += (double)x_data[ii - 1];
          }
        }

        if (refOrient_inRad == 0.0) {
          /*  if the entry is new, pad it. */
          tmp_size_idx_0 = candidatePairs_size_idx_0 + 1;
          for (idx = 0; idx < 2; idx++) {
            for (ii = 0; ii < candidatePairs_size_idx_0; ii++) {
              tmp_data[ii + (candidatePairs_size_idx_0 + 1) * idx] =
                candidatePairs_data[ii + candidatePairs_size_idx_0 * idx];
            }
          }

          for (idx = 0; idx < 2; idx++) {
            tmp_data[candidatePairs_size_idx_0 + (candidatePairs_size_idx_0 + 1)
              * idx] = entry[idx];
          }
        }

        candidatePairs_size_idx_0 = tmp_size_idx_0;
        ii = tmp_size_idx_0 * 2;
        for (idx = 0; idx < ii; idx++) {
          candidatePairs_data[idx] = tmp_data[idx];
        }
      }
    }
  }

  /*  check the quality of candidate pairs */
  for (i18 = 0; i18 < candidatePairs_size_idx_0; i18++) {
    cornerPointsCnt_data[i18] = 0;
  }

  i = 0;
  b_emxInit_real_T(&b_i, 1);
  b_emxInit_boolean_T(&x, 1);
  b_emxInit_real_T(&c_i, 1);
  emxInit_int32_T(&b_ii, 1);
  while (i <= candidatePairs_size_idx_0 - 1) {
    /*      cornerPointsCnt(i) = length(group(p(1)==groupOrientation).data) * ... */
    /*                           length(group(p(2)==groupOrientation).data); */
    /*  Although idx1_arr and idx2_arr contain only 1 element each (follows */
    /*  our algorithm, not obvious) Matlab coder compiler does not know. We */
    /*  explicitly refer to the first element to ease the compiler. */
    i18 = x->size[0];
    x->size[0] = groupOrientation_size[0];
    emxEnsureCapacity((emxArray__common *)x, i18, (int)sizeof(boolean_T));
    ii = groupOrientation_size[0];
    for (i18 = 0; i18 < ii; i18++) {
      x->data[i18] = (candidatePairs_data[i] == groupOrientation_data[i18]);
    }

    nx = x->size[0];
    idx = 0;
    i18 = b_ii->size[0];
    b_ii->size[0] = x->size[0];
    emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
    ii = 1;
    exitg5 = false;
    while ((!exitg5) && (ii <= nx)) {
      guard5 = false;
      if (x->data[ii - 1]) {
        idx++;
        b_ii->data[idx - 1] = ii;
        if (idx >= nx) {
          exitg5 = true;
        } else {
          guard5 = true;
        }
      } else {
        guard5 = true;
      }

      if (guard5) {
        ii++;
      }
    }

    if (x->size[0] == 1) {
      if (idx == 0) {
        i18 = b_ii->size[0];
        b_ii->size[0] = 0;
        emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
      }
    } else {
      i18 = b_ii->size[0];
      if (1 > idx) {
        b_ii->size[0] = 0;
      } else {
        b_ii->size[0] = idx;
      }

      emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
    }

    i18 = b_i->size[0];
    b_i->size[0] = b_ii->size[0];
    emxEnsureCapacity((emxArray__common *)b_i, i18, (int)sizeof(double));
    ii = b_ii->size[0];
    for (i18 = 0; i18 < ii; i18++) {
      b_i->data[i18] = b_ii->data[i18];
    }

    i18 = x->size[0];
    x->size[0] = groupOrientation_size[0];
    emxEnsureCapacity((emxArray__common *)x, i18, (int)sizeof(boolean_T));
    ii = groupOrientation_size[0];
    for (i18 = 0; i18 < ii; i18++) {
      x->data[i18] = (candidatePairs_data[i + candidatePairs_size_idx_0] ==
                      groupOrientation_data[i18]);
    }

    nx = x->size[0];
    idx = 0;
    i18 = b_ii->size[0];
    b_ii->size[0] = x->size[0];
    emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
    ii = 1;
    exitg4 = false;
    while ((!exitg4) && (ii <= nx)) {
      guard4 = false;
      if (x->data[ii - 1]) {
        idx++;
        b_ii->data[idx - 1] = ii;
        if (idx >= nx) {
          exitg4 = true;
        } else {
          guard4 = true;
        }
      } else {
        guard4 = true;
      }

      if (guard4) {
        ii++;
      }
    }

    if (x->size[0] == 1) {
      if (idx == 0) {
        i18 = b_ii->size[0];
        b_ii->size[0] = 0;
        emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
      }
    } else {
      i18 = b_ii->size[0];
      if (1 > idx) {
        b_ii->size[0] = 0;
      } else {
        b_ii->size[0] = idx;
      }

      emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
    }

    i18 = c_i->size[0];
    c_i->size[0] = b_ii->size[0];
    emxEnsureCapacity((emxArray__common *)c_i, i18, (int)sizeof(double));
    ii = b_ii->size[0];
    for (i18 = 0; i18 < ii; i18++) {
      c_i->data[i18] = b_ii->data[i18];
    }

    cornerPointsCnt_data[i] = group_data[(int)b_i->data[0] - 1].data.size[0] *
      group_data[(int)c_i->data[0] - 1].data.size[0];
    i++;
  }

  /* % for one 2-line pair and another 4-line pair */
  i18 = x->size[0];
  x->size[0] = candidatePairs_size_idx_0;
  emxEnsureCapacity((emxArray__common *)x, i18, (int)sizeof(boolean_T));
  for (i18 = 0; i18 < candidatePairs_size_idx_0; i18++) {
    x->data[i18] = (cornerPointsCnt_data[i18] == 8);
  }

  nx = x->size[0];
  idx = 0;
  i18 = b_ii->size[0];
  b_ii->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
  ii = 1;
  exitg3 = false;
  while ((!exitg3) && (ii <= nx)) {
    guard3 = false;
    if (x->data[ii - 1]) {
      idx++;
      b_ii->data[idx - 1] = ii;
      if (idx >= nx) {
        exitg3 = true;
      } else {
        guard3 = true;
      }
    } else {
      guard3 = true;
    }

    if (guard3) {
      ii++;
    }
  }

  if (x->size[0] == 1) {
    if (idx == 0) {
      i18 = b_ii->size[0];
      b_ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
    }
  } else {
    i18 = b_ii->size[0];
    if (1 > idx) {
      b_ii->size[0] = 0;
    } else {
      b_ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
  }

  i18 = b_i->size[0];
  b_i->size[0] = b_ii->size[0];
  emxEnsureCapacity((emxArray__common *)b_i, i18, (int)sizeof(double));
  ii = b_ii->size[0];
  for (i18 = 0; i18 < ii; i18++) {
    b_i->data[i18] = b_ii->data[i18];
  }

  b_emxInit_real_T(&idxSet, 1);
  i18 = idxSet->size[0];
  idxSet->size[0] = b_ii->size[0];
  emxEnsureCapacity((emxArray__common *)idxSet, i18, (int)sizeof(double));
  ii = b_ii->size[0];
  for (i18 = 0; i18 < ii; i18++) {
    idxSet->data[i18] = b_ii->data[i18];
  }

  if (b_i->size[0] == 1) {
    /*  Although idx1_arr and idx2_arr contain only 1 element each (follows */
    /*  our algorithm, not obvious) Matlab coder compiler does not know. We */
    /*  explicitly refer to the first element to ease the compiler. */
    i18 = 0 % idxSet->size[0];
    refOrient_inRad = candidatePairs_data[(int)idxSet->data[i18] - 1];
    i18 = x->size[0];
    x->size[0] = groupOrientation_size[0];
    emxEnsureCapacity((emxArray__common *)x, i18, (int)sizeof(boolean_T));
    ii = groupOrientation_size[0];
    for (i18 = 0; i18 < ii; i18++) {
      x->data[i18] = (refOrient_inRad == groupOrientation_data[i18]);
    }

    nx = x->size[0];
    idx = 0;
    i18 = b_ii->size[0];
    b_ii->size[0] = x->size[0];
    emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
    ii = 1;
    exitg2 = false;
    while ((!exitg2) && (ii <= nx)) {
      guard2 = false;
      if (x->data[ii - 1]) {
        idx++;
        b_ii->data[idx - 1] = ii;
        if (idx >= nx) {
          exitg2 = true;
        } else {
          guard2 = true;
        }
      } else {
        guard2 = true;
      }

      if (guard2) {
        ii++;
      }
    }

    if (x->size[0] == 1) {
      if (idx == 0) {
        i18 = b_ii->size[0];
        b_ii->size[0] = 0;
        emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
      }
    } else {
      i18 = b_ii->size[0];
      if (1 > idx) {
        b_ii->size[0] = 0;
      } else {
        b_ii->size[0] = idx;
      }

      emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
    }

    i18 = b_i->size[0];
    b_i->size[0] = b_ii->size[0];
    emxEnsureCapacity((emxArray__common *)b_i, i18, (int)sizeof(double));
    ii = b_ii->size[0];
    for (i18 = 0; i18 < ii; i18++) {
      b_i->data[i18] = b_ii->data[i18];
    }

    i18 = idxSet->size[0];
    idx = 1 % idxSet->size[0];
    refOrient_inRad = candidatePairs_data[((int)idxSet->data[idx] +
      candidatePairs_size_idx_0 * (1 / i18)) - 1];
    i18 = x->size[0];
    x->size[0] = groupOrientation_size[0];
    emxEnsureCapacity((emxArray__common *)x, i18, (int)sizeof(boolean_T));
    ii = groupOrientation_size[0];
    for (i18 = 0; i18 < ii; i18++) {
      x->data[i18] = (refOrient_inRad == groupOrientation_data[i18]);
    }

    nx = x->size[0];
    idx = 0;
    i18 = b_ii->size[0];
    b_ii->size[0] = x->size[0];
    emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
    ii = 1;
    exitg1 = false;
    while ((!exitg1) && (ii <= nx)) {
      guard1 = false;
      if (x->data[ii - 1]) {
        idx++;
        b_ii->data[idx - 1] = ii;
        if (idx >= nx) {
          exitg1 = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        ii++;
      }
    }

    if (x->size[0] == 1) {
      if (idx == 0) {
        i18 = b_ii->size[0];
        b_ii->size[0] = 0;
        emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
      }
    } else {
      i18 = b_ii->size[0];
      if (1 > idx) {
        b_ii->size[0] = 0;
      } else {
        b_ii->size[0] = idx;
      }

      emxEnsureCapacity((emxArray__common *)b_ii, i18, (int)sizeof(int));
    }

    i18 = c_i->size[0];
    c_i->size[0] = b_ii->size[0];
    emxEnsureCapacity((emxArray__common *)c_i, i18, (int)sizeof(double));
    ii = b_ii->size[0];
    for (i18 = 0; i18 < ii; i18++) {
      c_i->data[i18] = b_ii->data[i18];
    }

    groupPair_groupA_size[0] = group_data[(int)b_i->data[0] - 1].data.size[0];
    ii = group_data[(int)b_i->data[0] - 1].data.size[0];
    for (i18 = 0; i18 < ii; i18++) {
      groupPair_groupA_data[i18] = group_data[(int)b_i->data[0] - 1]
        .data.data[i18];
    }

    groupPair_groupB_size[0] = group_data[(int)c_i->data[0] - 1].data.size[0];
    ii = group_data[(int)c_i->data[0] - 1].data.size[0];
    for (i18 = 0; i18 < ii; i18++) {
      groupPair_groupB_data[i18] = group_data[(int)c_i->data[0] - 1]
        .data.data[i18];
    }

    *success = true;
  } else {
    /* groupPair = []; */
    /*  assigned some dummy results (at index #1) for Matlab Coder compiler */
    groupPair_groupA_size[0] = group_data[0].data.size[0];
    ii = group_data[0].data.size[0];
    for (i18 = 0; i18 < ii; i18++) {
      groupPair_groupA_data[i18] = group_data[0].data.data[i18];
    }

    groupPair_groupB_size[0] = group_data[0].data.size[0];
    ii = group_data[0].data.size[0];
    for (i18 = 0; i18 < ii; i18++) {
      groupPair_groupB_data[i18] = group_data[0].data.data[i18];
    }

    *success = false;
  }

  emxFree_int32_T(&b_ii);
  emxFree_real_T(&c_i);
  emxFree_boolean_T(&x);
  emxFree_real_T(&b_i);
  emxFree_real_T(&idxSet);
}

/* End of code generation (pickOutAPossiblePairOfGroups.c) */
