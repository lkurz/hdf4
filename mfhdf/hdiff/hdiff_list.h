/****************************************************************************
 * NCSA HDF                                                                 *
 * Software Development Group                                               *
 * National Center for Supercomputing Applications                          *
 * University of Illinois at Urbana-Champaign                               *
 * 605 E. Springfield, Champaign IL 61820                                   *
 *                                                                          *
 * For conditions of distribution and use, see the accompanying             *
 * hdf/COPYING file.                                                        *
 *                                                                          *
 ****************************************************************************/


#ifndef HDF_HDIFF_LIST__
#define HDF_HDIFF_LIST__



#ifdef __cplusplus
extern "C" {
#endif

#include "hdiff_table.h"


/* get the list of HDF objects in the file */
int Hgetlist (char* fname, table_t *list);

int hdiff_list_vg (char* fname,int32 file_id,table_t *table);
int hdiff_list_gr (char* fname,int32 file_id,table_t *table);
int hdiff_list_sds(char* fname,int32 file_id,table_t *table);
int hdiff_list_vs (char* fname,int32 file_id,table_t *table);
int hdiff_list_glb(char* fname,int32 file_id,table_t *table);
int hdiff_list_an (char* fname,int32 file_id,table_t *table);


int insert_vg_attrs(int32 vgroup_id,char *path);
int insert_vg_an(int32 file_id,int32 vgroup_id,char *path);


int insert_vg(char* fname, 
              int32 file_id, 
              char*path_name, 
              int32* tags, 
              int32* refs, 
              int npairs, 
              table_t *table);

int  insert_sds(int32 file_id,
                int32 sd_id,
                int32 tag,
                int32 ref,
                char *path_name,
                table_t *table);

int  insert_gr(int32 file_id,
               int32 gr_in,
               int32 tag,               /* tag of input GR */
               int32 ref,               /* ref of input GR */
               char*path_name,          /* absolute path for input group name */
               table_t *table);

int  insert_vs( int32 file_id,
                int32 tag,
                int32 ref,               /* ref of input VS */
                char*path_name,          /* absolute path for input group name */
                table_t *table,
                int is_lone);


int insert_sds_attrs(int32 sds_id,
                     int32 nattrs);

int insert_gr_attrs(int32 ri_id,
                    int32 nattrs);


int insert_an(int32 file_id,
              int32 ref_in, 
              int32 tag_in,
              char *path);

int insert_vs_an(int32 file_id,
                 int32 vdata_id,
                 char *path);

int  insert_vs_attrs(int32 in, int32 findex, intn attrindex);




#ifdef __cplusplus
}
#endif


#endif  /* HDF_HDIFF_LIST__ */