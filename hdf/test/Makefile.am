TESTS = testhdf fortest fortestF
check_PROGRAMS = testhdf fortest fortestF

testhdf_SOURCES = an.c anfile.c bitio.c blocks.c buffer.c chunks.c comp.c   \
                  conv.c extelt.c file.c file1.c litend.c macros.c man.c    \
                  mgr.c nbit.c rig.c sdmms.c sdnmms.c sdstr.c slab.c tbv.c  \
                  testhdf.c tree.c tvattr.c tvset.c tvsfpack.c vers.c
testhdf_CPPFLAGS = -I${top_srcdir}/hdf/src
testhdf_LDADD = ../src/libdf.a @LIBS@
testhdf_DEPENDENCIES = testdir ../src/libdf.a

fortest_SOURCES = forsupf.c forsupff.f fortest.c fortestF.f manf.f mgrf.f   \
                  slabwf.f t24f.f tanf.f tanfilef.f tpf.f tr8f.f tsdmmsf.f  \
                  tsdnmmsf.f tsdnntf.f tsdntf.f tsdstrf.f tstubsf.f         \
                  tvsetf.f tvattrf.f
fortest_CPPFLAGS = -I${top_srcdir}/hdf/src
fortest_LDADD = ../src/libdf.a @LIBS@
fortest_DEPENDENCIES = testdir ../src/libdf.a

fortestF_SOURCES = forsupf.c forsupff.f fortestF.f manf.f mgrf.f slabwf.f   \
                   t24f.f tanf.f tanfilef.f tpf.f tr8f.f tsdmmsf.f          \
                   tsdnmmsf.f tsdnntf.f tsdntf.f tsdstrf.f tstubsf.f        \
                   tvattrf.f tvsetf.f
fortestF_CPPFLAGS = -I${top_srcdir}/hdf/src
fortestF_LDADD = ../src/libdf.a @LIBS@
fortestF_DEPENDENCIES = testdir ../src/libdf.a

testdir:
	-mkdir testdir