cmake_minimum_required (VERSION 3.18)
project (HDF4_HDF_SRC C)

if (POLICY CMP0087)
  # To evaluate generator expressions for install(CODE) and install(SCRIPT).
  cmake_policy (SET CMP0087 NEW)
endif ()

LINK_DIRECTORIES (
    ${HDF4_HDF_BINARY_DIR}
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

set (HDF4_HDF_SRC_CSRCS
    ${HDF4_HDF_SRC_SOURCE_DIR}/atom.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/bitvect.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/cdeflate.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/cnbit.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/cnone.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/crle.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/cskphuff.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/cszip.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/df24.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfan.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfcomp.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfconv.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfgr.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfgroup.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfimcomp.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfjpeg.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfknat.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfkswap.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfp.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfr8.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfrle.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfsd.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfstubs.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfufp2i.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfunjpeg.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfutil.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/dynarray.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/hbitio.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/hblocks.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/hbuffer.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/hchunks.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/hcomp.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/hcompri.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/hdatainfo.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/hdfalloc.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/herr.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/hextelt.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/hfile.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/hfile_atexit.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/hfiledd.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/hkit.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/mcache.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/mfan.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/mfgr.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/mstdio.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/tbbt.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/vattr.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/vconv.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/vg.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/vgp.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/vhi.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/vio.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/vparse.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/vrw.c
    ${HDF4_HDF_SRC_SOURCE_DIR}/vsfld.c
)

set (HDF4_HDF_SRC_CHDRS
    ${HDF4_HDF_SRC_SOURCE_DIR}/H4api_adpt.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/df.h
    #${HDF4_BINARY_DIR}/h4config.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hbitio.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hcomp.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hdatainfo.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hdf.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/herr.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hfile.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hlimits.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hntdefs.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hproto.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/htags.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/mfan.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/mfgr.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/vg.h
)

# Internal headers end in _priv.h
set (HDF4_PRIVATE_HDF_SRC_CHDRS
    ${HDF4_HDF_SRC_SOURCE_DIR}/atom_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/bitvect_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/cdeflate_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/cnbit_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/cnone_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/crle_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/cskphuff_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/cszip_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfan_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfgr_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfrig_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfsd_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/dfufp2i_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/dynarray_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hbitio_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hchunks_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hcomp_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hconv_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hdf_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/herr_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hfile_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hfile_atexit_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hkit_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/hqueue_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/mcache_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/mfan_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/mfgr_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/mstdio_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/tbbt_priv.h
    ${HDF4_HDF_SRC_SOURCE_DIR}/vg_priv.h
)

if (BUILD_STATIC_LIBS)
  add_library (${HDF4_SRC_LIB_TARGET} STATIC ${HDF4_HDF_SRC_CSRCS} ${HDF4_HDF_SRC_CHDRS} ${HDF4_PRIVATE_HDF_SRC_CHDRS} ${HDF4_BINARY_DIR}/h4config.h)
  target_include_directories(${HDF4_SRC_LIB_TARGET}
      PRIVATE "${HDF4_HDF_BINARY_DIR};${HDF4_HDFSOURCE_DIR};${HDF4_BINARY_DIR};${HDF4_COMP_INCLUDE_DIRECTORIES}"
      INTERFACE "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>;$<BUILD_INTERFACE:${HDF4_HDF_BINARY_DIR}>"
  )
  target_compile_options(${HDF4_SRC_LIB_TARGET} PRIVATE "${HDF4_CMAKE_C_FLAGS}")
  if (WIN32 AND CMAKE_C_COMPILER_ID MATCHES "[Cc]lang")
    target_compile_options(${HDF4_SRC_LIB_TARGET} PRIVATE -Wno-implicit-function-declaration -Wno-typedef-redefinition)
  endif ()
  target_compile_definitions(${HDF4_SRC_LIB_TARGET}
      PUBLIC
          ${HDF_EXTRA_C_FLAGS}
          ${HDF_EXTRA_FLAGS}
  )
  TARGET_C_PROPERTIES (${HDF4_SRC_LIB_TARGET} STATIC)
  target_link_libraries (${HDF4_SRC_LIB_TARGET} PRIVATE ${LINK_LIBS} ${LINK_COMP_LIBS})
  set_global_variable (HDF4_LIBRARIES_TO_EXPORT "${HDF4_LIBRARIES_TO_EXPORT};${HDF4_SRC_LIB_TARGET}")
  H4_SET_LIB_OPTIONS (${HDF4_SRC_LIB_TARGET} ${HDF4_SRC_LIB_NAME} STATIC 0)
  set_target_properties (${HDF4_SRC_LIB_TARGET} PROPERTIES
      FOLDER libraries
      INTERFACE_INCLUDE_DIRECTORIES "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>"
  )
  set (install_targets ${HDF4_SRC_LIB_TARGET})
  install(CODE "execute_process(
           COMMAND ${CMAKE_COMMAND} -E create_symlink \"./$<TARGET_FILE_NAME:${HDF4_SRC_LIB_TARGET}>\" $<TARGET_FILE_PREFIX:${HDF4_SRC_LIB_TARGET}>${HDF4_SRC_LIB_SYM_NAME}$<TARGET_FILE_SUFFIX:${HDF4_SRC_LIB_TARGET}>
           WORKING_DIRECTORY \$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/${HDF4_INSTALL_LIB_DIR}
       )"
      COMPONENT libraries
  )
endif ()

if (BUILD_SHARED_LIBS)
  add_library (${HDF4_SRC_LIBSH_TARGET} SHARED ${HDF4_HDF_SRC_CSRCS} ${HDF4_HDF_SRC_CHDRS} ${HDF4_PRIVATE_HDF_SRC_CHDRS} ${HDF4_BINARY_DIR}/h4config.h)
  target_include_directories(${HDF4_SRC_LIBSH_TARGET}
      PRIVATE "${HDF4_HDF_BINARY_DIR};${HDF4_HDFSOURCE_DIR};${HDF4_BINARY_DIR};${HDF4_COMP_INCLUDE_DIRECTORIES}"
      INTERFACE "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>;$<BUILD_INTERFACE:${HDF4_HDF_BINARY_DIR}>"
  )
  target_compile_options(${HDF4_SRC_LIBSH_TARGET} PRIVATE "${HDF4_CMAKE_C_FLAGS}")
  if (WIN32 AND CMAKE_C_COMPILER_ID MATCHES "[Cc]lang")
    target_compile_options(${HDF4_SRC_LIBSH_TARGET} PRIVATE -Wno-implicit-function-declaration -Wno-typedef-redefinition)
  endif ()
  target_compile_definitions(${HDF4_SRC_LIBSH_TARGET}
      PUBLIC
          ${HDF_EXTRA_C_FLAGS}
          ${HDF_EXTRA_FLAGS}
  )
  TARGET_C_PROPERTIES (${HDF4_SRC_LIBSH_TARGET} SHARED)
  target_link_libraries (${HDF4_SRC_LIBSH_TARGET} PRIVATE ${LINK_LIBS} ${LINK_COMP_LIBS})
  set_global_variable (HDF4_LIBRARIES_TO_EXPORT "${HDF4_LIBRARIES_TO_EXPORT};${HDF4_SRC_LIBSH_TARGET}")
  H4_SET_LIB_OPTIONS (${HDF4_SRC_LIBSH_TARGET} ${HDF4_SRC_LIB_NAME} SHARED "DF")
  set_target_properties (${HDF4_SRC_LIBSH_TARGET} PROPERTIES
      FOLDER libraries
      COMPILE_DEFINITIONS "H4_BUILT_AS_DYNAMIC_LIB"
      INTERFACE_INCLUDE_DIRECTORIES "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>"
      INTERFACE_COMPILE_DEFINITIONS H4_BUILT_AS_DYNAMIC_LIB=1
  )
  set (install_targets ${install_targets} ${HDF4_SRC_LIBSH_TARGET})
  install(CODE "execute_process(
           COMMAND ${CMAKE_COMMAND} -E create_symlink \"./$<TARGET_FILE_NAME:${HDF4_SRC_LIBSH_TARGET}>\" $<TARGET_FILE_PREFIX:${HDF4_SRC_LIBSH_TARGET}>${HDF4_SRC_LIB_SYM_NAME}$<TARGET_FILE_SUFFIX:${HDF4_SRC_LIBSH_TARGET}>
           WORKING_DIRECTORY \$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/${HDF4_INSTALL_LIB_DIR}
       )"
      COMPONENT libraries
  )
endif ()

#-----------------------------------------------------------------------------
# Add file(s) to CMake Install
#-----------------------------------------------------------------------------
install (
    FILES
        ${HDF4_HDF_SRC_CHDRS}
    DESTINATION
        ${HDF4_INSTALL_INCLUDE_DIR}
    COMPONENT
        headers
)

#-----------------------------------------------------------------------------
# Add Target(s) to CMake Install for import into other projects
#-----------------------------------------------------------------------------
if (HDF4_EXPORTED_TARGETS)
  if (BUILD_SHARED_LIBS)
    INSTALL_TARGET_PDB (${HDF4_SRC_LIBSH_TARGET} ${HDF4_INSTALL_BIN_DIR} libraries)
  endif ()
  if (BUILD_STATIC_LIBS)
    INSTALL_TARGET_PDB (${HDF4_SRC_LIB_TARGET} ${HDF4_INSTALL_LIB_DIR} libraries)
  endif ()

  install (
      TARGETS
          ${install_targets}
      EXPORT
          ${HDF4_EXPORTED_TARGETS}
      LIBRARY DESTINATION ${HDF4_INSTALL_LIB_DIR} COMPONENT libraries
      ARCHIVE DESTINATION ${HDF4_INSTALL_LIB_DIR} COMPONENT libraries
      RUNTIME DESTINATION ${HDF4_INSTALL_BIN_DIR} COMPONENT libraries
      FRAMEWORK DESTINATION ${HDF4_INSTALL_FWRK_DIR} COMPONENT libraries
      INCLUDES DESTINATION include
  )
endif ()

#-----------------------------------------------------------------------------
# Option to build documentation
#-----------------------------------------------------------------------------
if (DOXYGEN_FOUND)
  # This custom target and doxygen/configure work together
  # Replace variables inside @@ with the current values
  add_custom_target (hdf4lib_doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${HDF4_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${HDF4_HDFSOURCE_DIR}
        COMMENT "Generating HDF4 library Source API documentation with Doxygen"
        VERBATIM )

  if (NOT TARGET doxygen)
    add_custom_target (doxygen)
  endif ()

  add_dependencies (doxygen hdf4lib_doc)

endif ()
