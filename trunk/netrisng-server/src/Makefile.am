bin_PROGRAMS = netrisng_server
netrisng_server_SOURCES = netrisng_server.cpp cdate.cpp cserver.cpp clog.cpp \
					cgame.cpp net.cpp sqlite.cpp avltree.cpp RBTree.cpp

# set the include path found by configure
INCLUDES= $(all_includes)

# the library search path.
netrisng_server_LDFLAGS = $(all_libraries) 
noinst_HEADERS = main.h clog.h cdate.h cserver.h cgame.h net.h sqlite.h cuser.h \
		avltree.h RBTree.h

