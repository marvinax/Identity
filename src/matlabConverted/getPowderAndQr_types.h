/*
 * getPowderAndQr_types.h
 *
 * Code generation for function 'getPowderAndQr'
 *
 */

#ifndef __GETPOWDERANDQR_TYPES_H__
#define __GETPOWDERANDQR_TYPES_H__

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T
struct emxArray_boolean_T
{
    boolean_T *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_boolean_T*/
#ifndef typedef_emxArray_boolean_T
#define typedef_emxArray_boolean_T
typedef struct emxArray_boolean_T emxArray_boolean_T;
#endif /*typedef_emxArray_boolean_T*/
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T
{
    double *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_real_T*/
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /*typedef_emxArray_real_T*/
#ifndef struct_emxArray_uint8_T
#define struct_emxArray_uint8_T
struct emxArray_uint8_T
{
    unsigned char *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_uint8_T*/
#ifndef typedef_emxArray_uint8_T
#define typedef_emxArray_uint8_T
typedef struct emxArray_uint8_T emxArray_uint8_T;
#endif /*typedef_emxArray_uint8_T*/
#ifndef struct_emxArray_uint8_T_49x49
#define struct_emxArray_uint8_T_49x49
struct emxArray_uint8_T_49x49
{
    unsigned char data[2401];
    int size[2];
};
#endif /*struct_emxArray_uint8_T_49x49*/
#ifndef typedef_emxArray_uint8_T_49x49
#define typedef_emxArray_uint8_T_49x49
typedef struct emxArray_uint8_T_49x49 emxArray_uint8_T_49x49;
#endif /*typedef_emxArray_uint8_T_49x49*/
#ifndef struct_syEgpcIJmPfhgiKirB5znw
#define struct_syEgpcIJmPfhgiKirB5znw
struct syEgpcIJmPfhgiKirB5znw
{
    emxArray_uint8_T_49x49 data;
    double halfCirclePatchSize;
};
#endif /*struct_syEgpcIJmPfhgiKirB5znw*/
#ifndef typedef_struct_T
#define typedef_struct_T
typedef struct syEgpcIJmPfhgiKirB5znw struct_T;
#endif /*typedef_struct_T*/
#ifndef struct_sWGVMMgQDh72OwRweYZntXG
#define struct_sWGVMMgQDh72OwRweYZntXG
struct sWGVMMgQDh72OwRweYZntXG
{
    double rawImgDim[2];
    double warpedImgDim[2];
    double pTheory[16];
    double pCoarse[16];
    double pPrecise[16];
    double rawImgTrulyRawNormalizer;
    boolean_T calcCameraPosFlag;
    emxArray_real_T *rawImgTrulyRaw;
    emxArray_uint8_T *rawImg;
    emxArray_boolean_T *imgMask;
    emxArray_uint8_T *rawImgBlurred;
    emxArray_real_T *warpedRegion2;
    emxArray_real_T *warpedRegion3;
    double figIdx;
    double regionCnt;
    double REGION_IDX[12];
    struct_T refCircle_small;
    struct_T refCircle_large;
};
#endif /*struct_sWGVMMgQDh72OwRweYZntXG*/
#ifndef typedef_AlignWorker_v2
#define typedef_AlignWorker_v2
typedef struct sWGVMMgQDh72OwRweYZntXG AlignWorker_v2;
#endif /*typedef_AlignWorker_v2*/
#ifndef struct_s2bYRKlvEaKS8uqbIV5ilbD
#define struct_s2bYRKlvEaKS8uqbIV5ilbD
struct s2bYRKlvEaKS8uqbIV5ilbD
{
    emxArray_real_T *rawPatch;
    double patch[40000];
    boolean_T patchMask[40000];
    double patchProcessed[40000];
};
#endif /*struct_s2bYRKlvEaKS8uqbIV5ilbD*/
#ifndef typedef_DigitalDevice
#define typedef_DigitalDevice
typedef struct s2bYRKlvEaKS8uqbIV5ilbD DigitalDevice;
#endif /*typedef_DigitalDevice*/
#ifndef struct_sMXWjHOwELOA5cgBpLM7rR
#define struct_sMXWjHOwELOA5cgBpLM7rR
struct sMXWjHOwELOA5cgBpLM7rR
{
    emxArray_uint8_T_49x49 data;
};
#endif /*struct_sMXWjHOwELOA5cgBpLM7rR*/
#ifndef typedef_b_struct_T
#define typedef_b_struct_T
typedef struct sMXWjHOwELOA5cgBpLM7rR b_struct_T;
#endif /*typedef_b_struct_T*/
#ifndef typedef_c_struct_T
#define typedef_c_struct_T
typedef struct
{
    emxArray_uint8_T *data;
} c_struct_T;
#endif /*typedef_c_struct_T*/
#ifndef struct_emxArray__common
#define struct_emxArray__common
struct emxArray__common
{
    void *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray__common*/
#ifndef typedef_emxArray__common
#define typedef_emxArray__common
typedef struct emxArray__common emxArray__common;
#endif /*typedef_emxArray__common*/
#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T
struct emxArray_int32_T
{
    int *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_int32_T*/
#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T
typedef struct emxArray_int32_T emxArray_int32_T;
#endif /*typedef_emxArray_int32_T*/
#ifndef struct_emxArray_int32_T_1024
#define struct_emxArray_int32_T_1024
struct emxArray_int32_T_1024
{
    int data[1024];
    int size[1];
};
#endif /*struct_emxArray_int32_T_1024*/
#ifndef typedef_emxArray_int32_T_1024
#define typedef_emxArray_int32_T_1024
typedef struct emxArray_int32_T_1024 emxArray_int32_T_1024;
#endif /*typedef_emxArray_int32_T_1024*/
#ifndef struct_emxArray_int32_T_1x30
#define struct_emxArray_int32_T_1x30
struct emxArray_int32_T_1x30
{
    int data[30];
    int size[2];
};
#endif /*struct_emxArray_int32_T_1x30*/
#ifndef typedef_emxArray_int32_T_1x30
#define typedef_emxArray_int32_T_1x30
typedef struct emxArray_int32_T_1x30 emxArray_int32_T_1x30;
#endif /*typedef_emxArray_int32_T_1x30*/
#ifndef struct_emxArray_real32_T
#define struct_emxArray_real32_T
struct emxArray_real32_T
{
    float *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_real32_T*/
#ifndef typedef_emxArray_real32_T
#define typedef_emxArray_real32_T
typedef struct emxArray_real32_T emxArray_real32_T;
#endif /*typedef_emxArray_real32_T*/
#ifndef struct_emxArray_real_T_10
#define struct_emxArray_real_T_10
struct emxArray_real_T_10
{
    double data[10];
    int size[1];
};
#endif /*struct_emxArray_real_T_10*/
#ifndef typedef_emxArray_real_T_10
#define typedef_emxArray_real_T_10
typedef struct emxArray_real_T_10 emxArray_real_T_10;
#endif /*typedef_emxArray_real_T_10*/
#ifndef struct_emxArray_real_T_1x156
#define struct_emxArray_real_T_1x156
struct emxArray_real_T_1x156
{
    double data[156];
    int size[2];
};
#endif /*struct_emxArray_real_T_1x156*/
#ifndef typedef_emxArray_real_T_1x156
#define typedef_emxArray_real_T_1x156
typedef struct emxArray_real_T_1x156 emxArray_real_T_1x156;
#endif /*typedef_emxArray_real_T_1x156*/
#ifndef struct_emxArray_real_T_1x2
#define struct_emxArray_real_T_1x2
struct emxArray_real_T_1x2
{
    double data[2];
    int size[2];
};
#endif /*struct_emxArray_real_T_1x2*/
#ifndef typedef_emxArray_real_T_1x2
#define typedef_emxArray_real_T_1x2
typedef struct emxArray_real_T_1x2 emxArray_real_T_1x2;
#endif /*typedef_emxArray_real_T_1x2*/
#ifndef struct_emxArray_real_T_1x30
#define struct_emxArray_real_T_1x30
struct emxArray_real_T_1x30
{
    double data[30];
    int size[2];
};
#endif /*struct_emxArray_real_T_1x30*/
#ifndef typedef_emxArray_real_T_1x30
#define typedef_emxArray_real_T_1x30
typedef struct emxArray_real_T_1x30 emxArray_real_T_1x30;
#endif /*typedef_emxArray_real_T_1x30*/
#ifndef struct_emxArray_real_T_1x9
#define struct_emxArray_real_T_1x9
struct emxArray_real_T_1x9
{
    double data[9];
    int size[2];
};
#endif /*struct_emxArray_real_T_1x9*/
#ifndef typedef_emxArray_real_T_1x9
#define typedef_emxArray_real_T_1x9
typedef struct emxArray_real_T_1x9 emxArray_real_T_1x9;
#endif /*typedef_emxArray_real_T_1x9*/
#ifndef struct_emxArray_real_T_256
#define struct_emxArray_real_T_256
struct emxArray_real_T_256
{
    double data[256];
    int size[1];
};
#endif /*struct_emxArray_real_T_256*/
#ifndef typedef_emxArray_real_T_256
#define typedef_emxArray_real_T_256
typedef struct emxArray_real_T_256 emxArray_real_T_256;
#endif /*typedef_emxArray_real_T_256*/
#ifndef struct_emxArray_real_T_30
#define struct_emxArray_real_T_30
struct emxArray_real_T_30
{
    double data[30];
    int size[1];
};
#endif /*struct_emxArray_real_T_30*/
#ifndef typedef_emxArray_real_T_30
#define typedef_emxArray_real_T_30
typedef struct emxArray_real_T_30 emxArray_real_T_30;
#endif /*typedef_emxArray_real_T_30*/
#ifndef struct_emxArray_real_T_49x49
#define struct_emxArray_real_T_49x49
struct emxArray_real_T_49x49
{
    double data[2401];
    int size[2];
};
#endif /*struct_emxArray_real_T_49x49*/
#ifndef typedef_emxArray_real_T_49x49
#define typedef_emxArray_real_T_49x49
typedef struct emxArray_real_T_49x49 emxArray_real_T_49x49;
#endif /*typedef_emxArray_real_T_49x49*/
#ifndef struct_emxArray_real_T_5
#define struct_emxArray_real_T_5
struct emxArray_real_T_5
{
    double data[5];
    int size[1];
};
#endif /*struct_emxArray_real_T_5*/
#ifndef typedef_emxArray_real_T_5
#define typedef_emxArray_real_T_5
typedef struct emxArray_real_T_5 emxArray_real_T_5;
#endif /*typedef_emxArray_real_T_5*/
#ifndef struct_emxArray_real_T_5x5
#define struct_emxArray_real_T_5x5
struct emxArray_real_T_5x5
{
    double data[25];
    int size[2];
};
#endif /*struct_emxArray_real_T_5x5*/
#ifndef typedef_emxArray_real_T_5x5
#define typedef_emxArray_real_T_5x5
typedef struct emxArray_real_T_5x5 emxArray_real_T_5x5;
#endif /*typedef_emxArray_real_T_5x5*/
#ifndef struct_emxArray_real_T_60x2
#define struct_emxArray_real_T_60x2
struct emxArray_real_T_60x2
{
    double data[120];
    int size[2];
};
#endif /*struct_emxArray_real_T_60x2*/
#ifndef typedef_emxArray_real_T_60x2
#define typedef_emxArray_real_T_60x2
typedef struct emxArray_real_T_60x2 emxArray_real_T_60x2;
#endif /*typedef_emxArray_real_T_60x2*/
#ifndef struct_emxArray_real_T_9
#define struct_emxArray_real_T_9
struct emxArray_real_T_9
{
    double data[9];
    int size[1];
};
#endif /*struct_emxArray_real_T_9*/
#ifndef typedef_emxArray_real_T_9
#define typedef_emxArray_real_T_9
typedef struct emxArray_real_T_9 emxArray_real_T_9;
#endif /*typedef_emxArray_real_T_9*/
#ifndef struct_emxArray_real_T_9x2
#define struct_emxArray_real_T_9x2
struct emxArray_real_T_9x2
{
    double data[18];
    int size[2];
};
#endif /*struct_emxArray_real_T_9x2*/
#ifndef typedef_emxArray_real_T_9x2
#define typedef_emxArray_real_T_9x2
typedef struct emxArray_real_T_9x2 emxArray_real_T_9x2;
#endif /*typedef_emxArray_real_T_9x2*/
#ifndef struct_emxArray_real_T_9x9
#define struct_emxArray_real_T_9x9
struct emxArray_real_T_9x9
{
    double data[81];
    int size[2];
};
#endif /*struct_emxArray_real_T_9x9*/
#ifndef typedef_emxArray_real_T_9x9
#define typedef_emxArray_real_T_9x9
typedef struct emxArray_real_T_9x9 emxArray_real_T_9x9;
#endif /*typedef_emxArray_real_T_9x9*/
#ifndef typedef_d_struct_T
#define typedef_d_struct_T
typedef struct
{
    double alpha_hat;
    double beta_hat;
    double gamma_hat;
} d_struct_T;
#endif /*typedef_d_struct_T*/
#ifndef typedef_e_struct_T
#define typedef_e_struct_T
typedef struct
{
    d_struct_T param;
    double point1[2];
    double point2[2];
    double theta;
    double rho;
} e_struct_T;
#endif /*typedef_e_struct_T*/
#ifndef struct_emxArray_struct_T_30
#define struct_emxArray_struct_T_30
struct emxArray_struct_T_30
{
    e_struct_T data[30];
    int size[1];
};
#endif /*struct_emxArray_struct_T_30*/
#ifndef typedef_emxArray_struct_T_30
#define typedef_emxArray_struct_T_30
typedef struct emxArray_struct_T_30 emxArray_struct_T_30;
#endif /*typedef_emxArray_struct_T_30*/
#ifndef typedef_f_struct_T
#define typedef_f_struct_T
typedef struct
{
    emxArray_struct_T_30 data;
} f_struct_T;
#endif /*typedef_f_struct_T*/
#ifndef struct_emxArray_struct_T_10
#define struct_emxArray_struct_T_10
struct emxArray_struct_T_10
{
    f_struct_T data[10];
    int size[1];
};
#endif /*struct_emxArray_struct_T_10*/
#ifndef typedef_emxArray_struct_T_10
#define typedef_emxArray_struct_T_10
typedef struct emxArray_struct_T_10 emxArray_struct_T_10;
#endif /*typedef_emxArray_struct_T_10*/
#ifndef struct_emxArray_struct_T_1x30
#define struct_emxArray_struct_T_1x30
struct emxArray_struct_T_1x30
{
    e_struct_T data[30];
    int size[2];
};
#endif /*struct_emxArray_struct_T_1x30*/
#ifndef typedef_emxArray_struct_T_1x30
#define typedef_emxArray_struct_T_1x30
typedef struct emxArray_struct_T_1x30 emxArray_struct_T_1x30;
#endif /*typedef_emxArray_struct_T_1x30*/
#ifndef struct_vision_Autothresholder_3
#define struct_vision_Autothresholder_3
struct vision_Autothresholder_3
{
    boolean_T S0_isInitialized;
    boolean_T S1_isReleased;
    int W0_HIST_FIXPT_DW[256];
    int W1_P_FIXPT_DW[256];
    int W2_MU_FIXPT_DW[256];
    int W3_NORMF_FIXPT_DW;
    unsigned char P0_BIN_BOUNDARY_FIXPT_RTP[256];
    int P1_SCALE_FIXPT_RTP;
    unsigned char P2_UMIN_FIXPT_RTP;
    unsigned char P3_UMAX_FIXPT_RTP;
};
#endif /*struct_vision_Autothresholder_3*/
#ifndef typedef_vision_Autothresholder_3
#define typedef_vision_Autothresholder_3
typedef struct vision_Autothresholder_3 vision_Autothresholder_3;
#endif /*typedef_vision_Autothresholder_3*/
#ifndef typedef_visioncodegen_Autothresholder
#define typedef_visioncodegen_Autothresholder
typedef struct
{
    boolean_T matlabCodegenIsDeleted;
    boolean_T isInitialized;
    boolean_T isReleased;
    boolean_T TunablePropsChanged;
    vision_Autothresholder_3 cSFunObject;
    boolean_T c_NoTuningBeforeLockingCodeGenE;
} visioncodegen_Autothresholder;
#endif /*typedef_visioncodegen_Autothresholder*/
#ifndef struct_vision_BlobAnalysis_7
#define struct_vision_BlobAnalysis_7
struct vision_BlobAnalysis_7
{
    boolean_T S0_isInitialized;
    boolean_T S1_isReleased;
    short W0_N_PIXLIST_DW[40000];
    short W1_M_PIXLIST_DW[40000];
    unsigned int W2_NUM_PIX_DW[100];
    unsigned char W3_PAD_DW[40804];
    unsigned int W4_STACK_DW[40000];
    int P0_WALKER_RTP[8];
    unsigned int P1_MINAREA_RTP;
    unsigned int P2_MAXAREA_RTP;
};
#endif /*struct_vision_BlobAnalysis_7*/
#ifndef typedef_vision_BlobAnalysis_7
#define typedef_vision_BlobAnalysis_7
typedef struct vision_BlobAnalysis_7 vision_BlobAnalysis_7;
#endif /*typedef_vision_BlobAnalysis_7*/
#ifndef typedef_visioncodegen_BlobAnalysis
#define typedef_visioncodegen_BlobAnalysis
typedef struct
{
    boolean_T matlabCodegenIsDeleted;
    boolean_T isInitialized;
    boolean_T isReleased;
    boolean_T TunablePropsChanged;
    vision_BlobAnalysis_7 cSFunObject;
    boolean_T c_NoTuningBeforeLockingCodeGenE;
} visioncodegen_BlobAnalysis;
#endif /*typedef_visioncodegen_BlobAnalysis*/
#ifndef struct_vision_HoughTransform_5
#define struct_vision_HoughTransform_5
struct vision_HoughTransform_5
{
    boolean_T S0_isInitialized;
    boolean_T S1_isReleased;
    double W0_FIRSTRHO_DW;
    double P0_SINE_TABLE_RTP[91];
    double P1_RHO_RESOL_RTP;
    emxArray_real_T *O0_Y0;
};
#endif /*struct_vision_HoughTransform_5*/
#ifndef typedef_vision_HoughTransform_5
#define typedef_vision_HoughTransform_5
typedef struct vision_HoughTransform_5 vision_HoughTransform_5;
#endif /*typedef_vision_HoughTransform_5*/
#ifndef typedef_visioncodegen_HoughTransform_6
#define typedef_visioncodegen_HoughTransform_6
typedef struct
{
    boolean_T matlabCodegenIsDeleted;
    boolean_T isInitialized;
    boolean_T isReleased;
    vision_HoughTransform_5 cSFunObject;
} visioncodegen_HoughTransform_6;
#endif /*typedef_visioncodegen_HoughTransform_6*/
#ifndef struct_vision_LocalMaximaFinder_6
#define struct_vision_LocalMaximaFinder_6
struct vision_LocalMaximaFinder_6
{
    boolean_T S0_isInitialized;
    boolean_T S1_isReleased;
    double W0_TEMP_IN_DWORKS[5089860];
    unsigned int W1_NUMPEAKS_DWORK;
    unsigned int P0_NHOODSIZE_RTP[2];
    double P1_THRESHOLD_RTP;
};
#endif /*struct_vision_LocalMaximaFinder_6*/
#ifndef typedef_vision_LocalMaximaFinder_6
#define typedef_vision_LocalMaximaFinder_6
typedef struct vision_LocalMaximaFinder_6 vision_LocalMaximaFinder_6;
#endif /*typedef_vision_LocalMaximaFinder_6*/
#ifndef typedef_visioncodegen_LocalMaximaFinder
#define typedef_visioncodegen_LocalMaximaFinder
typedef struct
{
    boolean_T matlabCodegenIsDeleted;
    boolean_T isInitialized;
    boolean_T isReleased;
    boolean_T TunablePropsChanged;
    vision_LocalMaximaFinder_6 cSFunObject;
} visioncodegen_LocalMaximaFinder;
#endif /*typedef_visioncodegen_LocalMaximaFinder*/

#endif
/* End of code generation (getPowderAndQr_types.h) */
