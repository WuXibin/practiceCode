CC=g++
INC_DIR=-I../../module_ngx_common
LIB_DIR=
CFLAGS=-g -shared -fPIC -W -Wall -Wno-unused-parameter -Werror -D_LARGEFILE64_SOURCE ${GCOV} \
	-D_FILE_OFFSET_BITS=64 -D_REENTRANT -D__VERSION_ID__="\"$(VERSION_ID)\""
LDFLAGS=

OBJS=subrequest_test.o
PROG=libsubtest.so

VERSION_ID=1.0.0.0 
#coverage testing tool
ifeq ($(GCOV_ON),1)
	GCOV= -ftest-coverage -fprofile-arcs -lgcov
endif

.PHONY: all install clean

all: $(PROG)

install:
	
clean:
	-rm -rf $(OBJS) $(PROG) 

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIB_DIR) $(LDFLAGS) 

$(OBJS): %.o : %.cc
	$(CC) $(INC_DIR) $(CFLAGS) -c $< -o $@

