## Process this file with automake to produce Makefile.in

include $(top_srcdir)/Makefile.am.global

noinst_LIBRARIES = liblisp.a liblisp_load.a

liblisp_a_SOURCES = $(LISP_SRCS)
liblisp_load_a_SOURCES = $(LISP_LOAD_SRCS)

CLEANFILES = $(LISP_CLEAN) $(LISP_LOAD_CLEAN)
