## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src 

swe545_assigment1_serverdocdir = ${prefix}/doc/swe545_assigment1_server
swe545_assigment1_serverdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(swe545_assigment1_serverdoc_DATA)


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(swe545_assigment1_serverdocdir)
