## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src 

swe545_assignment1_clientdocdir = ${prefix}/doc/swe545_assignment1_client
swe545_assignment1_clientdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(swe545_assignment1_clientdoc_DATA)


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(swe545_assignment1_clientdocdir)
