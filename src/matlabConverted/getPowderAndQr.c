/*
 * getPowderAndQr.c
 *
 * Code generation for function 'getPowderAndQr'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getPowderAndQr.h"
#include "getPowderAndQr_emxutil.h"
#include "DigitalDevice.h"
#include "AlignWorker_v2.h"
#include "libmwremaptbb.h"
#include "math.h"
#include "tmwtypes.h"
#include "viphough_rt.h"

/* Function Definitions */
void getPowderAndQr(const emxArray_real_T *reducedSizeImg, const
                    emxArray_boolean_T *reducedSizeMask, double edgeLength,
                    unsigned char debugMode, emxArray_real_T *imgPowder,
                    emxArray_real_T *imgQr, boolean_T *successFlag)
{
  AlignWorker_v2 objAlign;
  int i0;
  boolean_T b_successFlag;
  static DigitalDevice objPowder;
  int loop_ub;
  static DigitalDevice objQR;
  (void)debugMode;
  emxInitStruct_AlignWorker_v2(&objAlign);

  /* % This is a wrapper function for obtaining the extract powder patch and QR patch */
  /*    Chau-Wai Wong, 10/16/2015 */
  /*  figPos = {... */
  /*      [fig_width   350 fig_width fig_height], ... */
  /*      [0           350 fig_width fig_height], ... */
  /*      [fig_width*2 350 fig_width fig_height], ... */
  /*      [0             0 fig_width fig_height]}; */
  /*  % length of the square */
  /*  % short and long radii */
  /*  % offset for top-left corner point */
  /*  singlePatch or triPatch */
  i0 = imgPowder->size[0] * imgPowder->size[1];
  imgPowder->size[0] = 0;
  imgPowder->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)imgPowder, i0, (int)sizeof(double));
  i0 = imgQr->size[0] * imgQr->size[1];
  imgQr->size[0] = 0;
  imgQr->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)imgQr, i0, (int)sizeof(double));

  /* coder.varsize('imgPowder', [3000 3000], [true true]); */
  /*  constants */
  AlignWorker_v2_AlignWorker_v2(&objAlign);
  b_successFlag = c_AlignWorker_v2_carryOutMatchi(&objAlign, reducedSizeImg,
    reducedSizeMask, edgeLength);
  *successFlag = b_successFlag;
  if (b_successFlag) {
    emxInitStruct_DigitalDevice(&objPowder);

    /*  align powder patch */
    c_AlignWorker_v2_matchingIndivi(&objAlign);

    /*  post-process powder patch */
    i0 = objPowder.rawPatch->size[0] * objPowder.rawPatch->size[1];
    objPowder.rawPatch->size[0] = objAlign.warpedRegion3->size[0];
    objPowder.rawPatch->size[1] = objAlign.warpedRegion3->size[1];
    emxEnsureCapacity((emxArray__common *)objPowder.rawPatch, i0, (int)sizeof
                      (double));
    loop_ub = objAlign.warpedRegion3->size[0] * objAlign.warpedRegion3->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      objPowder.rawPatch->data[i0] = objAlign.warpedRegion3->data[i0];
    }

    emxInitStruct_DigitalDevice(&objQR);
    c_DigitalDevice_processSquarePa(&objPowder);
    DigitalDevice_glareRemoval(&objPowder);
    DigitalDevice_detrend(&objPowder);

    /*  align QR patch */
    d_AlignWorker_v2_matchingIndivi(&objAlign);

    /*  post-process QR patch */
    i0 = objQR.rawPatch->size[0] * objQR.rawPatch->size[1];
    objQR.rawPatch->size[0] = objAlign.warpedRegion2->size[0];
    objQR.rawPatch->size[1] = objAlign.warpedRegion2->size[1];
    emxEnsureCapacity((emxArray__common *)objQR.rawPatch, i0, (int)sizeof(double));
    loop_ub = objAlign.warpedRegion2->size[0] * objAlign.warpedRegion2->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      objQR.rawPatch->data[i0] = objAlign.warpedRegion2->data[i0];
    }

    d_DigitalDevice_processSquarePa(&objQR);
    DigitalDevice_glareRemoval(&objQR);
    DigitalDevice_detrend(&objQR);

    /*  hFig = figure(64); imshow(objAlign.warpedRegions(POWDER_PATCH).data,[]); */
    /*  title('Aligned tri-patch based on the 3rd sub-patch'); */
    /*  set(hFig, 'position', [350*2 0 350 600]); */
    /*  hFig = figure(164); imshow(objAlign.warpedRegions(QR_PATCH).data,[]); */
    /*  title('Aligned tri-patch based on the 2nd sub-patch'); */
    /*  set(hFig, 'position', [350*3 0 350 600]); */
    i0 = imgPowder->size[0] * imgPowder->size[1];
    imgPowder->size[0] = 200;
    imgPowder->size[1] = 200;
    emxEnsureCapacity((emxArray__common *)imgPowder, i0, (int)sizeof(double));
    for (i0 = 0; i0 < 40000; i0++) {
      imgPowder->data[i0] = objPowder.patchProcessed[i0];
    }

    emxFreeStruct_DigitalDevice(&objPowder);
    i0 = imgQr->size[0] * imgQr->size[1];
    imgQr->size[0] = 200;
    imgQr->size[1] = 200;
    emxEnsureCapacity((emxArray__common *)imgQr, i0, (int)sizeof(double));
    for (i0 = 0; i0 < 40000; i0++) {
      imgQr->data[i0] = objQR.patchProcessed[i0];
    }

    emxFreeStruct_DigitalDevice(&objQR);
  }

  emxFreeStruct_AlignWorker_v2(&objAlign);
}

/* End of code generation (getPowderAndQr.c) */
