BIN = .

INC = -I./ -I../../module_ngx_common/
LIB_INC = -L./ 

LIBS =	-lpthread

OBJS = test_up.o

TGTS = libtest_up.so

CXXFLAGS = -g -shared -fPIC -W -Wall -Wno-unused-parameter -Werror -D_LARGEFILE64_SOURCE ${GCOV} \
	-D_FILE_OFFSET_BITS=64 -D_REENTRANT -D__VERSION_ID__="\"$(VERSION_ID)\""

TFLAGS = -g -W -Wall -Wno-unused-parameter -Werror -D_LARGEFILE64_SOURCE ${GCOV} \
	-D_FILE_OFFSET_BITS=64 -D_REENTRANT -D__VERSION_ID__="\"$(VERSION_ID)\""

CC = g++

.PHONY  : all clean 

all: $(TGTS)

.cpp.o:
	$(CC) $(CXXFLAGS) -c $< -o $@ $(INC)

.cc.o:
	$(CC) $(CXXFLAGS) -c $< -o $@ $(INC)

$(TGTS): $(OBJS) 
	$(CC) $(CXXFLAGS) -o $(TGTS) $(OBJS) $(INC) $(LIB_INC) $(LIBS)

output:$(TGTS)
	mkdir -p output/
	cp -rf $(TGTS) output/
clean:
	$(RM) $(OBJS) $(TGTS)
	rm -rf test/*.o $(TESTS)        
	rm -fr output/*        
	rm -fr test-output/*        
	find . -name *.lint|xargs rm -f        
	find . -name *.gcda|xargs rm -f        
	find . -name *.gcov|xargs rm -f        
	find . -name *.gcno|xargs rm -f

#Test:$(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -o GuessAd $(INC) $(LIB_INC) $(LIBS) 
