#include "hdf.h"
#include "dfsd.h"
#include "tutils.h"

/* External Variables */
extern int num_errs;
extern int Verbocity;

/* Internal Variables */
#define CDIM_X  7
#define CDIM_Y  9

#define FILENAME    "litend.dat"
#define TMPFILE     "temp.hdf"

int8 cdata_i8[CDIM_Y][CDIM_X];
uint8 cdata_u8[CDIM_Y][CDIM_X];
int16 cdata_i16[CDIM_Y][CDIM_X];
uint16 cdata_u16[CDIM_Y][CDIM_X];
int32 cdata_i32[CDIM_Y][CDIM_X];
uint32 cdata_u32[CDIM_Y][CDIM_X];
float32 cdata_f32[CDIM_Y][CDIM_X];
float64 cdata_f64[CDIM_Y][CDIM_X];

VOID init_cdata()
{
    int i,j;

    for (i=0; i< CDIM_Y; i++)
       for (j=0; j< CDIM_X; j++) {
            cdata_i8[i][j]=(int8)(i*10+j);
            cdata_u8[i][j]=(uint8)(i*10+j);
            cdata_i16[i][j]=(int16)(i*10+j);
            cdata_u16[i][j]=(uint16)(i*10+j);
            cdata_i32[i][j]=(int32)(i*10+j);
            cdata_u32[i][j]=(uint32)(i*10+j);
            cdata_f32[i][j]=(float32)(i*10+j);
            cdata_f64[i][j]=(float64)(i*10+j);
          } /* end for */
}   /* end init_cdata() */

intn test_little_read()
{
    intn rank;
    int32 dimsizes[2];
    int32 numbertype;
    int8 *data_i8;
    uint8 *data_u8;
    int16 *data_i16;
    uint16 *data_u16;
    int32 *data_i32;
    uint32 *data_u32;
    float32 *data_f32;
    float64 *data_f64;
    int ret;

    ret=DFSDgetdims(FILENAME,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for INT8 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LINT8) {
            fprintf(stderr, "Numbertype for INT8 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_i8=(int8 *)HDgetspace(dimsizes[0]*dimsizes[1]*sizeof(int8));
            ret=DFSDgetdata(FILENAME,rank,dimsizes,data_i8);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_i8,data_i8,CDIM_X*CDIM_Y*sizeof(int8))) {
                fprintf(stderr,"INT8 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_i8);
          } /* end else */
      } /* end else */

    ret=DFSDgetdims(FILENAME,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for UINT8 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LUINT8) {
            fprintf(stderr, "Numbertype for UINT8 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_u8=(uint8 *)HDgetspace(dimsizes[0]*dimsizes[1]*sizeof(uint8));
            ret=DFSDgetdata(FILENAME,rank,dimsizes,data_u8);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_u8,data_u8,CDIM_X*CDIM_Y*sizeof(uint8))) {
                fprintf(stderr,"UINT8 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_u8);
          } /* end else */
      } /* end else */

    ret=DFSDgetdims(FILENAME,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for INT16 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LINT16) {
            fprintf(stderr, "Numbertype for INT16 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_i16=(int16 *)HDgetspace(dimsizes[0]*dimsizes[1]*sizeof(int16));
            ret=DFSDgetdata(FILENAME,rank,dimsizes,data_i16);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_i16,data_i16,CDIM_X*CDIM_Y*sizeof(int16))) {
                fprintf(stderr,"INT16 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_i16);
          } /* end else */
      } /* end else */

    ret=DFSDgetdims(FILENAME,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for UINT16 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LUINT16) {
            fprintf(stderr, "Numbertype for UINT16 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_u16=(uint16 *)HDgetspace(dimsizes[0]*
		    dimsizes[1]*sizeof(uint16));
            ret=DFSDgetdata(FILENAME,rank,dimsizes,data_u16);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_u16,data_u16,CDIM_X*CDIM_Y*sizeof(uint16))) {
                fprintf(stderr,"UINT16 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_u16);
          } /* end else */
      } /* end else */

    ret=DFSDgetdims(FILENAME,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for INT32 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LINT32) {
            fprintf(stderr, "Numbertype for INT32 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_i32=(int32 *)HDgetspace(dimsizes[0]*dimsizes[1]*sizeof(int32));
            ret=DFSDgetdata(FILENAME,rank,dimsizes,data_i32);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_i32,data_i32,CDIM_X*CDIM_Y*sizeof(int32))) {
                fprintf(stderr,"INT32 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_i32);
          } /* end else */
      } /* end else */

    ret=DFSDgetdims(FILENAME,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for UINT32 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LUINT32) {
            fprintf(stderr, "Numbertype for UINT32 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_u32=(uint32 *)HDgetspace(dimsizes[0]*dimsizes[1]*
		    sizeof(uint32));
            ret=DFSDgetdata(FILENAME,rank,dimsizes,data_u32);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_u32,data_u32,CDIM_X*CDIM_Y*sizeof(uint32))) {
                fprintf(stderr,"UINT32 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_u32);
          } /* end else */
      } /* end else */

    ret=DFSDgetdims(FILENAME,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for FLOAT32 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LFLOAT32) {
            fprintf(stderr, "Numbertype for FLOAT32 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_f32=(float32 *)HDgetspace(dimsizes[0]*dimsizes[1]*
		    sizeof(float32));
            ret=DFSDgetdata(FILENAME,rank,dimsizes,data_f32);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_f32,data_f32,CDIM_X*CDIM_Y*sizeof(float32))) {
                fprintf(stderr,"FLOAT32 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_f32);
          } /* end else */
      } /* end else */

    ret=DFSDgetdims(FILENAME,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for FLOAT64 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LFLOAT64) {
            fprintf(stderr, "Numbertype for FLOAT64 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_f64=(float64 *)HDgetspace(dimsizes[0]*dimsizes[1]*
		    sizeof(float64));
            ret=DFSDgetdata(FILENAME,rank,dimsizes,data_f64);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_f64,data_f64,CDIM_X*CDIM_Y*sizeof(float64))) {
                fprintf(stderr,"FLOAT64 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_f64);
          } /* end else */
      } /* end else */
}   /* end test_little_read */

intn test_little_write()
{
    intn rank;
    int32 dimsizes[2];
    int32 numbertype;
    int8 *data_i8;
    uint8 *data_u8;
    int16 *data_i16;
    uint16 *data_u16;
    int32 *data_i32;
    uint32 *data_u32;
    float32 *data_f32;
    float64 *data_f64;
    int ret;

    rank = 2;
    dimsizes[0]=CDIM_Y;
    dimsizes[1]=CDIM_X;

    ret=DFSDsetdims(2,dimsizes);
    RESULT("DFSDsetdims");
    ret=DFSDsetNT(DFNT_LINT8);
    RESULT("DFSDsetNT");
    ret=DFSDadddata(TMPFILE, rank, dimsizes, cdata_i8);
    RESULT("DFSDadddata");

    ret=DFSDsetdims(2,dimsizes);
    RESULT("DFSDsetdims");
    ret=DFSDsetNT(DFNT_LUINT8);
    RESULT("DFSDsetNT");
    ret=DFSDadddata(TMPFILE, rank, dimsizes, cdata_u8);
    RESULT("DFSDadddata");

    ret=DFSDsetdims(2,dimsizes);
    RESULT("DFSDsetdims");
    ret=DFSDsetNT(DFNT_LINT16);
    RESULT("DFSDsetNT");
    ret=DFSDadddata(TMPFILE, rank, dimsizes, cdata_i16);
    RESULT("DFSDadddata");

    ret=DFSDsetdims(2,dimsizes);
    RESULT("DFSDsetdims");
    ret=DFSDsetNT(DFNT_LUINT16);
    RESULT("DFSDsetNT");
    ret=DFSDadddata(TMPFILE, rank, dimsizes, cdata_u16);
    RESULT("DFSDadddata");

    ret=DFSDsetdims(2,dimsizes);
    RESULT("DFSDsetdims");
    ret=DFSDsetNT(DFNT_LINT32);
    RESULT("DFSDsetNT");
    ret=DFSDadddata(TMPFILE, rank, dimsizes, cdata_i32);
    RESULT("DFSDadddata");

    ret=DFSDsetdims(2,dimsizes);
    RESULT("DFSDsetdims");
    ret=DFSDsetNT(DFNT_LUINT32);
    RESULT("DFSDsetNT");
    ret=DFSDadddata(TMPFILE, rank, dimsizes, cdata_u32);
    RESULT("DFSDadddata");

    ret=DFSDsetdims(2,dimsizes);
    RESULT("DFSDsetdims");
    ret=DFSDsetNT(DFNT_LFLOAT32);
    RESULT("DFSDsetNT");
    ret=DFSDadddata(TMPFILE, rank, dimsizes, cdata_f32);
    RESULT("DFSDadddata");

    ret=DFSDsetdims(2,dimsizes);
    RESULT("DFSDsetdims");
    ret=DFSDsetNT(DFNT_LFLOAT64);
    RESULT("DFSDsetNT");
    ret=DFSDadddata(TMPFILE, rank, dimsizes, cdata_f64);
    RESULT("DFSDadddata");

    ret=DFSDrestart();
    RESULT("DFSDrestart");

    ret=DFSDgetdims(TMPFILE,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for INT8 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LINT8) {
            fprintf(stderr, "Numbertype for INT8 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_i8=(int8 *)HDgetspace(dimsizes[0]*dimsizes[1]*sizeof(int8));
            ret=DFSDgetdata(TMPFILE,rank,dimsizes,data_i8);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_i8,data_i8,CDIM_X*CDIM_Y*sizeof(int8))) {
                fprintf(stderr,"INT8 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_i8);
          } /* end else */
      } /* end else */

    ret=DFSDgetdims(TMPFILE,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for UINT8 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LUINT8) {
            fprintf(stderr, "Numbertype for UINT8 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_u8=(uint8 *)HDgetspace(dimsizes[0]*dimsizes[1]*sizeof(uint8));
            ret=DFSDgetdata(TMPFILE,rank,dimsizes,data_u8);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_u8,data_u8,CDIM_X*CDIM_Y*sizeof(uint8))) {
                fprintf(stderr,"UINT8 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_u8);
          } /* end else */
      } /* end else */

    ret=DFSDgetdims(TMPFILE,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for INT16 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LINT16) {
            fprintf(stderr, "Numbertype for INT16 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_i16=(int16 *)HDgetspace(dimsizes[0]*dimsizes[1]*sizeof(int16));
            ret=DFSDgetdata(TMPFILE,rank,dimsizes,data_i16);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_i16,data_i16,CDIM_X*CDIM_Y*sizeof(int16))) {
                fprintf(stderr,"INT16 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_i16);
          } /* end else */
      } /* end else */

    ret=DFSDgetdims(TMPFILE,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for UINT16 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LUINT16) {
            fprintf(stderr, "Numbertype for UINT16 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_u16=(uint16 *)HDgetspace(dimsizes[0]*dimsizes[1]*
		   sizeof(uint16));
            ret=DFSDgetdata(TMPFILE,rank,dimsizes,data_u16);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_u16,data_u16,CDIM_X*CDIM_Y*sizeof(uint16))) {
                fprintf(stderr,"UINT16 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_u16);
          } /* end else */
      } /* end else */

    ret=DFSDgetdims(TMPFILE,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for INT32 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LINT32) {
            fprintf(stderr, "Numbertype for INT32 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_i32=(int32 *)HDgetspace(dimsizes[0]*dimsizes[1]*sizeof(int32));
            ret=DFSDgetdata(TMPFILE,rank,dimsizes,data_i32);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_i32,data_i32,CDIM_X*CDIM_Y*sizeof(int32))) {
                fprintf(stderr,"INT32 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_i32);
          } /* end else */
      } /* end else */

    ret=DFSDgetdims(TMPFILE,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for UINT32 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LUINT32) {
            fprintf(stderr, "Numbertype for UINT32 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_u32=(uint32 *)HDgetspace(dimsizes[0]*dimsizes[1]*
		    sizeof(uint32));
            ret=DFSDgetdata(TMPFILE,rank,dimsizes,data_u32);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_u32,data_u32,CDIM_X*CDIM_Y*sizeof(uint32))) {
                fprintf(stderr,"UINT32 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_u32);
          } /* end else */
      } /* end else */

    ret=DFSDgetdims(TMPFILE,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for FLOAT32 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LFLOAT32) {
            fprintf(stderr, "Numbertype for FLOAT32 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_f32=(float32 *)HDgetspace(dimsizes[0]*dimsizes[1]*
		    sizeof(float32));
            ret=DFSDgetdata(TMPFILE,rank,dimsizes,data_f32);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_f32,data_f32,CDIM_X*CDIM_Y*sizeof(float32))) {
                fprintf(stderr,"FLOAT32 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_f32);
          } /* end else */
      } /* end else */

    ret=DFSDgetdims(TMPFILE,&rank,dimsizes,2);
    RESULT("DFSDgetdims");
    if(dimsizes[0]!=CDIM_Y || dimsizes[1]!=CDIM_X) {
        fprintf(stderr, "Dimensions for FLOAT64 data were incorrect\n");
        num_errs++;
      } /* end if */
    else {
        ret=DFSDgetNT(&numbertype);
        RESULT("DFSDgetNT");
        if(numbertype!=DFNT_LFLOAT64) {
            fprintf(stderr, "Numbertype for FLOAT64 data were incorrect\n");
            num_errs++;
          } /* end if */
        else {
            data_f64=(float64 *)HDgetspace(dimsizes[0]*dimsizes[1]*
		    sizeof(float64));
            ret=DFSDgetdata(TMPFILE,rank,dimsizes,data_f64);
            RESULT("DFSDgetdata");

            if(HDmemcmp(cdata_f64,data_f64,CDIM_X*CDIM_Y*sizeof(float64))) {
                fprintf(stderr,"FLOAT64 data was incorrect\n");
                num_errs++;
              } /* end if */
            HDfreespace((VOIDP)data_f64);
          } /* end else */
      } /* end else */
}   /* end test_little_write */

void test_litend()
{
    init_cdata();

    test_little_read();
    test_little_write();
}   /* end test_litend() */

