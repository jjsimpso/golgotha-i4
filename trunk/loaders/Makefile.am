## Process this file with automake to produce Makefile.in

include $(top_srcdir)/Makefile.am.global

noinst_LIBRARIES = libbmp.a libdir.a libimage_load.a libjpg_load.a libjpg_write.a libmp3_load.a libtga.a

libbmp_a_SOURCES = $(BMP_SRCS)
libdir_a_SOURCES = $(DIR_SRCS)
libimage_load_a_SOURCES = $(IMAGE_LOAD_SRCS)
libjpg_load_a_SOURCES = $(JPG_LOAD_SRCS)
libjpg_write_a_SOURCES = $(JPG_WRITE_SRCS)
libmp3_load_a_SOURCES = $(MP3_LOAD_SRCS)
libtga_a_SOURCES = $(TGA_SRCS)

CLEANFILES = $(BMP_CLEAN) $(DIR_CLEAN) $(IMAGE_LOAD_CLEAN) $(JPG_LOAD_CLEAN) $(JPG_WRITE_CLEAN) $(MP3_LOAD_CLEAN) $(TGA_CLEAN)

