/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF.  The full HDF copyright notice, including       *
 * terms governing use, modification, and redistribution, is contained in    *
 * the files COPYING and Copyright.html.  COPYING can be found at the root   *
 * of the source code distribution tree; Copyright.html can be found at      *
 * http://hdfgroup.org/products/hdf4/doc/Copyright.html.  If you do not have *
 * access to either file, you may request a copy from help@hdfgroup.org.     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/****************************************************************************
 * tattdatainfo.c - tests the functions SDgetattdatainfo & SDgetanndatainfo.
 * Structure of the file:
 *    test_attdatainfo - test driver
 *	  test_attrs - tests getting SDS attribute's data info
 *	  test_annots - tests getting SDS annotation's data info
****************************************************************************/


#ifdef HDF

#define DATAINFO_TESTER

#include "mfhdf.h"
#include "hdftest.h"

#define ATTR_FILE     "attdatainfo.hdf"	/* data file */
#define X_LENGTH      10
#define Y_LENGTH      10
#define RANK          2
#define ISFIRST    (int)1
#define NOTFIRST   (int)0

/****************************************************************************
   Name: test_attrs() - tests getting attribute's data info

   Description:
	This routine creates and writes data to non-special SDSs and verifies
	data and data information with SDgetattdatainfo.  The tests include
	the following SDSs:
	- a 2-dim 5x8 element SDS, float32, with no data
	- a 1-dim 10-element SDS, int32, with 10 values
	- a 2-dim 5x8 element SDS, float32, with 5x8 values
	- a 1-dim 20-element SDS, char, with 20 values
	SDgetattdatainfo will retrieve the number of blocks in the data sets
	and the offsets and lengths of the blocks.  Then the data will be read
	back from the file at the previously retrieved offsets/lengths, without
	the use of the HDF4 library, and will be verified against the original
	data buffers.

   BMR - Jul 2010
 ****************************************************************************/
#define SDS1_NAME	"First SDS"
#define SDS2_NAME	"Second SDS"
#define RANK1		1
#define RANK2		2
#define LENGTH1_X	10
#define LENGTH2_X	5
#define LENGTH2_Y	8
#define LENGTH3_X	21
#define FILE_ATTR_NAME "File_contents"
#define SDS_ATTR_NAME1  "Valid_range 1"
#define SDS_ATTR_NAME2  "Valid_range 2"
#define DIM_ATTR_NAME  "Dim_metric"

static intn test_attrs()
{
    int32 sd_id, sds_id, dim_id, dim_idx, att_idx;
    int32 dimsizes[2], starts[2], edges[2], rank=0;
    int32 data1[LENGTH1_X];
    float data2[LENGTH2_X][LENGTH2_Y];
    char  data3[LENGTH3_X], outdata3[LENGTH3_X];
    char  sds_name[20];
    uintn info_count = 0;
    int32 n_values, nattrs;
    int32 offset=0, length=0;
   char8   file_values[] = "Storm_track_data";
   float32 sds_values[2] = {2., 10.};
   float32 sds_values_out[2];
   char8   dim_values[]  = "Seconds";
    intn  status;
    int   ii, jj;
    intn  num_errs = 0;		/* number of errors so far */

    /* Create the file and initialize the SD interface */
    sd_id = SDstart(ATTR_FILE, DFACC_CREATE);
    CHECK(sd_id, FAIL, "test_attrs: SDstart");

    /* Set an attribute that describes the file contents. */
    n_values = 16;
    status = SDsetattr (sd_id, FILE_ATTR_NAME, DFNT_CHAR8, n_values,
                       (VOIDP)file_values);
    CHECK(status, FAIL, "SDsetattr")

    /***************************************************************
     Create and write non-special SDSs
     ***************************************************************/

    /* Create a 2x2 data set called "EmptyDataset" */
    dimsizes[0] = LENGTH2_X;
    dimsizes[1] = LENGTH2_Y;

    /*
     * Create a 1-dim 10-element SDS, type int32, then write 10 values
     * to it
     */
    dimsizes[0] = LENGTH1_X;
    sds_id = SDcreate (sd_id, SDS1_NAME, DFNT_INT32, RANK1, dimsizes);
    CHECK(sds_id, FAIL, "SDcreate");

    for (ii=0; ii < LENGTH1_X; ii++)
	data1[ii] = 1000 * ii;

    starts[0] = 0;
    edges[0] = LENGTH1_X;
    status = SDwritedata(sds_id, starts, NULL, edges, (VOIDP)data1);
    CHECK(status, FAIL, "SDwritedata");

    status = SDendaccess(sds_id);
    CHECK(status, FAIL, "SDendaccess");

    /* Assign two attributes to the first SDS. */
    n_values  = 2;
    status = SDsetattr (sds_id, SDS_ATTR_NAME1, DFNT_FLOAT32, n_values,
                       (VOIDP)sds_values);
    CHECK(status, FAIL, "SDsetattr")
    n_values = 7;
    status = SDsetattr (sds_id, SDS_ATTR_NAME2, DFNT_CHAR8, n_values,
                       (VOIDP)dim_values);
    CHECK(status, FAIL, "SDsetattr")

    /* 
     * Create a 2-dim 5x8 element SDS, type float32, then write 5x8 values
     * to it
     */
    dimsizes[0] = LENGTH2_X;
    dimsizes[1] = LENGTH2_Y;
    sds_id = SDcreate (sd_id, SDS2_NAME, DFNT_FLOAT32, RANK2, dimsizes);
    CHECK(sds_id, FAIL, "SDcreate");

    for (ii=0; ii < LENGTH2_X; ii++)
	for (jj=0; jj < LENGTH2_Y; jj++)
	    data2[ii][jj] = 500.50 * (ii+jj);

    starts[0] = 0;
    starts[1] = 0;
    edges[0] = LENGTH2_X;
    edges[1] = LENGTH2_Y;
    status = SDwritedata(sds_id, starts, NULL, edges, (VOIDP)data2);
    CHECK(status, FAIL, "SDwritedata");

    /* Get the the second dimension identifier of the SDS. */
    dim_idx = 1;
    dim_id = SDgetdimid (sds_id, dim_idx);
    CHECK(dim_id, FAIL, "SDgetdimid")

    /* Set an attribute of the dimension that specifies the dimension metric. */
    n_values = 7;
    status = SDsetattr (dim_id, DIM_ATTR_NAME, DFNT_CHAR8, n_values,
                       (VOIDP)dim_values);
    CHECK(status, FAIL, "SDsetattr")

    status = SDendaccess(sds_id);
    CHECK(status, FAIL, "SDendaccess");

    status = SDend(sd_id);
    CHECK(status, FAIL, "SDend");

    /***********************************************************************
     Read data info for later accessing data without the use of HDF4 library
     ***********************************************************************/

    /* Re-open the file */
    sd_id = SDstart(ATTR_FILE, DFACC_RDWR);
    CHECK(sd_id, FAIL, "test_attrs: SDstart");

    /* Open the second data set, verify that number of data block is 1, then
	retrieve and record the offset/length */
    sds_id = SDselect(sd_id, 0);
    CHECK(sds_id, FAIL, "test_attrs: SDselect SDS index 1");

    /* Get SDS' rank */
    status = SDgetinfo(sds_id, sds_name, NULL, NULL, NULL, &nattrs);
    CHECK(status, FAIL, "test_attrs: SDgetinfo SDS index 0");
    VERIFY(nattrs, 2, "test_attrs: SDgetinfo SDS index 0");

    for (att_idx=0; att_idx < nattrs; att_idx++)
    {
	status = SDgetattdatainfo(sds_id, att_idx, &offset, &length);
	CHECK(status, FAIL, "test_attrs: SDgetattdatainfo");
    }

    status = SDendaccess(sds_id);
    CHECK(status, FAIL, "SDendaccess");

    status = SDend(sd_id);
    CHECK(status, FAIL, "SDend");

    /******************************************************************
     Read data using previously obtained data info without HDF4 library
     ******************************************************************/

#if 0
    /* Open file and read in data without using SD API */
    {
	int   fd;		/* for open */
	int32 ret32;		/* for DFKconvert */
	int   ret;		/* for fabs */
        ssize_t readlen=0;	/* for read */
        int32 *readibuf, *readibuf_swapped;
        float *readfbuf, *readfbuf_swapped;
        char *readcbuf, *readcbuf_swapped;
	char readfbuf_str[12], data2_str[12]; /* for comparing readfbuf values */
        uint32 n_values;
	int ii, jj, kk;

	/* Open the file for reading without SD API */
	fd = open(ATTR_FILE, O_RDONLY);
	if (fd == -1)
	{
	    fprintf(stderr, "test_attrs: unable to open file %s", ATTR_FILE);
	    num_errs++;
            return num_errs;
	}

	/* Forward to the position of the data of SDS at index 1 */
        if (lseek(fd, (off_t)sds1_info.offsets[0], SEEK_SET) == -1)
        {
            fprintf(stderr, "test_attrs: unable to seek offset %d\n",
                (int)sds1_info.offsets[0]);
	    num_errs++;
            return num_errs;
        }

	/* Allocate buffers for SDS' data */
        readibuf = (int32 *) HDmalloc(sds1_info.n_values * sizeof(int32));
        readibuf_swapped = (int32 *) HDmalloc(sds1_info.n_values * sizeof(int32));
        /* Read in this block of data */
        readlen = read(fd, (VOIDP)readibuf, (size_t)sds1_info.lengths[0]);
	CHECK(readlen, FAIL, "DFKconvert");

	ret32 = DFKconvert(readibuf, readibuf_swapped, sds1_info.numtype,
				 (uint32)sds1_info.n_values, DFACC_WRITE, 0, 0);
	CHECK(ret32, FAIL, "DFKconvert");

	if (ret32 > 0)
	{
            /* Compare data read without SD API against the original buffer */
            for (ii = 0; ii < sds1_info.n_values; ii++)
            {
		if (readibuf_swapped[ii] != data1[ii])
		    fprintf(stderr, "At value# %d: written = %d read = %d\n",
					 ii, data1[ii], readibuf_swapped[ii]);
            }
	}

	/* Forward to the position of the data of SDS at index 2 */
        if (lseek(fd, (off_t)sds2_info.offsets[0], SEEK_SET) == -1)
        {
            fprintf(stderr, "test_attrs: unable to seek offset %d\n",
                (int)sds2_info.offsets[0]);
	    num_errs++;
            return num_errs;
        }

	/* Allocate buffers for SDS' data */
        readfbuf = (float32 *) HDmalloc(sds2_info.n_values * sizeof(float32));
        readfbuf_swapped = (float32 *) HDmalloc(sds2_info.n_values * sizeof(float32));
        /* Read in this block of data */
        readlen = read(fd, (VOIDP)readfbuf, (size_t)sds2_info.lengths[0]);
	CHECK(readlen, FAIL, "DFKconvert");

	ret32 = DFKconvert(readfbuf, readfbuf_swapped, sds2_info.numtype,
				 (uint32)sds2_info.n_values, DFACC_WRITE, 0, 0);
	CHECK(ret32, FAIL, "DFKconvert");

        /* Compare data read without SD API against the original buffer */
	kk = 0;
	for (jj = 0; jj < sds2_info.dimsizes[0]; jj++)
            for (ii = 0; ii < sds2_info.dimsizes[1]; ii++)
            {
		/* Flag if the two numbers are not close enough */
		if (fabs(readfbuf_swapped[kk] - data2[jj][ii]) > 0.00001)
		    fprintf(stderr, "At value# %d: written = %f read = %f\n",
				 ii, data2[jj][ii], readfbuf_swapped[kk]);
		if (kk < sds2_info.n_values) kk++;
            }

	/* Forward to the position of the data of SDS at index 3 */
        if (lseek(fd, (off_t)sds3_info.offsets[0], SEEK_SET) == -1)
        {
            fprintf(stderr, "test_attrs: unable to seek offset %d\n",
                (int)sds3_info.offsets[0]);
	    num_errs++;
            return num_errs;
        }

	/* Allocate buffers for SDS' data */
        readibuf = (int32 *) HDmalloc(sds3_info.n_values * sizeof(int32));
        readibuf_swapped = (int32 *) HDmalloc(sds3_info.n_values * sizeof(int32));
        /* Read in this block of data */
        readlen = read(fd, (VOIDP)readibuf, (size_t)sds3_info.lengths[0]);
	CHECK(readlen, FAIL, "DFKconvert");

	ret32 = DFKconvert(readibuf, readibuf_swapped, sds3_info.numtype,
				 (uint32)sds3_info.n_values, DFACC_WRITE, 0, 0);
	CHECK(ret32, FAIL, "DFKconvert");

	if (ret32 > 0)
	{
            /* Compare data read without SD API against the original buffer */
            for (ii = 0; ii < sds3_info.n_values; ii++)
            {
		if (readibuf_swapped[ii] != data3[ii])
		    fprintf(stderr, "At value# %d: written = %d read = %d\n",
					 ii, data3[ii], readibuf_swapped[ii]);
            }
	}

	if (close(fd) == -1)
	{
	    fprintf(stderr, "test_attrs: unable to close file %s", ATTR_FILE);
	    num_errs++;
            return num_errs;
	}
    }
    free_info(&sds1_info);
    free_info(&sds2_info);
    free_info(&sds3_info);
#endif

    /* Return the number of errors that's been kept track of so far */
    return num_errs;
} /* test_attrs */


#define DFAN_FILE "tdfanndg.hdf"
#define MAXLEN_LAB     50
#define MAXLEN_DESC   200
#define ROWS           10
#define COLS           10
#define REPS           2

/* Utility functions: */
/* to generate data set's data */
static VOID gen2Dfloat (int height, int width, float *data);
/* to verify data of labels and descriptions */
static intn check_lab_desc (uint16 tag, uint16 ref, char *label, char *desc);

/****************************************************************
**
**  gen2Dfloat:  generate 2-D data array
**
****************************************************************/
static      VOID
gen2Dfloat(int height, int width, float *data)
{
    int         i, j;
    float      *pdata;

    /* store one value per row, increasing by one for each row */
    pdata = data;
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
            *pdata++ = (float) (i + 1);

}

/****************************************************************
**
**  genimage:  generate image from 2-D float array
**
****************************************************************/
static      VOID
genimage(int height, int width, float *data, uint8 *image)
{
    int         i, limit;
    float      *pdata, max, min, multiplier;

    limit = height * width;
    pdata = data;
    max = min = *pdata;
    for (i = 0; i < limit; i++, pdata++)
      {
          max = (max > *pdata) ? max : *pdata;
          min = (min < *pdata) ? min : *pdata;
      }
    /* store one value per row, increasing by one for each row */
    pdata = data;
    multiplier = (float32) 255.0 / (max - min);
    for (i = 0; i < limit; i++)
        *image++ = (uint8) (((*pdata++) - min) * multiplier);

}

/****************************************************************
**
**  check_lab_desc:  read and compare label and description
**                   with expected ones
**
****************************************************************/
static      intn
check_lab_desc(uint16 tag, uint16 ref, char *label, char *desc)
{
    int32       inlablen, indesclen, ret;
    char        inlabel[MAXLEN_LAB], *indesc;
    intn num_errs=0;

    inlablen = DFANgetlablen(DFAN_FILE, tag, ref);
    CHECK(inlablen, FAIL, "check_lab_desc: DFANgetlablen");

    ret = DFANgetlabel(DFAN_FILE, tag, ref, inlabel, MAXLEN_LAB);
    CHECK(ret, FAIL, "check_lab_desc: DFANgetlabel");
    VERIFY_CHAR(inlabel, label, "check_lab_desc: DFANgetlabel");

    indesclen = DFANgetdesclen(DFAN_FILE, tag, ref);
    CHECK(indesclen, FAIL, "check_lab_desc: DFANgetdesclen");
    if (indesclen >= 0)
    {
        indesc = (char *) HDmalloc(indesclen + 1);
        ret = DFANgetdesc(DFAN_FILE, tag, ref, indesc, MAXLEN_DESC);
        CHECK(ret, FAIL, "check_lab_desc: DFANgetdesc");

        indesc[indesclen] = '\0';
        VERIFY_CHAR(indesc, desc, "check_lab_desc: DFANgetdesc");
        HDfree((VOIDP) indesc);
    }
    return(num_errs);
}


intn add_sdfile_annotations()
{
    int32  file_id;
    char   labels[2][MAXLEN_LAB], descs[2][MAXLEN_DESC], tempstr[MAXLEN_DESC];
    intn   ret;
    intn num_errs=0;

/* set up file labels and descriptions */

    HDstrcpy(labels[0], "File Label #1");
    HDstrcpy(labels[1], "File Label #2");
    HDstrcpy(descs[0], "File Descr #1: This is a file label, added\n");
    HDstrcat(descs[0], "       by the DFAN interface...**END SDS 1 DESCR**\n");
    HDstrcpy(descs[1], "File Descr #2: This is another file label added\n");
    HDstrcat(descs[1], "       by the DFAN API as well.**END SDS 2 DESCR**\n");

/********  Write file labels and descriptions *********/

    file_id = Hopen(DFAN_FILE, DFACC_CREATE, 0);
    if (file_id == FAIL)
        printf("\nUnable to open file %s for writing.\n\n", DFAN_FILE);

    ret = DFANaddfid(file_id, labels[0]);
    CHECK(ret, FAIL, "DFANaddfid");

    ret = DFANaddfid(file_id, labels[1]);
    CHECK(ret, FAIL, "DFANaddfid");

    ret = DFANaddfds(file_id, descs[0], (int32)HDstrlen(descs[0]));
    CHECK(ret, FAIL, "DFANaddfds");

    ret = DFANaddfds(file_id, descs[1], (int32)HDstrlen(descs[1]));
    CHECK(ret, FAIL, "DFANaddfds");

    if (FAIL == Hclose(file_id))
        printf("\nUnable to close file %s after writing.\n\n", DFAN_FILE);

/********  Read file labels *********/

    file_id = Hopen(DFAN_FILE, DFACC_READ, 0);
    if (file_id == FAIL)
        printf("\n\nUnable to open file %s for reading.\n\n", DFAN_FILE);

    ret = DFANgetfidlen(file_id, ISFIRST);
    CHECK(ret, FAIL, "DFANgetfidlen");
    VERIFY(ret, strlen(labels[0]), "DFANgetfidlen first file label");

    ret = DFANgetfid(file_id, tempstr, MAXLEN_LAB, ISFIRST);
    CHECK(ret, FAIL, "DFANgetfid");
    VERIFY_CHAR(labels[0], tempstr, "DFANgetfid first file label");

    ret = DFANgetfidlen(file_id, NOTFIRST);
    CHECK(ret, FAIL, "DFANgetfidlen");
    VERIFY(ret, strlen(labels[1]), "DFANgetfidlen second file label");

    ret = DFANgetfid(file_id, tempstr, MAXLEN_LAB, NOTFIRST);
    CHECK(ret, FAIL, "DFANgetfid");
    VERIFY_CHAR(labels[1], tempstr, "DFANgetfid second file label");

/********  Read file descriptions *********/

    ret = DFANgetfdslen(file_id, ISFIRST);
    CHECK(ret, FAIL, "DFANgetfdslen");
    VERIFY(ret, strlen(descs[0]), "DFANgetfdslen first file description");

    ret = DFANgetfds(file_id, tempstr, MAXLEN_DESC, ISFIRST);
    CHECK(ret, FAIL, "DFANgetfds");
    VERIFY_CHAR(tempstr, descs[0], "DFANgetfds first file description");

    ret = DFANgetfdslen(file_id, NOTFIRST);
    CHECK(ret, FAIL, "DFANgetfdslen");
    VERIFY(ret, strlen(descs[1]), "DFANgetfdslen second file description");

    ret = DFANgetfds(file_id, tempstr, MAXLEN_DESC, NOTFIRST);
    CHECK(ret, FAIL, "DFANgetfds");
    VERIFY_CHAR(tempstr, descs[1], "DFANgetfds second file description");

    if (FAIL == Hclose(file_id))
        printf("\n\nUnable to close file %s after reading.\n\n", DFAN_FILE);

    return (num_errs);
} /* add_sdfile_annotations */


intn add_sds_annotations()
{
    char        labels[2][MAXLEN_LAB], descs[2][MAXLEN_DESC];
    uint16      refnum;
    int32       ret;
    intn        rank;
    int         jj;
    int32       dimsizes[2];
    float      *data;
    intn num_errs=0;

/* set up object labels and descriptions */

    HDstrcpy(labels[0], "Object label #1: sds");
    HDstrcpy(labels[1], "Object label #2: sds");
    HDstrcpy(descs[0], "Object Descr #1: 1 2 3 4 5 6 7 8 9 10 11 12 \n");
    HDstrcat(descs[0], "       13 14 15 16 17 18 19 20 **END SDS 1 DESCR**\n");
    HDstrcpy(descs[1], "Object Descr #2: a b c d e f g h i j k l m n o p \n");
    HDstrcat(descs[1], "       q r s t u v w x y z ??? **END SDS 2 DESCR**\n");

/***** generate float array *****/

    data = (float *) HDmalloc(ROWS * COLS * sizeof(float));
    dimsizes[0] = ROWS;
    dimsizes[1] = COLS;

    /* Generate data for data sets */
    gen2Dfloat(ROWS, COLS, data);

    /* Set rank and dimension sizes for subsequent SDSs */
    ret = DFSDsetdims(2, dimsizes);

    /********  Write labels and descriptions *********/

    /* Write REPS data sets and add a label and a description to each data set */
    for (jj = 0; jj < REPS; jj++)
    {
        /* write out scientific data set */
        ret = DFSDadddata(DFAN_FILE, 2, dimsizes, (VOIDP) data);
        CHECK(ret, FAIL, "add_sds_annotations: DFSDadddata");
        refnum = DFSDlastref();

        /* Add label and description to this data set */
        ret = DFANputlabel(DFAN_FILE, DFTAG_NDG, refnum, labels[jj]);
        CHECK(ret, FAIL, "add_sds_annotations: DFANputlabel");

        ret = DFANputdesc(DFAN_FILE, DFTAG_NDG, refnum,
                              descs[jj], (int32)HDstrlen(descs[jj]));
        CHECK(ret, FAIL, "add_sds_annotations: DFANputdesc");
    }

    /********  Read labels and descriptions *********/
    for (jj = 0; jj < REPS; jj++)
    {
        ret = DFSDgetdims(DFAN_FILE, &rank, dimsizes, 3);
        CHECK(ret, FAIL, "add_sds_annotations: DFSDgetdims");
        refnum = DFSDlastref();

        /* Verify data of labels and descriptions */
        num_errs = check_lab_desc(DFTAG_NDG, refnum, labels[jj], descs[jj]);
    }
    HDfree((VOIDP) data);

    return (num_errs);
} /* add_sds_annotations */


static int test_dfannots(void)
{
    int32 sd_id, sds_id, sds_index;
    intn  ii, status, num_annots;
    int32 rank, data_type, dim_sizes[MAX_VAR_DIMS];
    int32 n_datasets, n_file_attr, n_attrs; 
    int32 *offsetarray=NULL, *lengtharray=NULL;
    ann_type annot_type;
    char  sds_name[MAX_NC_NAME];
    intn  num_errs = 0;

    /* Add file annotations */
    status = add_sdfile_annotations();
    if (status > 0)
        fprintf(stderr, "test_dfannots: errors while adding file annotations\n");

    /* Add SDS annotations */
    status = add_sds_annotations();
    if (status > 0)
        fprintf(stderr, "test_dfannots: errors while adding sds annotations\n");

    /**********************************************************************
     * Using SD API to get offset/length of data from data set annotations *
     **********************************************************************/

    /* Open the file and initialize the SD interface. */
    sd_id = SDstart(DFAN_FILE, DFACC_READ);
    CHECK(sd_id, FAIL, "test_dfannots: SDstart");

    /* Obtain information about the file. */ 
    status = SDfileinfo(sd_id, &n_datasets, &n_file_attr);
    CHECK(status, FAIL, "test_dfannots: SDfileinfo");

    /* Get annotation information of each SDS in the file. */
    for (sds_index=0; sds_index< n_datasets; sds_index++) 
    {
	sds_id = SDselect (sd_id, sds_index);
        CHECK(sds_id, FAIL, "test_dfannots: SDselect");

        /* Only data sets have annotations */
        if (!SDiscoordvar(sds_id))
        {
	    num_annots = SDgetanndatainfo(sds_id, AN_DATA_DESC, 0, NULL, NULL);
            CHECK(num_annots, FAIL, "test_dfannots: SDgetanndatainfo AN_DATA_DESC with NULL buffers");

	    if (num_annots > 0)
	    {
	        offsetarray = (int32 *)HDmalloc(num_annots * sizeof(int32));
	        if (offsetarray == NULL)
		    exit(-1);
	        lengtharray = (int32 *)HDmalloc(num_annots * sizeof(int32));
	        if (lengtharray == NULL)
		    exit(-1);

	        num_annots = SDgetanndatainfo(sds_id, AN_DATA_DESC, num_annots,
						offsetarray, lengtharray);
                CHECK(num_annots, FAIL, "test_dfannots: SDgetanndatainfo AN_DATA_DESC");

	    }

	    num_annots = SDgetanndatainfo(sds_id, AN_DATA_LABEL, 0, NULL, NULL);
            CHECK(num_annots, FAIL, "test_dfannots: SDgetanndatainfo AN_DATA_LABEL with NULL buffers");
	    if (num_annots > 0)
	    {
	        offsetarray = (int32 *)HDmalloc(num_annots * sizeof(int32));
	        if (offsetarray == NULL)
		    exit(-1);
	        lengtharray = (int32 *)HDmalloc(num_annots * sizeof(int32));
	        if (lengtharray == NULL)
		    exit(-1);

	        num_annots = SDgetanndatainfo(sds_id, AN_DATA_LABEL, num_annots,
						offsetarray, lengtharray);
                CHECK(num_annots, FAIL, "test_dfannots: SDgetanndatainfo AN_DATA_LABEL");

	    }
        } /* SDS is not coordinate var */

        /* Terminate access to the selected data set. */
        status = SDendaccess(sds_id);
        CHECK(status, FAIL, "test_dfannots: SDendaccess");
    } /* for each data set */

    /* Terminate access to the SD interface and close the file. */
    status = SDend(sd_id);
    CHECK(status, FAIL, "test_dfannots: SDend");

    /* Return the number of errors that's been kept track of so far */
    return num_errs;
}

/* Test driver for testing the public function SDgetattdatainfo. */
extern int test_att_ann_datainfo()
{
    intn status;
    int num_errs = 0;

    /* Output message about test being performed */
    TESTING("getting location info of attr and annot data (tattdatainfo.c)");

    /* Test getting data info of attributes for SDSs */
    num_errs = num_errs + test_attrs();

    /* Test getting data info of annotations added by DFAN API */
    num_errs = num_errs + test_dfannots();

    /* Test getting data info of annotations added by AN API */
     /* num_errs = num_errs + test_mfannots();
 */ 

    if (num_errs == 0) PASSED();
    return num_errs;
}
#endif /* HDF */
