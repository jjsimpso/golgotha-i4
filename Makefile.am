## Process this file with automake to produce Makefile.in

include $(top_srcdir)/Makefile.am.global

SUBDIRS =  \
	app \
	area \
	device \
	dll \
	file \
	gui \
	image \
	inc \
	lisp \
	loaders \
	math \
	menu \
	music \
	network \
	quantize \
	sound \
	video

noinst_LIBRARIES = libdll_base.a

libdll_base_a_SOURCES = $(DLL_BASE_SRCS)

CLEANFILES = $(DLL_BASE_CLEAN)
