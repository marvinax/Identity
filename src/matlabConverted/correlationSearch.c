/*
 * correlationSearch.c
 *
 * Code generation for function 'correlationSearch'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "correlationSearch.h"
#include "patchCorr.h"
#include "getPowderAndQr_emxutil.h"
#include "calcPearsonCorr.h"
#include "patchCorr_oneSearchMaskOnTheOther.h"
#include "myImresize.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void b_correlationSearch(const emxArray_uint8_T *wholeImg, const double
  coordinates[8], const unsigned char refCircle_small_data_data[], const int
  refCircle_small_data_size[2], double c_refCircle_small_halfCirclePat, const
  unsigned char refCircle_large_data_data[], const int
  refCircle_large_data_size[2], double c_refCircle_large_halfCirclePat, double
  coordinates_new[8], double circleSizeNum[4], double dVec_overall[2])
{
  emxArray_real_T *im1;
  emxArray_real_T *im2;
  emxArray_real_T *r25;
  emxArray_real_T *winRange;
  emxArray_uint8_T *testCircle;
  emxArray_uint8_T *imgBg;
  emxArray_uint8_T *imgMask;
  int idxPt;
  double corrVal_diffCircleSize[2];
  int i;
  double delta[4];
  int circleSizeIdx;
  int rrc_data_size[2];
  int ix;
  int i35;
  unsigned char rrc_data_data[2401];
  double mtmp;
  int n;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  double absa;
  double absb;
  int i36;
  double expl_temp[441];
  double b_expl_temp[441];
  double c_expl_temp[441];
  double bestMatchedPoint_intPel_x[2];
  boolean_T exitg2;
  emxArray_uint8_T b_rrc_data_data;
  double corrVal[169];
  short iv11[2];
  static const signed char iv12[169] = { -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4,
    5, 6, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, -6, -5, -4, -3, -2, -1, 0,
    1, 2, 3, 4, 5, 6, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, -6, -5, -4,
    -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6,
    -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, -6, -5, -4, -3, -2, -1, 0, 1, 2,
    3, 4, 5, 6, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, -6, -5, -4, -3, -2,
    -1, 0, 1, 2, 3, 4, 5, 6, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, -6, -5,
    -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4,
    5, 6 };

  short iv13[2];
  static const signed char iv14[169] = { -6, -6, -6, -6, -6, -6, -6, -6, -6, -6,
    -6, -6, -6, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -4, -4, -4,
    -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -3, -3, -3, -3, -3, -3, -3, -3, -3,
    -3, -3, -3, -3, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6 };

  int b_im1[1];
  int b_im2[1];
  emxArray_real_T c_im1;
  emxArray_real_T c_im2;
  boolean_T exitg1;
  signed char iv15[2];

  /* % This subroutine carries out cross-correlation search at  */
  /*   integer pixel level and then sub-pixel level. */
  /*   Chau-Wai Wong, Mar. 2015 */
  emxInit_real_T(&im1, 2);
  emxInit_real_T(&im2, 2);
  emxInit_real_T(&r25, 2);
  emxInit_real_T(&winRange, 2);
  emxInit_uint8_T(&testCircle, 2);
  emxInit_uint8_T(&imgBg, 2);
  emxInit_uint8_T(&imgMask, 2);
  for (idxPt = 0; idxPt < 4; idxPt++) {
    /*  stage 1 - integer pixel search */
    for (i = 0; i < 2; i++) {
      corrVal_diffCircleSize[i] = 0.0;
    }

    for (circleSizeIdx = 0; circleSizeIdx < 2; circleSizeIdx++) {
      if (1 + circleSizeIdx == 1) {
        rrc_data_size[0] = refCircle_small_data_size[0];
        rrc_data_size[1] = refCircle_small_data_size[1];
        ix = refCircle_small_data_size[0] * refCircle_small_data_size[1];
        for (i35 = 0; i35 < ix; i35++) {
          rrc_data_data[i35] = refCircle_small_data_data[i35];
        }

        mtmp = c_refCircle_small_halfCirclePat;
      } else {
        rrc_data_size[0] = refCircle_large_data_size[0];
        rrc_data_size[1] = refCircle_large_data_size[1];
        ix = refCircle_large_data_size[0] * refCircle_large_data_size[1];
        for (i35 = 0; i35 < ix; i35++) {
          rrc_data_data[i35] = refCircle_large_data_data[i35];
        }

        mtmp = c_refCircle_large_halfCirclePat;
      }

      if (rtIsNaN(-(mtmp + 10.0)) || rtIsNaN(mtmp + 10.0)) {
        n = 0;
        anew = rtNaN;
        apnd = mtmp + 10.0;
      } else if (mtmp + 10.0 < -(mtmp + 10.0)) {
        n = -1;
        anew = -(mtmp + 10.0);
        apnd = mtmp + 10.0;
      } else if (rtIsInf(-(mtmp + 10.0)) || rtIsInf(mtmp + 10.0)) {
        n = 0;
        anew = rtNaN;
        apnd = mtmp + 10.0;
      } else {
        anew = -(mtmp + 10.0);
        ndbl = floor(((mtmp + 10.0) - (-(mtmp + 10.0))) + 0.5);
        apnd = -(mtmp + 10.0) + ndbl;
        cdiff = apnd - (mtmp + 10.0);
        absa = fabs(-(mtmp + 10.0));
        absb = fabs(mtmp + 10.0);
        if ((absa >= absb) || rtIsNaN(absb)) {
          absb = absa;
        }

        if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
          ndbl++;
          apnd = mtmp + 10.0;
        } else if (cdiff > 0.0) {
          apnd = -(mtmp + 10.0) + (ndbl - 1.0);
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          n = (int)ndbl - 1;
        } else {
          n = -1;
        }
      }

      i35 = winRange->size[0] * winRange->size[1];
      winRange->size[0] = 1;
      winRange->size[1] = n + 1;
      emxEnsureCapacity((emxArray__common *)winRange, i35, (int)sizeof(double));
      if (n + 1 > 0) {
        winRange->data[0] = anew;
        if (n + 1 > 1) {
          winRange->data[n] = apnd;
          i = n / 2;
          for (ix = 1; ix < i; ix++) {
            winRange->data[ix] = anew + (double)ix;
            winRange->data[n - ix] = apnd - (double)ix;
          }

          if (i << 1 == n) {
            winRange->data[i] = (anew + apnd) / 2.0;
          } else {
            winRange->data[i] = anew + (double)i;
            winRange->data[i + 1] = apnd - (double)i;
          }
        }
      }

      i35 = testCircle->size[0] * testCircle->size[1];
      testCircle->size[0] = winRange->size[1];
      testCircle->size[1] = winRange->size[1];
      emxEnsureCapacity((emxArray__common *)testCircle, i35, (int)sizeof
                        (unsigned char));
      ix = winRange->size[1];
      for (i35 = 0; i35 < ix; i35++) {
        n = winRange->size[1];
        for (i36 = 0; i36 < n; i36++) {
          testCircle->data[i36 + testCircle->size[0] * i35] = wholeImg->data
            [((int)(coordinates[1 + (idxPt << 1)] + winRange->data
                    [winRange->size[0] * i36]) + wholeImg->size[0] * ((int)
               (coordinates[idxPt << 1] + winRange->data[winRange->size[0] * i35])
               - 1)) - 1];
        }
      }

      /*  integer search due to imprecise boundary positions obtained */
      /*  figure(689); imshow(imgBg); drawnow */
      patchCorr(testCircle, rrc_data_data, rrc_data_size,
                &corrVal_diffCircleSize[circleSizeIdx], &mtmp, &anew,
                c_expl_temp, b_expl_temp, expl_temp);
      bestMatchedPoint_intPel_x[0] = mtmp;
      bestMatchedPoint_intPel_x[1] = anew;
      for (i35 = 0; i35 < 2; i35++) {
        delta[i35 + (circleSizeIdx << 1)] = bestMatchedPoint_intPel_x[i35];
      }
    }

    /* circleSizeIdx = []; */
    i = 1;
    mtmp = corrVal_diffCircleSize[0];
    circleSizeIdx = 0;
    if (rtIsNaN(corrVal_diffCircleSize[0])) {
      ix = 2;
      exitg2 = false;
      while ((!exitg2) && (ix < 3)) {
        i = 2;
        if (!rtIsNaN(corrVal_diffCircleSize[1])) {
          mtmp = corrVal_diffCircleSize[1];
          circleSizeIdx = 1;
          exitg2 = true;
        } else {
          ix = 3;
        }
      }
    }

    if ((i < 2) && (corrVal_diffCircleSize[1] > mtmp)) {
      circleSizeIdx = 1;
    }

    /*  stage 2 - sub-pixel search */
    if (circleSizeIdx + 1 == 1) {
      rrc_data_size[0] = refCircle_small_data_size[0];
      rrc_data_size[1] = refCircle_small_data_size[1];
      ix = refCircle_small_data_size[0] * refCircle_small_data_size[1];
      for (i35 = 0; i35 < ix; i35++) {
        rrc_data_data[i35] = refCircle_small_data_data[i35];
      }

      mtmp = c_refCircle_small_halfCirclePat;
    } else {
      rrc_data_size[0] = refCircle_large_data_size[0];
      rrc_data_size[1] = refCircle_large_data_size[1];
      ix = refCircle_large_data_size[0] * refCircle_large_data_size[1];
      for (i35 = 0; i35 < ix; i35++) {
        rrc_data_data[i35] = refCircle_large_data_data[i35];
      }

      mtmp = c_refCircle_large_halfCirclePat;
    }

    if (rtIsNaN(-(mtmp + 2.0)) || rtIsNaN(mtmp + 2.0)) {
      n = 0;
      anew = rtNaN;
      apnd = mtmp + 2.0;
    } else if (mtmp + 2.0 < -(mtmp + 2.0)) {
      n = -1;
      anew = -(mtmp + 2.0);
      apnd = mtmp + 2.0;
    } else if (rtIsInf(-(mtmp + 2.0)) || rtIsInf(mtmp + 2.0)) {
      n = 0;
      anew = rtNaN;
      apnd = mtmp + 2.0;
    } else {
      anew = -(mtmp + 2.0);
      ndbl = floor(((mtmp + 2.0) - (-(mtmp + 2.0))) + 0.5);
      apnd = -(mtmp + 2.0) + ndbl;
      cdiff = apnd - (mtmp + 2.0);
      absa = fabs(-(mtmp + 2.0));
      absb = fabs(mtmp + 2.0);
      if ((absa >= absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = mtmp + 2.0;
      } else if (cdiff > 0.0) {
        apnd = -(mtmp + 2.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl - 1;
      } else {
        n = -1;
      }
    }

    i35 = winRange->size[0] * winRange->size[1];
    winRange->size[0] = 1;
    winRange->size[1] = n + 1;
    emxEnsureCapacity((emxArray__common *)winRange, i35, (int)sizeof(double));
    if (n + 1 > 0) {
      winRange->data[0] = anew;
      if (n + 1 > 1) {
        winRange->data[n] = apnd;
        i = n / 2;
        for (ix = 1; ix < i; ix++) {
          winRange->data[ix] = anew + (double)ix;
          winRange->data[n - ix] = apnd - (double)ix;
        }

        if (i << 1 == n) {
          winRange->data[i] = (anew + apnd) / 2.0;
        } else {
          winRange->data[i] = anew + (double)i;
          winRange->data[i + 1] = apnd - (double)i;
        }
      }
    }

    mtmp = coordinates[1 + (idxPt << 1)] + delta[1 + (circleSizeIdx << 1)];
    anew = coordinates[idxPt << 1] + delta[circleSizeIdx << 1];
    i35 = testCircle->size[0] * testCircle->size[1];
    testCircle->size[0] = winRange->size[1];
    testCircle->size[1] = winRange->size[1];
    emxEnsureCapacity((emxArray__common *)testCircle, i35, (int)sizeof(unsigned
      char));
    ix = winRange->size[1];
    for (i35 = 0; i35 < ix; i35++) {
      n = winRange->size[1];
      for (i36 = 0; i36 < n; i36++) {
        testCircle->data[i36 + testCircle->size[0] * i35] = wholeImg->data[((int)
          (mtmp + winRange->data[winRange->size[0] * i36]) + wholeImg->size[0] *
          ((int)(anew + winRange->data[winRange->size[0] * i35]) - 1)) - 1];
      }
    }

    myImresize(testCircle, imgBg);
    b_rrc_data_data.data = (unsigned char *)&rrc_data_data;
    b_rrc_data_data.size = (int *)&rrc_data_size;
    b_rrc_data_data.allocatedSize = 2401;
    b_rrc_data_data.numDimensions = 2;
    b_rrc_data_data.canFreeData = false;
    myImresize(&b_rrc_data_data, testCircle);
    i35 = imgMask->size[0] * imgMask->size[1];
    imgMask->size[0] = testCircle->size[0];
    imgMask->size[1] = testCircle->size[1];
    emxEnsureCapacity((emxArray__common *)imgMask, i35, (int)sizeof(unsigned
      char));
    ix = testCircle->size[0] * testCircle->size[1];
    for (i35 = 0; i35 < ix; i35++) {
      imgMask->data[i35] = testCircle->data[i35];
    }

    /*  This function calculates the correlation between two images that are not */
    /*  aligned but in the same scale. The precision of alignment is full pixel */
    /*  for now. */
    /*  Oct. 2014, Chau-Wai Wong */
    /* convertToIdx = @(range) range(1):range(2); */
    for (i = 0; i < 169; i++) {
      iv11[0] = 1;
      iv11[1] = (short)imgMask->size[0];
      for (i35 = 0; i35 < 2; i35++) {
        corrVal_diffCircleSize[i35] = (short)((iv11[i35] + iv12[i]) + 6);
      }

      convertToIdx(corrVal_diffCircleSize, winRange);
      iv13[0] = 1;
      iv13[1] = (short)imgMask->size[1];
      for (i35 = 0; i35 < 2; i35++) {
        corrVal_diffCircleSize[i35] = (short)((iv13[i35] + iv14[i]) + 6);
      }

      convertToIdx(corrVal_diffCircleSize, r25);
      i35 = im1->size[0] * im1->size[1];
      im1->size[0] = winRange->size[1];
      im1->size[1] = r25->size[1];
      emxEnsureCapacity((emxArray__common *)im1, i35, (int)sizeof(double));
      ix = r25->size[1];
      for (i35 = 0; i35 < ix; i35++) {
        n = winRange->size[1];
        for (i36 = 0; i36 < n; i36++) {
          im1->data[i36 + im1->size[0] * i35] = imgBg->data[((int)winRange->
            data[winRange->size[0] * i36] + imgBg->size[0] * ((int)r25->data
            [r25->size[0] * i35] - 1)) - 1];
        }
      }

      i35 = im2->size[0] * im2->size[1];
      im2->size[0] = imgMask->size[0];
      im2->size[1] = imgMask->size[1];
      emxEnsureCapacity((emxArray__common *)im2, i35, (int)sizeof(double));
      ix = imgMask->size[0] * imgMask->size[1];
      for (i35 = 0; i35 < ix; i35++) {
        im2->data[i35] = imgMask->data[i35];
      }

      /*  corrVal(sIdx) = corr(im1(:), im2(:), 'type', 'Pearson'); */
      b_im1[0] = im1->size[0] * im1->size[1];
      b_im2[0] = im2->size[0] * im2->size[1];
      c_im1 = *im1;
      c_im1.size = (int *)&b_im1;
      c_im1.numDimensions = 1;
      c_im2 = *im2;
      c_im2.size = (int *)&b_im2;
      c_im2.numDimensions = 1;
      corrVal[i] = calcPearsonCorr(&c_im1, &c_im2);

      /*  30% faster */
    }

    /* surf(vec_hori, vec_vert, reshape(corrVal, size(vec_hori))); */
    /* plot(sort(corrVal, 'descend'), 'o') */
    i = 1;
    mtmp = corrVal[0];
    n = 0;
    if (rtIsNaN(corrVal[0])) {
      ix = 1;
      exitg1 = false;
      while ((!exitg1) && (ix + 1 < 170)) {
        i = ix + 1;
        if (!rtIsNaN(corrVal[ix])) {
          mtmp = corrVal[ix];
          n = ix;
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (i < 169) {
      while (i + 1 < 170) {
        if (corrVal[i] > mtmp) {
          mtmp = corrVal[i];
          n = i;
        }

        i++;
      }
    }

    /* figure(obj.figIdx+1); surf(corrMap.x/upscaling, corrMap.y/upscaling, corrMap.val); view(0,0) */
    iv15[0] = iv14[n];
    iv15[1] = iv12[n];
    for (i35 = 0; i35 < 2; i35++) {
      mtmp = delta[i35 + (circleSizeIdx << 1)] + (double)iv15[i35] / 3.0;
      coordinates_new[i35 + (idxPt << 1)] = coordinates[i35 + (idxPt << 1)] +
        mtmp;
      dVec_overall[i35] = mtmp;
    }

    circleSizeNum[idxPt] = (double)circleSizeIdx + 1.0;
  }

  emxFree_real_T(&r25);
  emxFree_real_T(&im2);
  emxFree_real_T(&im1);
  emxFree_uint8_T(&imgMask);
  emxFree_uint8_T(&imgBg);
  emxFree_uint8_T(&testCircle);
  emxFree_real_T(&winRange);
}

void correlationSearch(const emxArray_uint8_T *wholeImg, const double
  coordinates[16], const unsigned char refCircle_small_data_data[], const int
  refCircle_small_data_size[2], double c_refCircle_small_halfCirclePat, const
  unsigned char refCircle_large_data_data[], const int
  refCircle_large_data_size[2], double c_refCircle_large_halfCirclePat, double
  coordinates_new[16], double circleSizeNum[8], double dVec_overall[2])
{
  emxArray_uint8_T *testCircle;
  emxArray_real_T *y;
  int idxPt;
  double corrVal_diffCircleSize[2];
  int i;
  double delta[4];
  int circleSizeIdx;
  int rc_data_size[2];
  int i27;
  unsigned char rc_data_data[2401];
  double mtmp;
  int itmp;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  double absa;
  double absb;
  int ix;
  double expl_temp[441];
  double b_expl_temp[441];
  double c_expl_temp[441];
  double bestMatchedPoint_intPel_x[2];
  boolean_T exitg1;

  /* % This subroutine carries out cross-correlation search at  */
  /*   integer pixel level and then sub-pixel level. */
  /*   Chau-Wai Wong, Mar. 2015 */
  emxInit_uint8_T(&testCircle, 2);
  emxInit_real_T(&y, 2);
  for (idxPt = 0; idxPt < 8; idxPt++) {
    /*  stage 1 - integer pixel search */
    for (i = 0; i < 2; i++) {
      corrVal_diffCircleSize[i] = 0.0;
    }

    for (circleSizeIdx = 0; circleSizeIdx < 2; circleSizeIdx++) {
      if (1 + circleSizeIdx == 1) {
        rc_data_size[0] = refCircle_small_data_size[0];
        rc_data_size[1] = refCircle_small_data_size[1];
        i = refCircle_small_data_size[0] * refCircle_small_data_size[1];
        for (i27 = 0; i27 < i; i27++) {
          rc_data_data[i27] = refCircle_small_data_data[i27];
        }

        mtmp = c_refCircle_small_halfCirclePat;
      } else {
        rc_data_size[0] = refCircle_large_data_size[0];
        rc_data_size[1] = refCircle_large_data_size[1];
        i = refCircle_large_data_size[0] * refCircle_large_data_size[1];
        for (i27 = 0; i27 < i; i27++) {
          rc_data_data[i27] = refCircle_large_data_data[i27];
        }

        mtmp = c_refCircle_large_halfCirclePat;
      }

      if (rtIsNaN(-(mtmp + 10.0)) || rtIsNaN(mtmp + 10.0)) {
        itmp = 0;
        anew = rtNaN;
        apnd = mtmp + 10.0;
      } else if (mtmp + 10.0 < -(mtmp + 10.0)) {
        itmp = -1;
        anew = -(mtmp + 10.0);
        apnd = mtmp + 10.0;
      } else if (rtIsInf(-(mtmp + 10.0)) || rtIsInf(mtmp + 10.0)) {
        itmp = 0;
        anew = rtNaN;
        apnd = mtmp + 10.0;
      } else {
        anew = -(mtmp + 10.0);
        ndbl = floor(((mtmp + 10.0) - (-(mtmp + 10.0))) + 0.5);
        apnd = -(mtmp + 10.0) + ndbl;
        cdiff = apnd - (mtmp + 10.0);
        absa = fabs(-(mtmp + 10.0));
        absb = fabs(mtmp + 10.0);
        if ((absa >= absb) || rtIsNaN(absb)) {
          absb = absa;
        }

        if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
          ndbl++;
          apnd = mtmp + 10.0;
        } else if (cdiff > 0.0) {
          apnd = -(mtmp + 10.0) + (ndbl - 1.0);
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          itmp = (int)ndbl - 1;
        } else {
          itmp = -1;
        }
      }

      i27 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = itmp + 1;
      emxEnsureCapacity((emxArray__common *)y, i27, (int)sizeof(double));
      if (itmp + 1 > 0) {
        y->data[0] = anew;
        if (itmp + 1 > 1) {
          y->data[itmp] = apnd;
          i = itmp / 2;
          for (ix = 1; ix < i; ix++) {
            y->data[ix] = anew + (double)ix;
            y->data[itmp - ix] = apnd - (double)ix;
          }

          if (i << 1 == itmp) {
            y->data[i] = (anew + apnd) / 2.0;
          } else {
            y->data[i] = anew + (double)i;
            y->data[i + 1] = apnd - (double)i;
          }
        }
      }

      i27 = testCircle->size[0] * testCircle->size[1];
      testCircle->size[0] = y->size[1];
      testCircle->size[1] = y->size[1];
      emxEnsureCapacity((emxArray__common *)testCircle, i27, (int)sizeof
                        (unsigned char));
      i = y->size[1];
      for (i27 = 0; i27 < i; i27++) {
        ix = y->size[1];
        for (itmp = 0; itmp < ix; itmp++) {
          testCircle->data[itmp + testCircle->size[0] * i27] = wholeImg->data
            [((int)(coordinates[1 + (idxPt << 1)] + y->data[y->size[0] * itmp])
              + wholeImg->size[0] * ((int)(coordinates[idxPt << 1] + y->data
                [y->size[0] * i27]) - 1)) - 1];
        }
      }

      /*  integer search due to imprecise boundary positions obtained */
      /*  figure(689); imshow(imgBg); drawnow */
      patchCorr(testCircle, rc_data_data, rc_data_size,
                &corrVal_diffCircleSize[circleSizeIdx], &mtmp, &anew,
                c_expl_temp, b_expl_temp, expl_temp);
      bestMatchedPoint_intPel_x[0] = mtmp;
      bestMatchedPoint_intPel_x[1] = anew;
      for (i27 = 0; i27 < 2; i27++) {
        delta[i27 + (circleSizeIdx << 1)] = bestMatchedPoint_intPel_x[i27];
      }
    }

    /* circleSizeIdx = []; */
    i = 1;
    mtmp = corrVal_diffCircleSize[0];
    itmp = 0;
    if (rtIsNaN(corrVal_diffCircleSize[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix < 3)) {
        i = 2;
        if (!rtIsNaN(corrVal_diffCircleSize[1])) {
          mtmp = corrVal_diffCircleSize[1];
          itmp = 1;
          exitg1 = true;
        } else {
          ix = 3;
        }
      }
    }

    if ((i < 2) && (corrVal_diffCircleSize[1] > mtmp)) {
      itmp = 1;
    }

    /*  stage 2 - sub-pixel search */
    for (i27 = 0; i27 < 2; i27++) {
      dVec_overall[i27] = delta[i27 + (itmp << 1)];
      coordinates_new[i27 + (idxPt << 1)] = coordinates[i27 + (idxPt << 1)] +
        delta[i27 + (itmp << 1)];
    }

    circleSizeNum[idxPt] = (double)itmp + 1.0;
  }

  emxFree_real_T(&y);
  emxFree_uint8_T(&testCircle);
}

/* End of code generation (correlationSearch.c) */
