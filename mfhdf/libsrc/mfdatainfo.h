/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * Copyright by the Board of Trustees of the University of Illinois.         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF.  The full HDF copyright notice, including       *
 * terms governing use, modification, and redistribution, is contained in    *
 * the files COPYING and Copyright.html.  COPYING can be found at the root   *
 * of the source code distribution tree; Copyright.html can be found at      *
 * http://hdfgroup.org/products/hdf4/doc/Copyright.html.  If you do not have *
 * access to either file, you may request a copy from help@hdfgroup.org.     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _MF_DATAINFO
#define _MF_DATAINFO

#include "H4api_adpt.h"

/* Activate raw datainfo interface - added for hmap project in 2010 */
#if defined DATAINFO_MASTER | defined DATAINFO_TESTER

#if defined c_plusplus || defined __cplusplus
extern      "C"
{
#endif                          /* c_plusplus || __cplusplus */

 /* #include "mfhdfi.h"
 */ 

/* Public functions for getting raw data information */

HDFLIBAPI intn SDgetdatainfo
    (int32 sdsid, int32 *chk_coord, uintn start_block, uintn info_count,
	int32 *offsetarray, int32 *lengtharray);

HDFLIBAPI intn SDgetattdatainfo
    (int32 id, int32 attrindex, int32 *offset, int32 *length);

HDFLIBAPI intn SDgetdimattdatainfo
    (int32 dimid, int32 sdsid, char *attr_name, int32 *offset, int32 *length);

HDFLIBAPI intn SDgetanndatainfo
    (int32 sdsid, ann_type annot_type, uintn size, int32* offsetarray,
	int32* lengtharray);

#if defined c_plusplus || defined __cplusplus
}
#endif /* c_plusplus || __cplusplus */
#endif /* DATAINFO_MASTER || DATAINFO_TESTER */
#endif /* _MF_DATAINFO */
