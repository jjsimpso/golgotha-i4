## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = foreign

include $(top_srcdir)/Makefile.am.defs


all-local: wmanager.o

wmanager.o: wmanager.cc
	$(CXX) $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CXXFLAGS) -c wmanager.cc -o wmanager.o
